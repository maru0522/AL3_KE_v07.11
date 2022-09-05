#include "Player.h"
#include "Calc.h"

void Player::Initialize(Model* model, Model* reticleModel, Model* playerBulletModel)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	reticleModel_ = reticleModel;
	playerBulletModel_ = playerBulletModel;
	texCRed_ = TextureManager::Load("playerBullet/playerBulletRed.png");
	texCYellow_ = TextureManager::Load("playerBullet/playerBulletYellow.png");
	texCGreen_ = TextureManager::Load("playerBullet/playerBulletGreen.png");
	texCPink_ = TextureManager::Load("playerBullet/playerBulletPink.png");

	// ���e�B�N���p�e�N�X�`���擾
	uint32_t textureReticle = TextureManager::Load("Task1_2Resources/reticle.jpg");

	//�X�v���C�g����
	sprite2DReticle_.reset(Sprite::Create(textureReticle, {}, { 1,1,1,1 }, { 0.5,0.5 }));

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	isDead_ = false;

	//��
	pAttackSoundHandle_ = audio_->LoadWave("Task1_2Resources/sounds/shot.wav");

	worldTransform_.translation_ = { 0,-6, 8 };
	worldTransform_.rotation_ = { 0 ,0,0 };

	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();
}

void Player::Move()
{
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	// �L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.2f;

	// �����������ňړ��x�N�g����ύX
	/*if (input_->PushKey(DIK_W)) {
		move = { 0,kCharacterSpeed,0 };
	}
	if (input_->PushKey(DIK_S)) {
		move = { 0,-kCharacterSpeed,0 };
	}*/
	if (input_->PushKey(DIK_A)) {
		move = { -kCharacterSpeed,0,0 };
	}
	if (input_->PushKey(DIK_D)) {
		move = { kCharacterSpeed,0,0 };
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// �ړ����E���W
	const float kMoveLimitX = 27;
	const float kMoveLimitY = 18;

	// �͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

void Player::Rotate()
{
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_.y -= 0.05f;
	}
	if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_.y += 0.05f;
	}

}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->PlayWave(pAttackSoundHandle_, false,0.02);

		// �e�̑��x
		const float kBulletSpeed = 1.0f;

		// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		 Vector3 velocity = GetReticleWorldPosition() - GetWorldPosition();
		 velocity = velocity.normalize() * kBulletSpeed;

		// �e�𔭎˂��A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(playerBulletModel_, GetWorldPosition() , velocity,texCRed_,texCYellow_, texCGreen_,texCPink_);

		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Update()
{
	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bulet) {
		return bulet->isDead();
					   });

	// �f�o�b�O�e�L�X�g
	//debugText_->SetPos(50, 50);
	//debugText_->Printf("player:(%f,%f,%f)",
	//				   worldTransform_.translation_.x,
	//				   worldTransform_.translation_.y,
	//				   worldTransform_.translation_.z);

	// �ړ�
	Move();
	// ��]
	Rotate();
	if (input_->TriggerKey(DIK_SPACE) && attackCoolTime_ <= 0) {
		// �e����
		Attack();
		attackCoolTime_ = 80;
	}
	attackCoolTime_--;

	UpdataReticle();

	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//���[���h�s��X�V
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
	DrawReticle(viewProjection);

	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::UpdataReticle()
{
	// ���@����3D���e�B�N���ւ̋���
	const float kDistancePlayerTo3DReticle = 20.0f;
	// ���@����3D���e�B�N���ւ̃I�t�Z�b�g
	Vector3 offset{ 0,0,1.0f };
	// ���@�̃��[���h�s��̉�]�𔽉f
	offset = Calc::DotVecMat(offset, worldTransform_.matWorld_);
	// �x�N�g���̒����𐮂���
	offset = offset.normalize() * kDistancePlayerTo3DReticle;
	// 3D���e�B�N���̍��W��ݒ�
	worldTransform3DReticle_.translation_ = GetWorldPosition() + offset;
	worldTransform3DReticle_.UpdateMatrix();
}

void Player::DrawReticle(ViewProjection viewProjection)
{
	reticleModel_->Draw(worldTransform3DReticle_, viewProjection);
}

void Player::UpdateUI()
{
	Vector3 postionReticle = GetReticleWorldPosition();

	//// �r���[�|�[�g�s��
	//Matrix4 matViewport = 
}

void Player::DrawUI()
{
	sprite2DReticle_->Draw();
}

void Player::OnCollision()
{
	isDead_ = true;
}

Vector3 Player::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetReticleWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}

Matrix4 Player::GetWorldMatrix()
{
	Matrix4 worldMat;
	return worldMat = worldTransform_.matWorld_;
}
