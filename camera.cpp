#include"DxLib.h"
#include"camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);

	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 1000.00f);
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
	
}