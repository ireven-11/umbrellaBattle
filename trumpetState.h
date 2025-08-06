#pragma once
#include"IState.h"

namespace CharaState
{
	//���b�p���
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);

	private:
		void reset();

		int directionCount_;	//���o�J�E���g

		const int max_direction_count = 100;
	};
}