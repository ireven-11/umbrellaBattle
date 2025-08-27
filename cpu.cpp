#include"Dxlib.h"
#include"charaBase.h"
#include"cpuBrain.h"
#include"cpu.h"
#include"stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="join_number">何Pかの数字</param>
CPU::CPU(const int join_number) : CharaBase(join_number)
{

}

/// <summary>
/// デストラクタ
/// </summary>
CPU::~CPU()
{
}

void CPU::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	//コントローラーの入力状態を取得する
	GetJoypadDirectInputState(controlerNumber_, &input);

	//状態によって行動を変える
	brain_->update(this, routine, stage);
	state_->update(this);

	//でばっぐリセット
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = 0.0f;
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(fan_, position_);
	draw();
}

void CPU::wind()
{
	//風を発生させる
	if (canSpawnWind_)
	{
		canSpawnWind_ = false;
		windPosition_ = position_;
		windMoveVector_ = VSub(stage_center, position_);
		windAngle_ = fanAngle_;
		PlaySoundMem(windSound_, DX_PLAYTYPE_BACK, TRUE);
	}
	//移動
	if (!canSpawnWind_)
	{
		++windCount_;
		windPosition_ = VAdd(windPosition_, VGet(windMoveVector_.x / 35, windMoveVector_.y / 35, windMoveVector_.z / 35));

		//風を消す
		if (max_wind_count < windCount_)
		{
			canSpawnWind_	= true;
			windCount_		= 0;
			StopSoundMem(windSound_);
		}
	}
}

//void CPU::move()
//{
//	auto isNoneAction = !isTackle_ && !isSwing_;
//
//	//スティックを傾けたら移動を決定
//	moveVector_ = VGet(move_speed, 0.0f, move_speed);
//	
//	//スティックの傾きからどのくらいモデルを回転させるか決定
//	rotation();
//
//	//スティックを傾けてる向きに移動
//	rotaionMatrix_	= MGetRotY(rotationAngleY_ + agnle_shift_number);
//	moveVector_		= VTransform(moveVector_, rotaionMatrix_);
//	position_		= VAdd(position_, moveVector_);
//}

void CPU::rotation()
{
	//アクションをしてない時だけ
	if (!isMovingtackle_ && !isSwing_)
	{
		MV1SetRotationXYZ(closingUmbrella_, VGet(0.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
	}
}