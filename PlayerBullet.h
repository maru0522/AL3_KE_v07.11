#pragma once
#include "Model.h"
#include "WorldTransform.h"

enum color {
	Red,	// 0
	Yellow,	// 1
	Pink,	// 2
	Blue,	// 3
	Green,	// 4
};

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity, uint32_t texCRed, uint32_t texCYellow, uint32_t texCGreen, uint32_t texCPink);
	void Update();
	void Update2();
	void Draw(const ViewProjection& viewProjection);

	bool isDead() const { return isDead_; }
	void SetIndexColor(uint8_t index) { indexColor_ = index; }
	void SetScale(Vector3& scale) { worldTransform_.scale_ = scale; }
	void SetRotate(Vector3& rotate) { worldTransform_.rotation_ = rotate; }

	// �Փ˂����o������Ăт������R�[���o�b�N�֐�
	void OnCollision();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texCRed_ = 0;
	uint32_t texCYellow_ = 0;
	uint32_t texCGreen_ = 0;
	uint32_t texCPink_ = 0;

	uint8_t indexColor_ = 0;

	// ���x
	Vector3 velocity_;

	// ���� <frame>
	static const int32_t kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;
};