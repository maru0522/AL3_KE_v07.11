#include "GuidLine.h"

void GuidLine::Initialize(Model* model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	// �V���O���g���C���X�^���X���擾����
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
	//���[���h�s��X�V
	worldTransform_.UpdateMatrix();
}

void GuidLine::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 GuidLine::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
