#include"DxLib.h"
#include"sceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
{
	reset();
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// ���Z�b�g
/// </summary>
void SceneManager::reset()
{
	sceneType_		= TITLE;
	isPrevButton_	= false;
}

/// <summary>
/// �X�^���o�C��ʂ�
/// </summary>
bool SceneManager::proceedStandby()
{
	//�R���g���[���[(D)�p�\���̕ϐ�
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//�R���g���[���[���g����悤�ɂ���
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
/// �v���C��ʂ�
/// </summary>
bool SceneManager::proceedPlay()
{
	//�R���g���[���[(D)�p�\���̕ϐ�
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//�R���g���[���[���g����悤�ɂ���
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
/// ���U���g��ʂ�
/// </summary>
bool SceneManager::proceedResult()
{
	sceneType_ = RESULT;

	return true;
}

/// <summary>
/// �^�C�g����ʂ�
/// </summary>
bool SceneManager::proceedTitle()
{
	//�R���g���[���[(D)�p�\���̕ϐ�
	DINPUT_JOYSTATE input1;
	DINPUT_JOYSTATE input2;
	DINPUT_JOYSTATE input3;
	DINPUT_JOYSTATE input4;

	//�R���g���[���[���g����悤�ɂ���
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