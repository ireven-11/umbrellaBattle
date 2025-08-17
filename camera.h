#pragma once

constexpr float init_Y = 30.0f;
constexpr float init_z = -30.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void virtualUpdate(VECTOR upPosition);

	bool GetwasZoomUP_()const { return wasZoomUp_; }

private:
	VECTOR	position_;				//カメラポジション
	VECTOR	targetPosition_;		//カメラのターゲットポジション
	bool	wasZoomUp_;				//ズームアップしたかどうか
	bool	wasZoomUPXYZ_[3];		//ズームアップしたかどうかxyz
	
	const float		move_speed			= 0.3f;						//移動スピード
	const VECTOR	zoom_out_position	= VGet(0.0f, 10.0f, 8.0f);	//ズームアウト座標
	const float		error				= 0.3;						//誤差
};