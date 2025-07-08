#pragma once
#include"IState.h"

namespace ActionState
{
	class WindState
	{
	public:
		WindState();
		~WindState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);
	private:

	};
}