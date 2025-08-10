#include"DxLib.h"
#include"titleGraph.h"

TitleGraph::TitleGraph()
{
	umbrella1Handle_	= LoadGraph("graph/black.png");
	umbrella2Handle_	= LoadGraph("graph/skyblue.png");
	umbrella3Handle_	= LoadGraph("graph/orange.png");
	umbrella4Handle_	= LoadGraph("graph/pink.png");
	LoadDivGraph("graph/2dHit.png", hit_div_number, hit_div_X, hit_div_y, hit_size_x, hit_size_y, hitHandle_);

	reset();
}

TitleGraph::~TitleGraph()
{
	DeleteGraph(umbrella1Handle_);
	DeleteGraph(umbrella2Handle_);
	DeleteGraph(umbrella3Handle_);
	DeleteGraph(umbrella4Handle_);
	for (auto i = 0; i < hit_div_number; i++)
	{
		DeleteGraph(hitHandle_[i]);
	}
}

void TitleGraph::reset()
{
	for (auto i = 0; i < 4; i++)
	{
		umbrellaPosition_[i] = VGet(0.0f, 0.0f, 0.0f);
	}
	hitPosition_		= VGet(1000.0f, 0.0f, 0.0f);
	hitAnimationCount_	= 0;
	hitWaitCount_		= 0;
}

void DrawAnimationGraph(int graphHandle[], int divNumber, VECTOR position, int width, int height, int& animationCount, int swichTiming, int& waitCount)
{
	//切り替えまでカウントを増やして待つ
	++waitCount;
	if (waitCount >= swichTiming)
	{
		//アニメーションカウントを増やす
		++animationCount;
		waitCount = 0;

		//アニメーションが最後までいったら最初に戻す
		if (animationCount >= divNumber)
		{
			animationCount = 0;
		}
	}
	DrawExtendGraph(position.x, position.y, position.x + width, position.y + height, graphHandle[animationCount], TRUE);
}

void TitleGraph::update()
{
	DrawAnimationGraph(hitHandle_, hit_div_number, hitPosition_, hit_width, hit_height, hitAnimationCount_, hit_switch_time, hitWaitCount_);
	/*for (auto i = 0; i < 4; i++)
	{
		DrawRotaGraph(umbrellaPosition_[i])
	}*/
}
