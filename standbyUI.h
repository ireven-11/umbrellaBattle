#pragma once

class StandbyUI
{
public:
	StandbyUI(const char* fontName);
	~StandbyUI();

	void update(bool isjoiningPlayer[], const int max_player_number);

private:
	void playerJoin(bool isjoiningPlayer[], const int max_player_number);
	void explaneRule();

	int	fontHandle_;		//フォントハンドル
	int	fontHandleSize100_;	//フォントハンドル100
	int fontHandleSize150_;	//フォントハンドル150
	int screenHandle_;		//スクリーンハンドル
	int movieExplane_;		//説明動画

	const VECTOR	player_number_position	= VGet(270, 870, 0);
	const int		player_number_gap		= 400;
	const VECTOR	wait_or_join_position	= VGet(245, 940, 0);
	const VECTOR	join_player_position	= VGet(700, 750, 0);
	const VECTOR	game_start_position		= VGet(565, 150, 0);
	const VECTOR	practice_position		= VGet(775, 15, 0);
	const VECTOR	movie_explane_pos		= VGet(1350, 70, 0);
	const int		movie_explane_widht		= 500;
	const int		movie_explane_height	= 300;
};