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