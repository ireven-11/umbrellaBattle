#pragma once
#include"charaState.h"

class OpenState:public StateMachine::IState
{
public:
	OpenState();
	~OpenState();

	virtual void changeState(shared_ptr<CharaBase> charaBase);
	virtual void update(shared_ptr<CharaBase> charaBase);
private:

};