#pragma once
#include"IState.h"

namespace CharaState
{
	//î•—‹@ó‘Ô
	class FanState : public StateMachine::IState
	{
	public:
		FanState();
		~FanState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}