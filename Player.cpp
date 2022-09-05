#include "Player.h"
#include "Calc.h"

void Player::Initialize(Model* model, Model* reticleModel, Model* playerBulletModel)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	reticleModel_ = reticleModel;
	playerBulletModel_ = playerBulletModel;
	texCRed_ = TextureManager::Load("playerBullet/playerBulletRed.png");
	texCYellow_ = TextureManager::Load("playerBullet/playerBulletYellow.png");
	texCGreen_ = TextureManager::Load("playerBullet/playerBulletGreen.png");
	texCPink_ = TextureManager::Load("playerBullet/playerBulletPink.png");

	// レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("Task1_2Resources/reticle.jpg");

	//スプライト生成
	sprite2DReticle_.reset(Sprite::Create(textureReticle, {}, { 1,1,1,1 }, { 0.5,0.5 }));

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	isDead_ = false;

	//音
	pAttackSoundHandle_ = audio_->LoadWave("Task1_2Resources/sounds/shot.wav");

	worldTransform_.translation_ = { 0,-6, 8 };
	worldTransform_.rotation_ = { 0 ,0,0 };

	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();
}

void Player::Move()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更
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

	// 移動限界座標
	const float kMoveLimitX = 27;
	const float kMoveLimitY = 18;

	// 範囲を超えない処理
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

		// 弾の速度
		const float kBulletSpeed = 1.0f;

		// 速度ベクトルを自機の向きに合わせて回転させる
		 Vector3 velocity = GetReticleWorldPosition() - GetWorldPosition();
		 velocity = velocity.normalize() * kBulletSpeed;

		// 弾を発射し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(playerBulletModel_, GetWorldPosition() , velocity,texCRed_,texCYellow_, texCGreen_,texCPink_);

		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Update()
{
	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bulet) {
		return bulet->isDead();
					   });

	// デバッグテキスト
	//debugText_->SetPos(50, 50);
	//debugText_->Printf("player:(%f,%f,%f)",
	//				   worldTransform_.translation_.x,
	//				   worldTransform_.translation_.y,
	//				   worldTransform_.translation_.z);

	// 移動
	Move();
	// 回転
	Rotate();
	if (input_->TriggerKey(DIK_SPACE) && attackCoolTime_ <= 0) {
		// 弾発射
		Attack();
		attackCoolTime_ = 80;
	}
	attackCoolTime_--;

	UpdataReticle();

	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//ワールド行列更新
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
	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 20.0f;
	// 自機から3Dレティクルへのオフセット
	Vector3 offset{ 0,0,1.0f };
	// 自機のワールド行列の回転を反映
	offset = Calc::DotVecMat(offset, worldTransform_.matWorld_);
	// ベクトルの長さを整える
	offset = offset.normalize() * kDistancePlayerTo3DReticle;
	// 3Dレティクルの座標を設定
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

	//// ビューポート行列
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
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetReticleWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
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
