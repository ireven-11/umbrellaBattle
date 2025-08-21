#pragma once

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();

	void update();

private:
	void reset();

	int		umbrella1Handle_;		//傘１
	int		umbrella2Handle_;		//傘２
	VECTOR	umbrellaPosition_[4];	//傘座標
	int		screenHandle_;			//スクリーンハンドル
	int		movieHandle_;			//動画ハンドル

	const int		umbrella_width	= 500;	//傘幅
	const int		umbrella_height	= 400;	//高さ
	const VECTOR	umbrella1_init_position = VGet(550, 60, 0);	//かさしょきざひょう
	const VECTOR	umbrella2_init_position = VGet(850, 60, 0);	//かさしょきざひょう
}; 