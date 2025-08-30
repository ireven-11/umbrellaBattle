#pragma once

constexpr float init_Y = 30.0f;
constexpr float init_z = -35.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void virtualUpdate(VECTOR upPosition);
	void reset();

	bool GetwasZoomUP_()const { return wasZoomUp_; }

private:
	VECTOR	position_;				//カメラポジション
	VECTOR	targetPosition_;		//カメラのターゲットポジション
	bool	wasZoomUp_;				//ズームアップしたかどうか
	bool	wasZoomUPXYZ_[3];		//ズームアップしたかどうかxyz
	int		skydomeHandle_;			//スカイドームハンドル
	float	acceleration_;			//加速度
	
	const VECTOR	zoom_out_position	= VGet(0.0f, 10.0f, 8.0f);	//ズームアウト座標
	const float		error				= 0.3;						//誤差
	const float		scale				= 0.1;						//スカイドームのスケール
	const float		add_move_speed		= 0.0075;					//カメラの加速度
};