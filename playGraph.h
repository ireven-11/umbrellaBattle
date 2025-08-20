#pragma once

class PlayGraph
{
public:
	PlayGraph(const char* fontName);
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
	int		fontHandle_;		//フォントハンドル
	int		startSound_;		//スタートサウンド
	int		trumpet_;			//トランペット画像
	int		fontHandleSize300_;	//フォントハンドル300
	int		beat_;				//相手倒す画像

	const int		init_movie_width		= 750;				//動画初期幅
	const int		init_movie_height		= 460;				//動画初期高さ
	const VECTOR	init_movie_position		= VGet(1220, 0, 0);	//初期座標
	const int		max_expand_count		= 210;				//最大拡大カウント
	const short		expand_speed_x			= 20;				//拡大スピードx
	const short		expand_speed_y			= 10;				//拡大スピードy
	const VECTOR	explane_rule_position	= VGet(440, 90, 0);	//ルール説明座標
	const short		start_sound_volume		= 150;				//スタートサウンドボリューム
	const VECTOR	trumpet_position		= VGet(350, 300, 0);//トランペット座標
	const float		trumpet_width			= 625.0f;
	const float		trumpet_height			= 325.0f;
	const VECTOR	batu_position			= VGet(900, 325, 0);
	const VECTOR	beat_position			= VGet(300, 325, 0);
	const float		beat_width				= 1325.0f;
	const float		beat_height				= 425.0f;
};