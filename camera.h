#pragma once

constexpr float init_Y = 30.0f;
constexpr float init_z = -33.5f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void virtualUpdate(VECTOR upPosition);
	void attensionTargetPlayer(VECTOR attensionPos = VGet(0.0f, 0.0f, 0.0f));
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
	const float		distance_error		= 13.0;						//距離誤差
	const float		scale				= 0.1f;						//スカイドームのスケール
	const float		add_move_speed		= 0.002f;					//カメラの加速度
	const VECTOR	zoom_in_position	= VGet(0.0f, 15.0f, -16.0f);
};