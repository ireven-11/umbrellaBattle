#pragma once
#include"IState.h"

namespace CharaState
{
	//�J�������
	class OpenState : public StateMachine::IState
	{
	public:
		OpenState();
		~OpenState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}