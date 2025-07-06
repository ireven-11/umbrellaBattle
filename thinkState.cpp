#include"DxLib.h"
#include"charaBase.h"
#include"thinkState.h"
#include"calculateDistance.h"

namespace ActionState
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ThinkState::ThinkState()
	{
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	ThinkState::~ThinkState()
	{
	}

	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void ThinkState::changeState(CharaBase* charaBase)
	{

	}

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="charaBase">キャラの親クラス</param>
	void ThinkState::update(CharaBase* charaBase)
	{
		int tempRandom = GetRand(3) + 1;
		CalculateDistance<float>(charaBase->Getposition_(), charaBase->Getposition_());
	}
}