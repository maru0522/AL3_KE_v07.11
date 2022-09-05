#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "input.h"
#include "DebugText.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>

class GuidLine
{
public:
	// 初期化
	void Initialize(Model* model);
	// 更新
	void Update();
	// 描画
	void Draw(ViewProjection viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// ワールド行列を取得
	/*Matrix4 GetWorldMatrix();*/

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; }
private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

