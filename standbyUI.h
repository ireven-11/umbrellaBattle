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

	int	fontHandle_;		//�t�H���g�n���h��
	int	fontHandleSize100_;	//�t�H���g�n���h��100
	int fontHandleSize150_;	//�t�H���g�n���h��150
	int screenHandle_;		//�X�N���[���n���h��

	const VECTOR	player_number_position	= VGet(270, 870, 0);
	const int		player_number_gap		= 400;
	const VECTOR	wait_or_join_position	= VGet(245, 940, 0);
	const VECTOR	join_player_position	= VGet(700, 750, 0);
	const VECTOR	game_start_position		= VGet(565, 150, 0);
	const VECTOR	practice_position		= VGet(775, 15, 0);
};