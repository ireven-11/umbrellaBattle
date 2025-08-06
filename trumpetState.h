#pragma once
#include"IState.h"

namespace CharaState
{
	//ラッパ状態
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);

	private:
		void reset();

		int directionCount_;	//演出カウント

		const int max_direction_count = 100;
	};
}