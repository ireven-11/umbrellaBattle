#pragma once

class StandbyUI
{
public:
	StandbyUI(const char* fontName);
	~StandbyUI();

	void update(bool isjoiningPlayer[], const int max_player_number);

private:
	void playerJoin(bool isjoiningPlayer[], const int max_player_number);

	int	fontHandle_;		//フォントハンドル
	int	fontHandleSize100_;	//フォントハンドル

	const VECTOR	player_number_position	= VGet(270, 870, 0);
	const int		player_number_gap		= 400;
	const VECTOR	wait_or_join_position	= VGet(245, 940, 0);
	const VECTOR	join_player_position	= VGet(700, 70, 0);
};