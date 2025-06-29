#include"DxLib.h"
#include"CharaState.h"
using namespace CharaState;

/// <summary>
/// コンストラクタ
/// </summary>
OpenState::OpenState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
OpenState::~OpenState()
{
}

/// <summary>
/// 状態変化/// </summary>
/// <param name="charaBase">キャラの親クラス</param>
void OpenState::changeState(shared_ptr<IState> state, shared_ptr<CharaBase> charaBase)
{
	charaBase->changeOpenToClose();
	charaBase->transformFan();
}

/// <summary>
/// OPEN状態で行う処理内容
/// </summary>
/// <param name="charaBase"></param>
void OpenState::update(shared_ptr<CharaBase> charaBase)
{
	charaBase->move();
	charaBase->swing();
	charaBase->tackle();
}