#include"DxLib.h"
#include"RotationVectorY.h"

VECTOR RotationVectorY(VECTOR vector, double rotationAngle)
{
	//角度法だとエラーが出るようにする
	assert((-DX_PI_F < rotationAngle && rotationAngle < DX_PI_F) && "回転角度が弧度法（ラジアン）になってないです！これだとベクトルがよくわからんぐらい回転します！");

	//回転
	MATRIX rotationMatrix	= MGetRotY(rotationAngle);
	vector					= VTransform(vector, rotationMatrix);
	return vector;
}