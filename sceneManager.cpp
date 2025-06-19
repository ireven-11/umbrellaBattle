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
	sceneType_ = STANDBY;
}

/// <summary>
/// スタンバイ画面へ
/// </summary>
void SceneManager::proceedStandby()
{
	sceneType_ = STANDBY;
}

/// <summary>
/// プレイ画面へ
/// </summary>
void SceneManager::proceedPlay()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == true)
	{
		sceneType_ = PLAY;
	}
}

/// <summary>
/// リザルト画面へ
/// </summary>
void SceneManager::proceedResult()
{
	sceneType_ = RESULT;
}

/// <summary>
/// タイトル画面へ
/// </summary>
void SceneManager::proceedTitle()
{
	sceneType_ = TITLE;
}