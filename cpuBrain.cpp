#include"DxLib.h"
#include"cpuBrain.h"
#include"calculateDistance.h"
#include"charaBase.h"
#include"routine.h"

class CharaBase;

CPUBrain::CPUBrain()
{
	isTarget_ = true;
	randomTarget_ = 0;
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine)
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

	float distance = CalculateDistance<float>(charaBase->Getposition_(), routine->players[randomTarget_ - 1]->Getposition_());

	//キャラが扇風機出ない時だけターゲットにする
	if (routine->players[randomTarget_ - 1]->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(routine->players[randomTarget_ - 1]->Getstate_()))
	{
		//距離によってどの行動をするか変える
		if (distance < 5)
		{
			charaBase->input.Buttons[1] = 1;
		}
		else
		{
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = -100;
			}
			else
			{
				charaBase->input.X = +100;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = -100;
			}
			else
			{
				charaBase->input.Y = +100;
			}
		}
	}
	else
	{
		isTarget_ = true;
	}
}