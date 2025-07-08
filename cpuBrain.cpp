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
	canCharge_		= true;
	doActionRandom_ = 0;
	dicideActionCount_ = 0;
	actionState_	= chaseState_();
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine)
{
	decideTarget(charaBase);

	distance_ = CalculateDistance<float>(charaBase->Getposition_(), routine->players[randomTarget_ - 1]->Getposition_());

	//�^�[�Q�b�g����@�łȂ����������̍s���Ɉڂ�
	if (routine->players[randomTarget_ - 1]->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(routine->players[randomTarget_ - 1]->Getstate_()))
	{
		decideNextAction(charaBase, routine);
	}
	else
	{
		//�^�[�Q�b�g���Č���
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
	if (distance_ < 3)
	{
		//int doActionRandom_ = GetRand(100);

		if (doActionRandom_ > 50)
		{
			//actionState_ = swingState_();
			charaBase->input.Buttons[1] = 128;
		}
		else
		{
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = -745;
			}
			else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = 635;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = 750;
			}
			else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = -830;
			}
		}
	}
	else if (distance_ > 20 && charaBase->GettackleCount_() <= charaBase->Getmax_tackle_count() && canCharge_)
	{
		doActionRandom_ = GetRand(50);
		if (charaBase->GettackleCount_() == charaBase->Getmax_tackle_count() - doActionRandom_)
		{
			canCharge_ = false;
		}

		//if (random > 30)
		{
			charaBase->input.Buttons[0] = 128;
			VECTOR stickVector = VGet(0.0f, 0.0f, 0.0f);
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				//charaBase->input.X = 635;
				stickVector.x += 635.0f;
			}
			else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				//charaBase->input.X = -745;
				stickVector.x += -745.0f;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				//charaBase->input.Y = -830;
				stickVector.y += -830.0f;
			}
			else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				//charaBase->input.Y = 750;
				stickVector.y += 750.0f;
			}

			double targetAngle = atan2(static_cast<double>(routine->players[randomTarget_ - 1]->Getposition_().x - charaBase->Getposition_().x),
				static_cast<double>(routine->players[randomTarget_ - 1]->Getposition_().z - charaBase->Getposition_().z));
			MATRIX rotationMatrix = MGetRotY(targetAngle);
			stickVector = VTransform(stickVector, rotationMatrix);

			charaBase->input.X = stickVector.x;
			charaBase->input.Y = stickVector.y;
		}
	}
	else
	{
		if (dicideActionCount_ == 0)
		{
			doActionRandom_ = GetRand(100);
		}
		else if (dicideActionCount_ > 200)
		{
			dicideActionCount_ = 0;
		}

		dicideActionCount_++;


		if (doActionRandom_ > 30)
		{
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = 635;
			}
			else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = -745;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = -830;
			}
			else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = 750;
			}
		}
		else
		{
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = -745;
			}
			else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = 635;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = 750;
			}
			else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = -830;
			}
		}

		//actionState_ = chaseState_();
	}

	if (charaBase->GettackleCount_() == 0)
	{
		canCharge_ = true;
	}
}