#include"DxLib.h"
#include"charaBase.h"
#include"closeState.h"

namespace CharaState
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CloseState::CloseState()
	{

	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	CloseState::~CloseState()
	{

	}

	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <param name="charaBase">�L�����̐e�N���X</param>
	void CloseState::changeState(CharaBase* charaBase)
	{
		charaBase->changeCloseToOpen();
		charaBase->transformFan();
	}

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="charaBase">�L�����̐e�N���X</param>
	void CloseState::update(CharaBase* charaBase)
	{
		charaBase->move();
		changeState(charaBase);
	}
}