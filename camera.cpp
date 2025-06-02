#include"DxLib.h"
#include"camera.h"

Camera::Camera()
{
	position_.x = 0.0f;;
	position_.y = initY;
	position_.z = initZ;
}

Camera::~Camera()
{
}

void Camera::update()
{
	//‰œs1`100‚Ü‚Å‚ğƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Æ‚·‚é
	SetCameraNearFar(1.00f, 100.00f);
	SetCameraPositionAndTarget_UpVecY(VGet(position_.x, position_.y, position_.z), VGet(targetPosition_.x, targetPosition_.y, targetPosition_.z));
}