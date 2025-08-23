#pragma once
#include<memory>
#include<list>
#include"IState.h"
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
};