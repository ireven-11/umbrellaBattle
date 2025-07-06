#include"DxLib.h"
#include"cpuBrain.h"
#include"calculateDistance.h"
#include"charaBase.h"
#include"routine.h"

class CharaBase;

CPUBrain::CPUBrain()
{
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine)
{
	int tempRandom;
	while (true)
	{
		tempRandom = GetRand(3) + 1;

		if (tempRandom != charaBase->GetcontrolerNumber_())
		{
			break;
		}
	}

	float distance = CalculateDistance<float>(charaBase->Getposition_(), routine->players[tempRandom]->Getposition_());

	if (distance < 1)
	{

	}
}