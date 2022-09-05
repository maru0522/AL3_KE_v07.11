#include "GuidLine.h"

void GuidLine::Initialize(Model* model)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.translation_ = { 0,-6, 7 };
	worldTransform_.scale_ = { 1,1,40 };
	worldTransform_.rotation_ = { 0,1.5708 ,0 };
	//worldTransform_

	worldTransform_.Initialize();
}

void GuidLine::Update()
{
	//ワールド行列更新
	worldTransform_.UpdateMatrix();
}

void GuidLine::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 GuidLine::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
