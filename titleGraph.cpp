#include"DxLib.h"
#include"titleGraph.h"

TitleGraph::TitleGraph()
{
	umbrella1Handle_	= LoadGraph("graph/black.png");
	umbrella2Handle_	= LoadGraph("graph/skyblue.png");
	
	reset();
}

TitleGraph::~TitleGraph()
{
	DeleteGraph(umbrella1Handle_);
	DeleteGraph(umbrella2Handle_);
}

void TitleGraph::reset()
{
	for (auto i = 0; i < 4; i++)
	{
		umbrellaPosition_[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

void TitleGraph::update()
{
	//ŽP‚ð•`‰æ
	DrawExtendGraph(umbrella1_init_position.x, umbrella1_init_position.y,
		umbrella1_init_position.x + umbrella_width, umbrella1_init_position.y + umbrella_height, umbrella1Handle_, TRUE);
	DrawExtendGraph(umbrella2_init_position.x + umbrella_width, umbrella2_init_position.y,
		umbrella2_init_position.x, umbrella2_init_position.y + umbrella_height, umbrella2Handle_, TRUE);
}
