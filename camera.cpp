#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	//ステージ背景をセット
	skydomeHandle_ = MV1LoadModel("3dmodel/Skydome/スカイドーム_雨空PP3/Skydome_PP3/Dome_PP301.pmx");
	MV1SetScale(skydomeHandle_, VGet(scale, scale, scale));
	MV1SetUseZBuffer(skydomeHandle_, FALSE);

	position_				= VGet(0.0f, init_Y, init_z);
	targetPosition_			= VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_				= false;
	acceleration_			= 0.0f;
	for (auto i = 0; i < 3; i++)
	{
		wasZoomUPXYZ_[i] = false;
	}

	//ゼットバッファを有効にする
	SetUseZBufferFlag(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	SetUseSetDrawScreenSettingReset(false);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	MV1DeleteModel(skydomeHandle_);
}

void Camera::reset()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_		= false;
	acceleration_	= 0.0f;
	for (auto i = 0; i < 3; i++)
	{
		wasZoomUPXYZ_[i] = false;
	}
}

/// <summary>
/// 更新
/// </summary>
void Camera::update()
{
	//奥行1～100までをカメラの描画範囲とする
	SetCameraNearFar(1.00f, 500.00f);

	//カメラの注視点を設定
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	//スカイボックス描画
	MV1SetPosition(skydomeHandle_, VGet(position_.x, position_.y - 30.0f, position_.z));
	MV1DrawModel(skydomeHandle_);
	
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}

void Camera::virtualUpdate(VECTOR upPosition)
{
	//奥行1～100までをカメラの描画範囲とする
	SetCameraNearFar(1.00f, 500.00f);

	//注視点を移動
	if (targetPosition_.x - upPosition.x > error || targetPosition_.x - upPosition.x < -error)//誤差を設定
	{
		if (targetPosition_.x < upPosition.x)
		{
			targetPosition_.x += acceleration_;
		}
		else if (targetPosition_.x > upPosition.x)
		{
			targetPosition_.x -= acceleration_;
		}
	}
	if (targetPosition_.z - upPosition.z > error || targetPosition_.z - upPosition.z < -error)//誤差を設定
	{
		if (targetPosition_.z < upPosition.z)
		{
			targetPosition_.z += acceleration_;
		}
		else if (targetPosition_.z > upPosition.z)
		{
			targetPosition_.z -= acceleration_;
		}
	}

	//カメラ座標を移動
	if (position_.x - upPosition.x > error ||
		position_.x - upPosition.x < -error)//誤差を設定
	{
		if (position_.x < upPosition.x)
		{
			position_.x += acceleration_;
		}
		else if (position_.x > upPosition.x)
		{
			position_.x -= acceleration_;
		}
	}
	else
	{
		wasZoomUPXYZ_[0] = true;
	}
	if (position_.y > upPosition.y + zoom_out_position.y)
	{
		position_.y -= acceleration_;
	}
	else
	{
		wasZoomUPXYZ_[1] = true;
	}
	if (position_.z - upPosition.z + zoom_out_position.z > error ||
		position_.z - upPosition.z + zoom_out_position.z < -error)//誤差を設定
	{
		if (position_.z < upPosition.z + zoom_out_position.z)
		{
			position_.z += acceleration_;
		}
		else if (position_.z > upPosition.z + zoom_out_position.z)
		{
			position_.z -= acceleration_;
		}
	}
	else
	{
		wasZoomUPXYZ_[2] = true;
	}

	//スカイボックス描画
	MV1SetPosition(skydomeHandle_, VGet(position_.x, position_.y, position_.z));
	MV1DrawModel(skydomeHandle_);

	//ズーム終わりを表す
	if (wasZoomUPXYZ_[0] && wasZoomUPXYZ_[1] && wasZoomUPXYZ_[2])
	{
		wasZoomUp_ = true;
	}
	else
	{
		//ズームが終わってなければ加速度を速くする
		acceleration_ += add_move_speed;
	}

	//カメラの注視点を設定
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}