#include"DxLib.h"
#include"charaBase.h"
#include"thinkState.h"
#include"calculateDistance.h"

namespace ActionState
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ThinkState::ThinkState()
	{
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	ThinkState::~ThinkState()
	{
	}

	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <param name="charaBase">�L�����̐e�N���X</param>
	void ThinkState::changeState(CharaBase* charaBase)
	{

	}

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="charaBase">�L�����̐e�N���X</param>
	void ThinkState::update(CharaBase* charaBase)
	{
		int tempRandom = GetRand(3) + 1;
		CalculateDistance<float>(charaBase->Getposition_(), charaBase->Getposition_());
	}
}