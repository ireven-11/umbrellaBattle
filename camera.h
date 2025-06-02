#pragma once

const int	maxFallCount = 10;		//最大落下カウント
const int	minimumFallCount = -10;		//最小落下カウント
const float	initZ = -75.00f;	//カメラ初期Z
const float initY = 15.00f;	//カメラ初期Y
const float initTargetY = 10.00f;	//ターゲット初期Y

class Camera
{
public:
	Camera();
	~Camera();

	void update();

private:
	VECTOR position_;		//カメラポジション
	VECTOR targetPosition_;	//カメラのターゲットポジション
};