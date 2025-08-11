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
	int		fontHandle_;		//�t�H���g�n���h��
	int		umbrella1_;			//�P1
	int		umbrella2_;			//�P2
	int		umbrella3_;			//�P3
	int		umbrella4_;			//�P4
	int		hpEmpty_;			//hp��
	int		hp_;				//hp
	VECTOR	hpPosition_;		//hp���W
	VECTOR	umbrellaPosition_;	//�P���W
	VECTOR	hpEmptyPosition_;	//hp����W

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
};