#include"DxLib.h"
#include"camera.h"

Camera::Camera()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);

	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 100.00f);
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);
}

Camera::~Camera()
{
}

void Camera::update()
{
	
}