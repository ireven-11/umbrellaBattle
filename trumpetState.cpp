#include"DxLib.h"
#include"charaBase.h"
#include"trumpetState.h"

namespace CharaState
{
	TrumpetState::TrumpetState()
	{
		reset();
	}

	TrumpetState::~TrumpetState()
	{

	}

	void TrumpetState::reset()
	{
		directionCount_ = 0;
	}

	void TrumpetState::changeState(CharaBase* charaBase)
	{
		charaBase->changeFan();
	}

	void TrumpetState::update(CharaBase* charaBase)
	{
		++directionCount_;
		charaBase->vibration();

		//コントローラーを振動させる
		StartJoypadVibration(charaBase->GetcontrolerNumber_(), vibration_power * 2, vibration_time / 2);

		if (directionCount_ > max_direction_count)
		{
			changeState(charaBase);
			charaBase->stopSound();
			reset();
		}
	}
}