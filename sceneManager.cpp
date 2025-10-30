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
	//コントローラー(D)用構造体変数
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//コントローラーを使えるようにする
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input1);
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input2);
	GetJoypadDirectInputState(DX_INPUT_PAD3, &input3);
	GetJoypadDirectInputState(DX_INPUT_PAD4, &input4);

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE ||
		input1.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_360 ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_ONE ||
		input2.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_360 ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_ONE || 
		input3.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_360 ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_ONE || 
		input4.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_360 ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_ONE)
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
	//コントローラー(D)用構造体変数
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//コントローラーを使えるようにする
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input1);
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input2);
	GetJoypadDirectInputState(DX_INPUT_PAD3, &input3);
	GetJoypadDirectInputState(DX_INPUT_PAD4, &input4);

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE ||
		input1.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_360 ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_ONE ||
		input2.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_360 ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_ONE ||
		input3.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_360 ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_ONE ||
		input4.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_360 ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_ONE)
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
	//コントローラー(D)用構造体変数
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//コントローラーを使えるようにする
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input1);
	GetJoypadDirectInputState(DX_INPUT_PAD2, &input2);
	GetJoypadDirectInputState(DX_INPUT_PAD3, &input3);
	GetJoypadDirectInputState(DX_INPUT_PAD4, &input4);

	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE ||
		input1.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_360 ||
		input1.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD1) == DX_PADTYPE_XBOX_ONE ||
		input2.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_360 ||
		input2.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD2) == DX_PADTYPE_XBOX_ONE ||
		input3.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_360 ||
		input3.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD3) == DX_PADTYPE_XBOX_ONE ||
		input4.Buttons[12] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_360 ||
		input4.Buttons[7] > 0 && GetJoypadType(DX_INPUT_PAD4) == DX_PADTYPE_XBOX_ONE)
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