#pragma once
#include"IState.h"

namespace ActionState
{
	class AttackState : public StateMachine::IState
	{
	public:
		AttackState();
		~AttackState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}