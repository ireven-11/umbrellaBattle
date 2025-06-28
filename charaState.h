#pragma once
#include"charaBase.h"

namespace StateMachine
{
	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void changeState(shared_ptr<IState> state) = 0;
		virtual void update(CharaBase *charaBase) = 0;
	};
}


namespace PlayerState
{
	class PlayerIdleState : public StateMachine::IState
	{
	public:
		void changeState(shared_ptr<IState> state)
		{
			// ÀÛ‚Ìˆ—
		}

		void update(CharaBase *charaBase) {}
	};

	class PlayerWalkState : public StateMachine::IState
	{
	public:
		void changeState(shared_ptr<IState> state)
		{
			// ÀÛ‚Ìˆ—
		}

		void update(CharaBase *charaBase) {}
	};
}