#include"DxLib.h"
#include"charaBase.h"
#include"CharaState.h"
using namespace CharaState;

/// <summary>
/// �R���X�g���N�^
/// </summary>
FanState::FanState()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FanState::~FanState()
{

}

/// <summary>
/// �X�e�[�g�ύX
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void FanState::changeState(CharaBase* charaBase)
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void FanState::update(CharaBase* charaBase)
{
	charaBase->wind();
	charaBase->moveFan();
	changeState(charaBase);
}