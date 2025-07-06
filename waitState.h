#pragma once
#include"IState.h"

namespace ActionState
{
	class WaitState : public StateMachine::IState
	{
	public:
		WaitState();
		~WaitState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}