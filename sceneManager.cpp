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
void SceneManager::proceedStandby()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
	{
		if (!isPrevButton_)
		{
			sceneType_ = STANDBY;
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_	= false;
	}
}

/// <summary>
/// �v���C��ʂ�
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
void SceneManager::proceedTitle()
{
	sceneType_ = TITLE;
}