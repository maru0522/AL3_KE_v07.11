#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "input.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include <random>
#include "audio.h"

// 自機クラスの前方宣言
class Player;

enum class Phase {
	Approach,	// 接近する
	Leave,		// 離脱する
};

class Enemy
{
private:
	// 発射間隔
	static const int kFireInterval = 60;

	// 発射タイマ
	int32_t fireTimer = 0;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	//uint32_t textureHandle_ = 0;

	DebugText* debugText_ = nullptr;

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// 自キャラ
	Player* player_ = nullptr;

	// デスフラグ
	bool isDead_ = false;

	int timer_ = 20;

	uint32_t point_;

	Audio* audio_ = nullptr;

	uint32_t eDeadSound_ = 0;
public:
	void Initialize(Model* model, Vector3& pos, uint32_t point);
	void Fire();
	void FireForward();

	void SetWorldPosition(Vector3& pos);

	void PhaseInitApproach();
	void PhaseApproach();
	void PhaseLeave();
	void Update();
	void Draw(ViewProjection viewProjection);
	void SetPlayer(Player* player) { player_ = player; }

	int32_t fireCoolTime = 120;

	bool isDead() const { return isDead_; }

	// 衝突を検出したら呼びだされるコールバック関数
	void OnCollision();

	void SetIsDead() { isDead_ = true; }

	// 弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetPosition();

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; }

	uint32_t GetPoint() { return point_; }
};