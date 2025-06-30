#include"DxLib.h"
#include"charaBase.h"
#include"CharaState.h"
using namespace CharaState;

/// @brief �R���X�g���N�^
CloseState::CloseState()
{

}

/// @brief �f�X�g���N�^
CloseState::~CloseState()
{

}

void CloseState::changeState(CharaBase* charaBase)
{
	charaBase->changeCloseToOpen();
	charaBase->transformFan();
}

void CloseState::update(CharaBase* charaBase)
{
	charaBase->move();
	changeState(charaBase);
}