#pragma once
#include"IState.h"

namespace CharaState
{
	//�������
	class CloseState : public StateMachine::IState
	{
	public:
		CloseState();
		~CloseState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}