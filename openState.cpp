#include"DxLib.h"
#include"openState.h"

OpenState::OpenState()
{
}

OpenState::~OpenState()
{
}

void OpenState::changeState(shared_ptr<CharaBase> charaBase)
{
	charaBase->changeOpenToClose();
	charaBase->transformFan();
}

void OpenState::update(shared_ptr<CharaBase> charaBase)
{

}