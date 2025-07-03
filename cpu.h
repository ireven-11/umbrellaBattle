#pragma once
#include"charaBase.h"

class CPU:public CharaBase
{
public:
	CPU(const int join_number);
	~CPU();

private:


	//s“®‚Ìó‘Ô
	shared_ptr<StateMachine::IState> actionState_;
};