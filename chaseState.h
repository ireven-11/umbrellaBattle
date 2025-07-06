#pragma once
#include"IState.h"

namespace ActionState
{
	class ChaseState : public StateMachine::IState
	{
	public:
		ChaseState();
		~ChaseState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}