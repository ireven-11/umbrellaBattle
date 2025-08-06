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
		charaBase->transformFan();
	}

	void TrumpetState::update(CharaBase* charaBase)
	{
		++directionCount_;
		if (directionCount_ > max_direction_count)
		{
			changeState(charaBase);
		}
	}
}