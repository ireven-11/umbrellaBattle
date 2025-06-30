#include"DxLib.h"
#include"charaBase.h"
#include"CharaState.h"
using namespace CharaState;

/// <summary>
/// �R���X�g���N�^
/// </summary>
OpenState::OpenState()
{ 
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OpenState::~OpenState()
{
}

/// <summary>
/// ��ԕω�/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void OpenState::changeState(CharaBase* charaBase)
{
	charaBase->changeOpenToClose();
	charaBase->transformFan();
}

/// <summary>
/// OPEN��Ԃōs���������e
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void OpenState::update(CharaBase* charaBase)
{
	charaBase->move();
	charaBase->swing();
	charaBase->tackle();
	changeState(charaBase);
}