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
	// ������
	void Initialize(Model* model, Model* reticleModel, Model* playerBulletModel);
	// �ړ�
	void Move();
	// ����]
	void Rotate();
	// �U��
	void Attack();
	// �X�V
	void Update();
	// �`��
	void Draw(ViewProjection viewProjection);

	// 3d���e�B�N���p�X�V
	void UpdataReticle();
	// 3d���e�B�N���p�`��
	void DrawReticle(ViewProjection viewProjection);

	// 2d���e�B�N���p�X�V
	void UpdateUI();
	// 2d���e�B�N���p�`��
	void DrawUI();

	// �Փ˂����o������Ăт������R�[���o�b�N�֐�
	void OnCollision();

	// �e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();
	// 3D���e�B�N���̃��[���h���W���擾
	Vector3 GetReticleWorldPosition();

	// ���[���h�s����擾
	Matrix4 GetWorldMatrix();

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; }

	bool isDead_ = false;

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// 3D���e�B�N���p���[���h�ϊ��f�[�^
	WorldTransform worldTransform3DReticle_;

	// 2D���e�B�N���p�X�v���C�g
	std::unique_ptr<Sprite> sprite2DReticle_;

	// ���f��
	Model* model_ = nullptr;

	// ���e�B�N���p���f��
	Model* reticleModel_ = nullptr;

	// ���@�e���f��
	Model* playerBulletModel_ = nullptr;

	// �e�N�X�`���n���h��
	uint32_t texCRed_ = 0u;
	uint32_t texCYellow_ = 0u;
	uint32_t texCPink_ = 0u;
	uint32_t texCGreen_ = 0u;

	int8_t attackCoolTime_ = 20;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t pAttackSoundHandle_ = 0;

	// �e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};