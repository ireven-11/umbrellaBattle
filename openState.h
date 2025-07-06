#pragma once
#include"IState.h"

namespace CharaState
{
	//ŠJ‚¢‚½ó‘Ô
	class OpenState : public StateMachine::IState
	{
	public:
		OpenState();
		~OpenState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}