#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);

	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// �X�V
/// </summary>
void Camera::update()
{
	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 1000.00f);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}