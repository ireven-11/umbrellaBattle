#include"DxLib.h"
#include"charaBase.h"
#include"CharaState.h"
using namespace CharaState;

/// @brief コンストラクタ
CloseState::CloseState()
{

}

/// @brief デストラクタ
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