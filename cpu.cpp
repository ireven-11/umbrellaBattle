#include"Dxlib.h"
#include"charaBase.h"
#include"cpuBrain.h"
#include"cpu.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="join_number">何Pかの数字</param>
CPU::CPU(const int join_number) : CharaBase(join_number)
{
	actionState_ = thinkState_();
}

/// <summary>
/// デストラクタ
/// </summary>
CPU::~CPU()
{
}

void CPU::update()
{
	//コントローラーの入力状態を取得する
	GetJoypadDirectInputState(controlerNumber_, &input);

	//状態によって行動を変える
	actionState_->update(this);
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