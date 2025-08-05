#include"DxLib.h"
#include"charaBase.h"
#include"fanState.h"

namespace CharaState
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FanState::FanState()
	{

	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	FanState::~FanState()
	{

	}

	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void FanState::changeState(CharaBase* charaBase)
	{
	}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void FanState::update(CharaBase* charaBase)
	{
		charaBase->wind();
		charaBase->moveFan();
		charaBase->respawn();
		changeState(charaBase);
	}
}