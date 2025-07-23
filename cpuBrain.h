#pragma once
#include<memory>
#include<list>
#include"IState.h"
#include"waitState.h"
#include"chaseState.h"
#include"escapeState.h"
#include"thinkState.h"
#include"swingState.h"
#include"tackleState.h"
#include"windState.h"
#include"AStar.h"

class CharaBase;
class Routine;

const VECTOR stick_max_range		= VGet(635.0f, -830.0f, 0.0f);
const VECTOR stick_minimum_range	= VGet(-745.0f, 750.0f, 0.0f);

class CPUBrain
{
public:
	CPUBrain();
	~CPUBrain();

	void update(CharaBase* charaBase, Routine* routine, std::shared_ptr<Stage> stage);

private:
	void decideTarget(CharaBase* charaBase);
	void decideNextAction(CharaBase* charaBase, Routine* routine, std::shared_ptr<Stage> stage);
	void decideChaceRoot(CharaBase* charaBase, Routine* routine);

	bool	isTarget_;
	int		randomTarget_;
	float	distance_;
	bool	canCharge_;
	int		dicideActionCount_;
	int		doActionRandom_;
	int		dicideTargetCount_;
	std::list<position> chaseRoot_;
	position aStarStartPosition_;
	position aStarGoalPosition_;
	int		chaseCount_;
	position nextTilePosition_;

	//�s���̏��
	std::shared_ptr<StateMachine::IState> actionState_;
	static std::shared_ptr<ActionState::WaitState> waitState_()
	{
		static std::shared_ptr<ActionState::WaitState> state = std::make_shared<ActionState::WaitState>();
		return state;
	}
	static std::shared_ptr<ActionState::SwingState> swingState_()
	{
		static std::shared_ptr<ActionState::SwingState> state = std::make_shared<ActionState::SwingState>();
		return state;
	}
	static std::shared_ptr<ActionState::TackleState> tackleState_()
	{
		static std::shared_ptr<ActionState::TackleState> state = std::make_shared<ActionState::TackleState>();
		return state;
	}
	static std::shared_ptr <ActionState::WindState> windState_()
	{
		static std::shared_ptr<ActionState::WindState> state = std::make_shared<ActionState::WindState>();
		return state;
	}
	static std::shared_ptr<ActionState::ChaseState> chaseState_()
	{
		static std::shared_ptr<ActionState::ChaseState> state = std::make_shared<ActionState::ChaseState>();
		return state;
	}static std::shared_ptr<ActionState::EscapeState> escapeState_()
	{
		static std::shared_ptr<ActionState::EscapeState> state = std::make_shared<ActionState::EscapeState>();
		return state;
	}
	static std::shared_ptr<ActionState::ThinkState> thinkState_()
	{
		static std::shared_ptr<ActionState::ThinkState> state = std::make_shared<ActionState::ThinkState>();
		return state;
	}
};