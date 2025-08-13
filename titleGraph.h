#pragma once

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();

	void update();

private:
	void reset();

	int		umbrella1Handle_;		//P‚P
	int		umbrella2Handle_;		//P‚Q
	int		umbrella3Handle_;		//P3
	int		umbrella4Handle_;		//P‚S
	int		hitHandle_[18];			//ƒqƒbƒg
	VECTOR	umbrellaPosition_[4];	//PÀ•W
	VECTOR	hitPosition_;			//ƒqƒbƒgÀ•W
	
	const short hit_div_number	= 18;	//ƒqƒbƒg•ªŠ„”
	const short hit_div_X		= 9;	//ƒqƒbƒg•ªŠ„”x
	const short hit_div_y		= 2;	//ƒqƒbƒg•ªŠ„”y
	const int	hit_size_x		= 516;	//‰æ‘œ‚Ì‘å‚«‚³x
	const int	hit_size_y		= 528;	//‰æ‘œ‚Ì‘å‚«‚³y
	const int	hit_width		= 100;	//ƒqƒbƒg‚Ì•
	const int	hit_height		= 100;	//ƒqƒbƒg‚Ìt‚‚³
	const int	hit_switch_time = 2;	//ƒqƒbƒg•Ï‚í‚éŠÔ

	const int		umbrella_width	= 700;	//P•
	const int		umbrella_height	= 600;	//‚‚³
	const VECTOR	umbrella1_init_position = VGet(400, 60, 0);	//‚©‚³‚µ‚å‚«‚´‚Ğ‚å‚¤
	const VECTOR	umbrella2_init_position = VGet(800, 60, 0);	//‚©‚³‚µ‚å‚«‚´‚Ğ‚å‚¤
}; 