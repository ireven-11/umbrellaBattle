#include"DxLib.h"
#include"sceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
{
	reset();
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// リセット
/// </summary>
void SceneManager::reset()
{
	sceneType_		= TITLE;
	isPrevButton_	= false;
}

/// <summary>
/// スタンバイ画面へ
/// </summary>
bool SceneManager::proceedStandby()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (!isPrevButton_)
		{
			sceneType_ = STANDBY;
			return true;
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_	= false;
	}

	return false;
}

/// <summary>
/// プレイ画面へ
/// </summary>
bool SceneManager::proceedPlay()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (!isPrevButton_)
		{
			sceneType_ = PLAY;
			return true;
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_ = false;
	}

	return false;
}

/// <summary>
/// リザルト画面へ
/// </summary>
bool SceneManager::proceedResult()
{
	sceneType_ = RESULT;

	return true;
}

/// <summary>
/// タイトル画面へ
/// </summary>
bool SceneManager::proceedTitle()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (!isPrevButton_)
		{
			sceneType_ = TITLE;
			return true;
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_ = false;
	}

	return false;
}