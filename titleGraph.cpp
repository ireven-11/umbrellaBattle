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

	//�ʎ�̃A�j���[�V�����ւ̐؂�ւ������m���ăJ�E���g���O�ɖ߂�
	static int checkChangeAnim = startGraphNumber;
	if (checkChangeAnim != startGraphNumber)
	{
		waitCount = 0;
		animationCount = startGraphNumber;
		checkChangeAnim = startGraphNumber;
	}

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
	//�P��`��
	DrawExtendGraph(umbrella1_init_position.x, umbrella1_init_position.y,
		umbrella1_init_position.x + umbrella_width, umbrella1_init_position.y + umbrella_height, umbrella1Handle_, TRUE);
	DrawExtendGraph(umbrella2_init_position.x + umbrella_width, umbrella2_init_position.y,
		umbrella2_init_position.x, umbrella2_init_position.y + umbrella_height, umbrella2Handle_, TRUE);
}
