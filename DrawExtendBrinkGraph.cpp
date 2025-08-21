#include"DxLib.h"
#include"DrawExtendBrinkGraph.h"

void DrawExtendBrinkGraph(float positionX, float positionY, float widht, float height, int graphHandle, bool isTrans, unsigned short brinkSpeed)
{
	//点滅スピードが0だったら点滅しない
	if (brinkSpeed == 0)
	{
		DrawExtendGraph(positionX, positionY, positionX + widht, positionY + height, graphHandle, isTrans);
	}
	else
	{
		//点滅カウント
		static int brinkCount;
		brinkCount += 1 * brinkSpeed;
		if (brinkCount > 100)
		{
			brinkCount = 0;
		}

		//点滅カウントが一定値以下のときだけ描画する
		if (brinkCount > 100 / brinkSpeed)
		{
			DrawExtendGraph(positionX, positionY, positionX + widht, positionY + height, graphHandle, isTrans);
		}
	}
}