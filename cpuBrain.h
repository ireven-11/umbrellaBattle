#pragma once
#include<memory>
#include"IState.h"
#include"waitState.h"
#include"attackState.h"
#include"chaseState.h"
#include"escapeState.h"
#include"thinkState.h"

class CharaBase;
class Routine;

class CPUBrain
{
public:
	CPUBrain();
	~CPUBrain();

	void update(CharaBase* charaBase, Routine* routine);

private:
	void decideTarget(CharaBase* charaBase);
	void decideNextAction(CharaBase* charaBase, Routine* routine);

	bool	isTarget_;
	int		randomTarget_;
	float	distance_;
	bool	canCharge_;

	//s“®‚Ìó‘Ô
	std::shared_ptr<StateMachine::IState> actionState_;
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