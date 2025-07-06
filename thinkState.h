#pragma once
#include"IState.h"

namespace ActionState
{
	class ThinkState : public StateMachine::IState
	{
	public:
		ThinkState();
		~ThinkState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}