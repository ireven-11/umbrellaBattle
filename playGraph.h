#pragma once

class PlayGraph
{
public:
	PlayGraph();
	~PlayGraph();

	void update();

	bool GetonCountDown_()const { return onCountDown_; }

private:
	int		countDownMovie_;	//カウントダウン動画
	int		screenHandle_;		//スクリーンハンドル
	int		movieWidht_;		//動画幅
	int		movieHeight_;		//動画高さ
	VECTOR	moviePosition_;		//動画座標
	bool	onCountDown_;		//カウントダウン中かどうか
	int		expandMovieCount_;	//拡大カウント

	const int		init_movie_width		= 750;				//動画初期幅
	const int		init_movie_height		= 460;				//動画初期高さ
	const VECTOR	init_movie_position		= VGet(1220, 0, 0);	//初期座標
	const int		max_expand_count		= 200;				//最大拡大カウント
	const short		expand_speed_x			= 20;				//拡大スピードx
	const short		expand_speed_y			= 10;				//拡大スピードy
};