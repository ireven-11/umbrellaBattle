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

/// <summary>
/// 画像アニメーション描画
/// </summary>
/// <param name="position">描画座標</param>
/// <param name="graphHandle">画像ハンドル(分割読み込みしたもの)</param>
/// <param name="graphWidth">画像の幅(1分割分)</param>
/// <param name="graphHeight">画像の高さ(1分割分)</param>
/// <param name="tilSwitchTime">画像が切り替わるまでの時間</param>
/// <param name="finishGraphNumber">最後のアニメーション画像が何枚目かを表す数字</param>
/// <param name="startGraphNumber">最初のアニメーション画像が何枚目かを表す数字</param>
void DrawAnimationGraph(VECTOR position, int graphHandle[], int graphWidth, int graphHeight, unsigned int tilSwitchTime, unsigned int finishGraphNumber, unsigned int startGraphNumber = 0)
{
	//切り替えまでカウントを増やして待つ
	static int waitCount;
	static int animationCount = startGraphNumber;
	++waitCount;

	//別種のアニメーションへの切り替えを感知してカウントを０に戻す
	static int checkChangeAnim = startGraphNumber;
	if (checkChangeAnim != startGraphNumber)
	{
		waitCount = 0;
		animationCount = startGraphNumber;
		checkChangeAnim = startGraphNumber;
	}

	if (waitCount >= tilSwitchTime)
	{
		//アニメーションカウントを増やす
		++animationCount;
		waitCount = 0;

		//アニメーションが最後までいったら最初に戻す
		if (animationCount >= finishGraphNumber)
		{
			animationCount = startGraphNumber;
		}
	}
	DrawExtendGraph(position.x, position.y, position.x + graphWidth, position.y + graphHeight, graphHandle[animationCount], TRUE);
}

void TitleGraph::update()
{
	//傘を描画
	DrawExtendGraph(umbrella1_init_position.x, umbrella1_init_position.y,
		umbrella1_init_position.x + umbrella_width, umbrella1_init_position.y + umbrella_height, umbrella1Handle_, TRUE);
	DrawExtendGraph(umbrella2_init_position.x + umbrella_width, umbrella2_init_position.y,
		umbrella2_init_position.x, umbrella2_init_position.y + umbrella_height, umbrella2Handle_, TRUE);
}
