#include"DxLib.h"
#include"standbyUI.h"
#include"DrawBrinkStringToHandle.h"
#include"PlayTransparentMovie.h"
#include<cmath>
#include<algorithm>

/// <summary>
/// コンストラクタ
/// </summary>
StandbyUI::StandbyUI(const char* fontName)
{
	fontHandle_					= CreateFontToHandle(fontName, 50, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize100_			= CreateFontToHandle(fontName, 90, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize150_			= CreateFontToHandle(fontName, 150, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	screenHandle_				= MakeScreen(1920, 1080);
	movieExplane_				= LoadGraph("movie/explaneRule.mp4");
	concentrationlLinesMovie_	= LoadGraph("movie/concentrationlLines.mp4");
	transparentScreen_			= MakeScreen(1920, 1080, TRUE);
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
	DeleteGraph(transparentScreen_);
	DeleteGraph(concentrationlLinesMovie_);
}

void StandbyUI::init()
{
	SeekMovieToGraph(movieExplane_, 0);
}

float UpDownPositionY(float positionY, const float amplitude = 1.0f, const float period = 1.0f)
{
	if (period == 0.0f) return -1.0f;

	static	float rad		= 0.0f;
	const	float add_rad	= 10.0f;
	rad						+= add_rad;
	if (rad > 360.0f)
	{
		rad = 0.0f;
	}

	positionY += sinf(rad / period) * amplitude;
	return positionY;
}

void StandbyUI::update(bool isjoiningPlayer[], const int max_player_number)
{
	playerJoin(isjoiningPlayer, max_player_number);

	explaneRule();

	DrawStringToHandle(practice_position.x, UpDownPositionY(practice_position.y, 10.0f, 100.0f), "練習場", GetColor(255, 255, 50), fontHandleSize150_);
	
	for (auto i = 0; i < max_player_number; i++)
	{
		//誰も参加してなかったら描画しない
		if (!isjoiningPlayer[i]) continue;

		DrawStringToHandle(game_start_position.x, game_start_position.y, "Startでバトル開始！", GetColor(255, 255, 255), fontHandleSize100_);
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
		if (!isjoiningPlayer[i])
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "待機中...", GetColor(255, 255, 255), fontHandle_);
			DrawFormatStringToHandle(player_number_position.x + player_number_gap * i, player_number_position.y, GetColor(255, 255, 255), fontHandle_, "%dP", i + 1);
		}
	}

	//全員参加してたら描画しない
	for (int i = 0; i < max_player_number; i++)
	{
		if (isjoiningPlayer[i]) continue;

		DrawBrinkStringToHandle(join_player_position, "Aボタンで参加！", GetColor(255, 50, 0), fontHandleSize100_);
	}
}

void StandbyUI::explaneRule()
{
	SetDrawScreen(screenHandle_);
	PlayMovieToGraph(movieExplane_, DX_PLAYTYPE_LOOP);
	DrawExtendGraph(movie_explane_pos.x, movie_explane_pos.y, movie_explane_pos.x + movie_explane_widht, movie_explane_pos.y + movie_explane_height, movieExplane_, TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawBox(movie_explane_pos.x - 5, movie_explane_pos.y - 5, movie_explane_pos.x + movie_explane_widht + 5, movie_explane_pos.y + movie_explane_height + 5, GetColor(255,255,255), TRUE);
	DrawExtendGraph(movie_explane_pos.x, movie_explane_pos.y, movie_explane_pos.x + movie_explane_widht, movie_explane_pos.y + movie_explane_height, movieExplane_, TRUE);
	PlayTransparentMovie(concentrationlLinesMovie_, transparentScreen_, 0, movie_explane_widht * extend_width_height, movie_explane_height * extend_width_height,
		VGet(movie_explane_pos.x - 5 * adjsut_concentrationl_lines_pos.x, movie_explane_pos.y - 5 * adjsut_concentrationl_lines_pos.y, 0));
}