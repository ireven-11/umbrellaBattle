#include"DxLib.h"
#include<math.h>
#include"calculateDistance.h"
#include"charaBase.h"
#include"routine.h"
#include"cpuBrain.h"

CPUBrain::CPUBrain()
{
	isTarget_		= true;
	randomTarget_	= 0;
	distance_		= 0.0f;
	canCharge_	= false;
	actionState_	= chaseState_();
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine)
{
	decideTarget(charaBase);

	distance_ = CalculateDistance<float>(charaBase->Getposition_(), routine->players[randomTarget_ - 1]->Getposition_());

	//�L��������@�o�Ȃ��������^�[�Q�b�g�ɂ���
	if (routine->players[randomTarget_ - 1]->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(routine->players[randomTarget_ - 1]->Getstate_()))
	{
		decideNextAction(charaBase, routine);
	}
	else
	{
		isTarget_ = true;
	}


	actionState_->update(charaBase);
}

/// <summary>
/// �^�[�Q�b�g������
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void CPUBrain::decideTarget(CharaBase* charaBase)
{
	if (isTarget_)
	{
		while (true)
		{
			randomTarget_ = GetRand(3) + 1;

			if (randomTarget_ != charaBase->GetcontrolerNumber_())
			{
				isTarget_ = false;
				break;
			}
		}
	}
}

/// <summary>
/// ���̍s��������
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
/// <param name="routine">���[�`���N���X</param>
void CPUBrain::decideNextAction(CharaBase* charaBase, Routine* routine)
{
	//�����ɂ���Ăǂ̍s�������邩�ς���
	if (distance_ < 5)
	{
		charaBase->input.Buttons[1] = 128;
		//actionState_ = attackState_();
	}
	else if (distance_ > 15 && charaBase->GettackleCount_() <= charaBase->Getmax_tackle_count() && canCharge_)
	{
		if (charaBase->GettackleCount_() == charaBase->Getmax_tackle_count())
		{
			canCharge_ = false;
		}

		charaBase->input.Buttons[0] = 128;
	}
	else
	{
		if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
		{
			charaBase->input.X = 635;
		}
		else if(charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
		{
			charaBase->input.X = -745;
		}
		if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
		{
			charaBase->input.Y = -830;
		}
		else if(charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
		{
			charaBase->input.Y = 750;
		}
	}

	if (charaBase->GettackleCount_() == 0)
	{
		canCharge_ = true;
	}
}