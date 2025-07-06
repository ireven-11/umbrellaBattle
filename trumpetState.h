#pragma once
#include"IState.h"

namespace CharaState
{
	//ƒ‰ƒbƒpó‘Ô
	class TrumpetState : public StateMachine::IState
	{
	public:
		TrumpetState();
		~TrumpetState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	};
}