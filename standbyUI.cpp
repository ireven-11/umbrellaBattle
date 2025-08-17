#include"DxLib.h"
#include"standbyUI.h"
#include"DrawBrinkStringToHandle.h"

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

	DrawStringToHandle(game_start_position.x, game_start_position.y, "Enterでゲームスタート", GetColor(255, 255, 255), fontHandle_);
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
		if (!isjoiningPlayer[i])
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "待機中...", GetColor(255, 255, 255), fontHandle_);
			DrawFormatStringToHandle(player_number_position.x + player_number_gap * i, player_number_position.y, GetColor(255, 255, 255), fontHandle_, "%dP", i + 1);
		}
	}

	DrawBrinkStringToHandle(join_player_position, "Aボタンで参加！", GetColor(255, 50, 0), fontHandleSize100_);
}