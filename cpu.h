#pragma once
#include"charaBase.h"

class CPU:public CharaBase
{
public:
	CPU(const int join_number);
	~CPU();

private:


	//�s���̏��
	shared_ptr<StateMachine::IState> actionState_;
};