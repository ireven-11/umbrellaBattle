#include"DxLib.h"
#include"playGraph.h"
#include"PlayTransparentMovie.h"

PlayGraph::PlayGraph()
{
	countDownMovie_ = LoadGraph("movie/countdown.mp4");
	screenHandle_ = MakeScreen(1920, 1080, TRUE);
}

PlayGraph::~PlayGraph()
{
	DeleteGraph(countDownMovie_);
}

void PlayGraph::update()
{

}