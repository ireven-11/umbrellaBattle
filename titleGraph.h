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
	int		umbrella3Handle_;		//傘3
	int		umbrella4Handle_;		//傘４
	int		hitHandle_[18];			//ヒット
	VECTOR	umbrellaPosition_[4];	//傘座標
	VECTOR	hitPosition_;			//ヒット座標
	int		hitAnimationCount_;		//ヒットアニメーションカウント
	int		hitWaitCount_;			//ヒットアニメーション待ちカウント

	const short hit_div_number	= 18;	//ヒット分割数
	const short hit_div_X		= 9;	//ヒット分割数x
	const short hit_div_y		= 2;	//ヒット分割数y
	const int	hit_size_x		= 516;	//画像の大きさx
	const int	hit_size_y		= 528;	//画像の大きさy
	const int	hit_width		= 100;	//ヒットの幅
	const int	hit_height		= 100;	//ヒットのt高さ
	const int	hit_switch_time = 2;	//ヒット変わる時間
};