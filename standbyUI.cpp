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
	fontHandleSize150_	= CreateFontToHandle(fontName, 150, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	screenHandle_		= MakeScreen(1920, 1080);
	movieExplane_		= LoadGraph("movie/explaneRule.mp4");
}

/// <summary>
/// デストラクタ
/// </summary>
StandbyUI::~StandbyUI()
{
	DeleteFontToHandle(fontHandle_);
	DeleteFontToHandle(fontHandleSize100_);
	DeleteFontToHandle(fontHandleSize150_);
	DeleteGraph(screenHandle_);
}

void StandbyUI::update(bool isjoiningPlayer[], const int max_player_number)
{
	playerJoin(isjoiningPlayer, max_player_number);

	explaneRule();

	DrawStringToHandle(practice_position.x, practice_position.y, "練習場", GetColor(255, 255, 50), fontHandleSize150_);
	DrawStringToHandle(game_start_position.x, game_start_position.y, "Enterでゲームスタート", GetColor(255, 255, 255), fontHandleSize100_);
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

void StandbyUI::explaneRule()
{
	SetDrawScreen(screenHandle_);
	PlayMovieToGraph(movieExplane_, DX_PLAYTYPE_LOOP);
	DrawExtendGraph(movie_explane_pos.x, movie_explane_pos.y, movie_explane_pos.x + movie_explane_widht, movie_explane_pos.y + movie_explane_height, movieExplane_, TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawBox(movie_explane_pos.x - 5, movie_explane_pos.y -5 , movie_explane_pos.x + movie_explane_widht + 5, movie_explane_pos.y + movie_explane_height + 5, GetColor(255,255,255), TRUE);
	DrawExtendGraph(movie_explane_pos.x, movie_explane_pos.y, movie_explane_pos.x + movie_explane_widht, movie_explane_pos.y + movie_explane_height, movieExplane_, TRUE);
}