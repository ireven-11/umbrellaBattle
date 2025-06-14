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
	sceneType_ = PLAY;
}

/// <summary>
/// �X�^���o�C��ʂ�
/// </summary>
void SceneManager::proceedStandby()
{
	sceneType_ = STANDBY;
}

/// <summary>
/// �v���C��ʂ�
/// </summary>
void SceneManager::proceedPlay()
{
	sceneType_ = PLAY;
}

/// <summary>
/// ���U���g��ʂ�
/// </summary>
void SceneManager::proceedResult()
{
	sceneType_ = RESULT;
}

/// <summary>
/// �^�C�g����ʂ�
/// </summary>
void SceneManager::proceedTitle()
{
	sceneType_ = TITLE;
}