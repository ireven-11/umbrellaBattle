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