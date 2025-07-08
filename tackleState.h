#pragma once
#include"IState.h"

namespace ActionState
{
	class TackleState
	{
	public:
		TackleState();
		~TackleState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	private:

	};
}