#include"DxLib.h"
#include"DrawExtendBrinkGraph.h"

void DrawExtendBrinkGraph(float positionX, float positionY, float widht, float height, int graphHandle, bool isTrans, unsigned short brinkSpeed)
{
	//�_�ŃX�s�[�h��0��������_�ł��Ȃ�
	if (brinkSpeed == 0)
	{
		DrawExtendGraph(positionX, positionY, positionX + widht, positionY + height, graphHandle, isTrans);
	}
	else
	{
		//�_�ŃJ�E���g
		static int brinkCount;
		brinkCount += 1 * brinkSpeed;
		if (brinkCount > 100)
		{
			brinkCount = 0;
		}

		//�_�ŃJ�E���g�����l�ȉ��̂Ƃ������`�悷��
		if (brinkCount > 100 / brinkSpeed)
		{
			DrawExtendGraph(positionX, positionY, positionX + widht, positionY + height, graphHandle, isTrans);
		}
	}
}