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
	// ������
	void Initialize(Model* model);
	// �X�V
	void Update();
	// �`��
	void Draw(ViewProjection viewProjection);

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	// ���[���h�s����擾
	/*Matrix4 GetWorldMatrix();*/

	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; }
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
};

