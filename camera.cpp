#include"DxLib.h"
#include"camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);

	//奥行1～100までをカメラの描画範囲とする
	SetCameraNearFar(1.00f, 1000.00f);
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// 更新
/// </summary>
void Camera::update()
{
	
}