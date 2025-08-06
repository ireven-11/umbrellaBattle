#include"DxLib.h"
#include"charaBase.h"
#include"openState.h"

namespace CharaState
{
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
	/// 状態変化/// 
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void OpenState::changeState(CharaBase* charaBase)
	{
		charaBase->changeOpenToClose();
		charaBase->changeTrumpet();
		charaBase->transformFan();
	}

	/// <summary>
	/// OPEN状態で行う処理内容
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void OpenState::update(CharaBase* charaBase)
	{
		charaBase->move();
		charaBase->swing();
		charaBase->tackle();
		charaBase->collisionRotation();
		changeState(charaBase);
	}
}