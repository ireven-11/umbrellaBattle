#include"DxLib.h"
#include"charaBase.h"
#include"CharaState.h"
using namespace CharaState;

FanState::FanState()
{

}

FanState::~FanState()
{

}

void FanState::changeState(CharaBase* charaBase)
{
	charaBase->wind();
}

void FanState::update(CharaBase* charaBase)
{
	changeState(charaBase);
}