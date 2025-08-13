#include"DxLib.h"
#include"DrawBrinkStringToHandle.h"

/// <summary>
/// 文字点滅描画関数(フォント指定可能)
/// </summary>
/// <param name="position">描画座標</param>
/// <param name="text">描画したいテキスト</param>
/// <param name="color">文字の色</param>
/// <param name="fontHandle">フォントハンドル</param>
/// <param name="brinkSpeed">点滅スピード(デフォルトは2、0を入れると点滅しない)</param>
void DrawBrinkStringToHandle(VECTOR position, const char* text, int color, int fontHandle, unsigned short brinkSpeed)
{
	//点滅スピードが0だったら点滅しない
	if (brinkSpeed == 0)
	{
		DrawStringToHandle(position.x, position.y, text, color, fontHandle);
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
			DrawStringToHandle(position.x, position.y, text, color, fontHandle);
		}
	}
}