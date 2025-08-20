#pragma once
#include<memory>
class CharaBase;

class PlayUI
{
public:
	PlayUI(const char* fontName);
	~PlayUI();

	void update(std::shared_ptr<CharaBase> chara, int playerNumber);

private:
	void playerUI(std::shared_ptr<CharaBase> chara, int playerNumber);
	void buttonUI();

	int		fontHandle_;		//フォントハンドル
	int		umbrella1_;			//傘1
	int		umbrella2_;			//傘2
	int		umbrella3_;			//傘3
	int		umbrella4_;			//傘4
	int		hpEmpty_;			//hp空
	int		hp_;				//hp
	VECTOR	hpPosition_;		//hp座標
	VECTOR	umbrellaPosition_;	//傘座標
	VECTOR	hpEmptyPosition_;	//hp空座標
	int		AbuttonUI_;			//Aボタンui
	int		LstickUI_;			//LスティックUI
	int		LTbuttonUI_;		//LTボタンUI
	int		RTbuttonUI_;		//RTボタンUI
	int		fontHandleSize60_;	//60サイズのフォント
	int		trumpet_[4];		//ラッパがさ画像
	int		fontHandleSize30_;	//フォントサイズ30
	
	const int		umbrella_width			= 150;
	const int		umbrella_height			= 150;
	const VECTOR	umbrella_init_position	= VGet(-160.0f, 850.0f, 0.0f);
	const int		adjust_umbrella_x		= 400;
	const VECTOR	hp_empty_init_position	= VGet(-180.0f, 975.0f, 0.0f);
	const int		hp_empty_width			= 210;
	const int		hp_empty_height			= 50;
	const int		adjust_hp_empty_x		= 400;
	const VECTOR	hp__init_position		= VGet(-130.0f, 987.0f, 0.0f);
	const int		hp__width				= 150;
	const int		hp__height				= 25;
	const int		adjust_hp__x			= 400;
	const VECTOR	A_ui_position			= VGet(30, 30, 0);
	const VECTOR	Lstick_ui_position		= VGet(30, 110, 0);
	const VECTOR	LT_ui_position			= VGet(30, 180, 0);
	const VECTOR	RT_ui_position			= VGet(35, 260, 0);
	const float		button_ui_width			= 60;
	const float		button_ui_height		= 60;
	const VECTOR	action_text_position	= VGet(105, 25, 0);
	const VECTOR	move_text_position		= VGet(105, 105, 0);
	const VECTOR	left_turn_text_position	= VGet(105, 175, 0);
	const VECTOR	right_turn_text_position= VGet(105, 255, 0);
};