#include"DxLib.h"
#include"standbyUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
StandbyUI::StandbyUI(const char* fontName)
{
	fontHandle_			= CreateFontToHandle(fontName, 50, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize100_	= CreateFontToHandle(fontName, 90, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

/// <summary>
/// デストラクタ
/// </summary>
StandbyUI::~StandbyUI()
{
}

void StandbyUI::update(bool isjoiningPlayer[], const int max_player_number)
{
	playerJoin(isjoiningPlayer, max_player_number);


	DrawStringToHandle(900, 800, "EnterKeyでゲームスタート", GetColor(255, 255, 255), fontHandle_);
}

/// <summary>
/// 文字点滅描画関数(フォント指定可能)
/// </summary>
/// <param name="position">描画座標</param>
/// <param name="text">描画したいテキスト</param>
/// <param name="color">文字の色</param>
/// <param name="fontHandle">フォントハンドル</param>
/// <param name="brinkSpeed">点滅スピード(デフォルトは2、0を入れると点滅しない)</param>
void DrawBrinkStringToHandle(VECTOR position, const char* text, int color, int fontHandle = 0, unsigned short brinkSpeed = 2)
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

/// <summary>
/// プレイヤーが参加するui
/// </summary>
/// <param name="isjoiningPlayer"></param>
/// <param name="max_player_number"></param>
void StandbyUI::playerJoin(bool isjoiningPlayer[], const int max_player_number)
{
	for (int i = 0; i < max_player_number; i++)
	{
		DrawFormatStringToHandle(player_number_position.x + player_number_gap * i, player_number_position.y, GetColor(255, 255, 255), fontHandle_, "%dP", i + 1);
		if (isjoiningPlayer[i])
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "参加！", GetColor(255, 255, 255), fontHandle_);
		}
		else
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "待機中...", GetColor(255, 255, 255), fontHandle_);
		}
	}

	DrawBrinkStringToHandle(join_player_position, "Aボタンで参加！", GetColor(255, 50, 0), fontHandleSize100_);
	//DrawStringToHandle(join_player_position.x, join_player_position.y, "Aボタンで参加！", GetColor(255, 50, 0), fontHandleSize100_);
}