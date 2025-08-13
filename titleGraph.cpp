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
}

/// <summary>
/// �摜�A�j���[�V�����`��
/// </summary>
/// <param name="position">�`����W</param>
/// <param name="graphHandle">�摜�n���h��(�����ǂݍ��݂�������)</param>
/// <param name="graphWidth">�摜�̕�(1������)</param>
/// <param name="graphHeight">�摜�̍���(1������)</param>
/// <param name="tilSwitchTime">�摜���؂�ւ��܂ł̎���</param>
/// <param name="finishGraphNumber">�Ō�̃A�j���[�V�����摜�������ڂ���\������</param>
/// <param name="startGraphNumber">�ŏ��̃A�j���[�V�����摜�������ڂ���\������</param>
void DrawAnimationGraph(VECTOR position, int graphHandle[], int graphWidth, int graphHeight, unsigned int tilSwitchTime, unsigned int finishGraphNumber, unsigned int startGraphNumber = 0)
{
	//�؂�ւ��܂ŃJ�E���g�𑝂₵�đ҂�
	static int waitCount;
	static int animationCount = startGraphNumber;
	++waitCount;
	if (waitCount >= tilSwitchTime)
	{
		//�A�j���[�V�����J�E���g�𑝂₷
		++animationCount;
		waitCount = 0;

		//�A�j���[�V�������Ō�܂ł�������ŏ��ɖ߂�
		if (animationCount >= finishGraphNumber)
		{
			animationCount = startGraphNumber;
		}
	}
	DrawExtendGraph(position.x, position.y, position.x + graphWidth, position.y + graphHeight, graphHandle[animationCount], TRUE);
}

void TitleGraph::update()
{
	DrawAnimationGraph(hitPosition_, hitHandle_, hit_width, hit_height, hit_switch_time, hit_div_number);
}
