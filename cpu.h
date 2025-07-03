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
	static shared_ptr<ActionState::WaitState> waitState_()
	{
		static shared_ptr<ActionState::WaitState> state = make_shared<ActionState::WaitState>();
		return state;
	}
	static shared_ptr<ActionState::AttackState> attackState_()
	{
		static shared_ptr<ActionState::AttackState> state = make_shared<ActionState::AttackState>();
		return state;
	}
	static shared_ptr<ActionState::ChaseState> chaseState_()
	{
		static shared_ptr<ActionState::ChaseState> state = make_shared<ActionState::ChaseState>();
		return state;
	}static shared_ptr<ActionState::EscapeState> escapeState_()
	{
		static shared_ptr<ActionState::EscapeState> state = make_shared<ActionState::EscapeState>();
		return state;
	}
	static shared_ptr<ActionState::ThinkState> thinkState_()
	{
		static shared_ptr<ActionState::ThinkState> state = make_shared<ActionState::ThinkState>();
		return state;
	}
};