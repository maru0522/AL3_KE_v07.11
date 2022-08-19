#include "SkyDome.h"
#include <cassert>

void Skydome::Initialize(Model* model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	worldTransform_.Initialize();
}

void Skydome::Update()
{
}

void Skydome::Draw(ViewProjection viewProjection_)
{
    // 3D���f���`��
    model_->Draw(worldTransform_, viewProjection_);
}
