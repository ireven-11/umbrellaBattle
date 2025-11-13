#include"DxLib.h"
#include"titleGraph.h"

TitleGraph::TitleGraph()
{
	
	logo_				= LoadGraph("graph/titleLogo.png");
	
	reset();
}

TitleGraph::~TitleGraph()
{
	
	DeleteGraph(logo_);
}

void TitleGraph::reset()
{
	
}

void TitleGraph::update()
{
	DrawExtendGraphF(logo_min_pos.x, logo_min_pos.y, logo_max_pos.x, logo_max_pos.y, logo_, TRUE);
}
