#pragma once
#include"IState.h"

namespace ActionState
{
	class EscapeState : public StateMachine::IState
	{
	public:
		EscapeState();
		~EscapeState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}