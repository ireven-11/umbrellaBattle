#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"
#include"calculateDistance.h"
#include <cmath>

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
	if (targetPosition_.x != upPosition.x ||
		targetPosition_.y != upPosition.y ||
		targetPosition_.z != upPosition.z)
	{
		targetPosition_.x = std::lerp(targetPosition_.x, upPosition.x, acceleration_);
		targetPosition_.y = std::lerp(targetPosition_.y, upPosition.y, acceleration_);
		targetPosition_.z = std::lerp(targetPosition_.z, upPosition.z, acceleration_);
	}

	//カメラ座標を移動
	if (position_.x != upPosition.x ||
		position_.y != upPosition.y ||
		position_.z != upPosition.z)
	{
		//ズームが終わってなければ加速度を速くする
		if (!wasZoomUp_)
		{
			acceleration_ += add_move_speed;

			position_.x = std::lerp(position_.x, upPosition.x, acceleration_);
			position_.y = std::lerp(position_.y, upPosition.y + zoom_out_position.y, acceleration_);
			position_.z = std::lerp(position_.z, upPosition.z - zoom_out_position.z, acceleration_);
		}

		//ズームアップ終わり
		if (CalculateDistance<float>(position_,upPosition) < distance_error)
		{
			wasZoomUp_ = true;
		}
	}

	//スカイボックス描画
	MV1SetPosition(skydomeHandle_, VGet(position_.x, position_.y, position_.z));
	MV1DrawModel(skydomeHandle_);

	//カメラの注視点を設定
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}