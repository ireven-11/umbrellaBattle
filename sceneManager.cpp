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
	sceneType_ = PLAY;
}

void SceneManager::proceedStandby()
{
	sceneType_ = STANDBY;
}

void SceneManager::proceedPlay()
{
	sceneType_ = PLAY;
}

void SceneManager::proceedResult()
{
	sceneType_ = RESULT;
}

void SceneManager::proceedTitle()
{
	sceneType_ = TITLE;
}