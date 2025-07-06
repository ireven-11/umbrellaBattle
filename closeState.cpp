#include"DxLib.h"
#include"charaBase.h"
#include"closeState.h"

namespace CharaState
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CloseState::CloseState()
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	CloseState::~CloseState()
	{

	}

	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void CloseState::changeState(CharaBase* charaBase)
	{
		charaBase->changeCloseToOpen();
		charaBase->transformFan();
	}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void CloseState::update(CharaBase* charaBase)
	{
		charaBase->move();
		changeState(charaBase);
	}
}