#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	position_				= VGet(0.0f, init_Y, init_z);
	targetPosition_			= VGet(0.0f, 0.0f, 0.0f);
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
	//奥行1～100までをカメラの描画範囲とする
	SetCameraNearFar(1.00f, 1000.00f);

	//カメラの注視点を設定
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}

void Camera::virtualUpdate(VECTOR upPosition)
{
	//奥行1～100までをカメラの描画範囲とする
	SetCameraNearFar(1.00f, 1000.00f);

	//カメラの注視点を設定
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	//注視点を移動
	if (targetPosition_.x - upPosition.x > error || targetPosition_.x - upPosition.x < -error)//誤差を設定
	{
		if (targetPosition_.x < upPosition.x)
		{
			targetPosition_.x += move_speed;
		}
		else if (targetPosition_.x > upPosition.x)
		{
			targetPosition_.x -= move_speed;
		}
	}
	if (targetPosition_.z - upPosition.z > error || targetPosition_.z - upPosition.z < -error)//誤差を設定
	{
		if (targetPosition_.z < upPosition.z)
		{
			targetPosition_.z += move_speed;
		}
		else if (targetPosition_.z > upPosition.z)
		{
			targetPosition_.z -= move_speed;
		}
	}

	//カメラ座標を移動
	if (position_.x - upPosition.x > error ||
		position_.x - upPosition.x < -error)//誤差を設定
	{
		if (position_.x < upPosition.x)
		{
			position_.x += move_speed;
		}
		else if (position_.x > upPosition.x)
		{
			position_.x -= move_speed;
		}
	}
	if (position_.y > upPosition.y + zoom_out_position.y)
	{
		position_.y -= move_speed;
	}
	if (position_.z - upPosition.z + zoom_out_position.z > error ||
		position_.z - upPosition.z + zoom_out_position.z < -error)//誤差を設定
	{
		if (position_.z < upPosition.z + zoom_out_position.z)
		{
			position_.z += move_speed;
		}
		else if (position_.z > upPosition.z + zoom_out_position.z)
		{
			position_.z -= move_speed;
		}
	}

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}