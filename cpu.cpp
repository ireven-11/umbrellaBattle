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

	//ダメージ状態をリセットする
	onDamage_ = false;

	if (!onHitStop_)
	{
		//状態によって行動を変える
		brain_->update(this, routine, stage);
		state_->update(this);
	}
	else
	{
		hitStopNow();
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(fan_, position_);
}

void CPU::wind()
{
	//風を発生させる
	if (canSpawnWind_)
	{
		canSpawnWind_		= false;
		windPosition_		= position_;
		windMoveVector_		= VSub(stage_center, position_);
		windAngle_			= fanAngle_;
		PlaySoundMem(windSound_, DX_PLAYTYPE_BACK, TRUE);
	}
	//移動
	if (!canSpawnWind_)
	{
		++windCount_;
		windPosition_ = VAdd(windPosition_, VGet(windMoveVector_.x / 35, 0.0f, windMoveVector_.z / 35));

		//風を消す
		if (max_wind_count < windCount_)
		{
			canSpawnWind_	= true;
			windCount_		= 0;
			StopSoundMem(windSound_);
		}
	}
}

void CPU::rotation()
{
	//アクションをしてない時だけ
	if (!isMovingTackle_ && !isSwing_)
	{
		MV1SetRotationXYZ(inverseUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
	}
}

void CPU::tackle()
{
	if (input.Buttons[1] > 0 && !isMovingTackle_ ||
		input.Buttons[0] > 0 && !isMovingTackle_ ||
		input.Buttons[0] > 0 && !isMovingTackle_)
	{
		isChargeTackle_ = true;
	}
	else
	{
		isChargeTackle_ = false;
	}

	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[1] == 0 ||
		tackleCount_ > 0 && input.Buttons[0] == 0 ||
		tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingTackle_ = true;
		StopSoundMem(chargeSound_);
		canLoopSound_ = false;
		--tackleCount_;
		tackleMoving();

		if (!isOneSE_)
		{
			PlaySoundMem(tackleSound_, DX_PLAYTYPE_BACK);
			SetFrequencySoundMem(-1, chargeSound_);
			isOneSE_ = true;
		}

		//アクションするとhpが減る
		subHp();
	}
	//Bボタンを押したら
	else if (isChargeTackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			tackleCount_++;
			tackleInplusePercent_ += add_tackle_inpluse_percent;

			if (max_tackle_count == tackleCount_)
			{
				SetFrequencySoundMem(65000, chargeSound_);
			}
		}

		//どの方向にタックルするかY軸の回転行列で決める
		rotaionMatrix_ = MGetRotY(static_cast<float>(rotationAngleY_ + agnle_shift_number));

		if (!canLoopSound_)
		{
			PlaySoundMem(chargeSound_, DX_PLAYTYPE_LOOP, TRUE);
			canLoopSound_ = true;
		}
	}

	//カウントが０なるかタックル中にBを押したらやめる
	if (tackleCount_ == 0 && isMovingTackle_ || isMovingTackle_ && input.Buttons[1] > 0 ||
		tackleCount_ == 0 && isMovingTackle_ || isMovingTackle_ && input.Buttons[0] > 0 ||
		tackleCount_ == 0 && isMovingTackle_ || isMovingTackle_ && input.Buttons[0] > 0)
	{
		//タックルをやめる
		stopTackle();
	}
}