#pragma once


namespace CharaState
{
	class HitStopState : public StateMachine::IState
	{
	public:
		HitStopState();
		~HitStopState();
		void changeState(CharaBase* charaBase);
		void update(CharaBase* charaBase);

	private:
		
	};
}