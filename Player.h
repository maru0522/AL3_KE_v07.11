#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "input.h"
#include "DebugText.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
#include "Audio.h"

class Player
{
public:
	// 初期化
	void Initialize(Model* model, Model* reticleModel, Model* playerBulletModel);
	// 移動
	void Move();
	// 軸回転
	void Rotate();
	// 攻撃
	void Attack();
	// 更新
	void Update();
	// 描画
	void Draw(ViewProjection viewProjection);

	// 3dレティクル用更新
	void UpdataReticle();
	// 3dレティクル用描画
	void DrawReticle(ViewProjection viewProjection);

	// 2dレティクル用更新
	void UpdateUI();
	// 2dレティクル用描画
	void DrawUI();

	// 衝突を検出したら呼びだされるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// 3Dレティクルのワールド座標を取得
	Vector3 GetReticleWorldPosition();

	// ワールド行列を取得
	Matrix4 GetWorldMatrix();

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; }

	bool isDead_ = false;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// 3Dレティクル用ワールド変換データ
	WorldTransform worldTransform3DReticle_;

	// 2Dレティクル用スプライト
	std::unique_ptr<Sprite> sprite2DReticle_;

	// モデル
	Model* model_ = nullptr;

	// レティクル用モデル
	Model* reticleModel_ = nullptr;

	// 自機弾モデル
	Model* playerBulletModel_ = nullptr;

	// テクスチャハンドル
	uint32_t texCRed_ = 0u;
	uint32_t texCYellow_ = 0u;
	uint32_t texCPink_ = 0u;
	uint32_t texCGreen_ = 0u;

	int8_t attackCoolTime_ = 20;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t pAttackSoundHandle_ = 0;

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};