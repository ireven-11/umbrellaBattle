#include"DxLib.h"
#include"resultGraph.h"
#include"PlayTransparentMovie.h"

ResultGraph::ResultGraph()
{
    movieHandle_    = LoadGraph("movie/confetti02.mp4");
    screenHandle_   = MakeScreen(1920, 1080, TRUE);
}

ResultGraph::~ResultGraph()
{
    DeleteGraph(movieHandle_);
    DeleteGraph(screenHandle_);
}

void ResultGraph::update()
{
    PlayTransparentMovie(movieHandle_, screenHandle_);
}