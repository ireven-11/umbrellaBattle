#pragma once
#include"charaBase.h"

class CharaState
{
public:
	virtual ~CharaState(){}

	virtual void changeState(shared_ptr<CharaBase> charaBase){}
	virtual void update(shared_ptr<CharaBase> charaBase){}
};