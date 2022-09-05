#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity, uint32_t texCRed, uint32_t texCYellow, uint32_t texCGreen, uint32_t texCPink)
{
	// Null�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	// �e�N�X�`���ǂݍ���
	texCRed_ = texCRed;
	texCYellow_ = texCYellow;
	texCGreen_ = texCGreen;
	texCPink_ = texCPink;


	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	worldTransform_.Initialize();

	velocity_ = velocity;
}


void PlayerBullet::Update()
{
	// ���W���ړ�������
	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();

	if (0 < worldTransform_.translation_.z && worldTransform_.translation_.z < 14) {
		indexColor_ = Red;
	}
	else if (14 < worldTransform_.translation_.z && worldTransform_.translation_.z < 28) {
		indexColor_ = Yellow;
	}
	else if (28 < worldTransform_.translation_.z && worldTransform_.translation_.z < 42) {
		indexColor_ = Pink;
	}
	else if (42 < worldTransform_.translation_.z && worldTransform_.translation_.z < 56) {
		indexColor_ = Blue;
	}
	else if (56 < worldTransform_.translation_.z && worldTransform_.translation_.z < 70) {
		indexColor_ = Green;
	}
	else if (80 < worldTransform_.translation_.z) {
		indexColor_ = Red;
	}

	// ���Ԍo�߂�death
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Update2()
{
	worldTransform_.UpdateMatrix();
}


void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	switch (indexColor_) {
		case Red:
			model_->Draw(worldTransform_, viewProjection, texCRed_);
			break;
		case Yellow:
			model_->Draw(worldTransform_, viewProjection, texCYellow_);
			break;
		case Pink:
			model_->Draw(worldTransform_, viewProjection, texCPink_);
			break;
		case Blue:
			model_->Draw(worldTransform_, viewProjection);
			break;
		case Green:
			model_->Draw(worldTransform_, viewProjection, texCGreen_);
			break;
		default:
			model_->Draw(worldTransform_, viewProjection, texCRed_);
	}
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 PlayerBullet::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}