#include"DxLib.h"
#include"playGraph.h"
#include"PlayTransparentMovie.h"

PlayGraph::PlayGraph()
{
	countDownMovie_		= LoadGraph("movie/countdown.mp4");
	screenHandle_		= MakeScreen(1920, 1080, TRUE);
	movieWidht_			= init_movie_width;
	movieHeight_		= init_movie_height;
	moviePosition_		= init_movie_position;
	onCountDown_		= true;
	expandMovieCount_	= 0;
}

PlayGraph::~PlayGraph()
{
	DeleteGraph(countDownMovie_);
}

void PlayGraph::update()
{
	//動画を流す
	if (onCountDown_)
	{
		PlayTransparentMovie(countDownMovie_, screenHandle_, movieWidht_, movieHeight_, moviePosition_, false);

		//カウントが一定になるとカウントダウン動画を拡大させる
		++expandMovieCount_;
		if (expandMovieCount_ > max_expand_count)
		{
			moviePosition_.x	-= expand_speed_x;
			movieWidht_			+= expand_speed_x;
			movieHeight_		+= expand_speed_y;

			//画面よりでかくなりそうだったら戻す
			if (movieWidht_ > 1920)
			{
				movieWidht_ = 1920;
			}
			if (movieHeight_ > 1080)
			{
				movieHeight_ = 1080;
			}
			if (moviePosition_.x < 0)
			{
				moviePosition_.x = 0;
			}
		}

		if (!GetMovieStateToGraph(countDownMovie_))
		{
			onCountDown_ = false;
		}
	}
}