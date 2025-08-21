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
	VECTOR	umbrellaPosition_[4];	//PÀ•W
	
	const int		umbrella_width	= 500;	//P•
	const int		umbrella_height	= 400;	//‚‚³
	const VECTOR	umbrella1_init_position = VGet(550, 60, 0);	//‚©‚³‚µ‚å‚«‚´‚Ğ‚å‚¤
	const VECTOR	umbrella2_init_position = VGet(850, 60, 0);	//‚©‚³‚µ‚å‚«‚´‚Ğ‚å‚¤
}; 