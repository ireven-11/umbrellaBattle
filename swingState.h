#pragma once
#include"IState.h"

namespace ActionState
{
	class SwingState : public StateMachine::IState
	{
	public:
		SwingState();
		~SwingState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	private:

	};
}