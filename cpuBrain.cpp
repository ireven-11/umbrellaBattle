#include"DxLib.h"
#include<math.h>
#include"calculateDistance.h"
#include"charaBase.h"
#include"routine.h"
#include"cpuBrain.h"
#include"stage.h"

CPUBrain::CPUBrain()
{
	isTarget_				= true;
	randomTarget_			= 0;
	distance_				= 0.0f;
	canCharge_				= true;
	doActionRandom_			= 0;
	dicideActionCount_		= 0;
	dicideTargetCount_		= 0;
	aStarStartPosition_.x	= 0;
	aStarStartPosition_.y	= 0;
	aStarGoalPosition_.x	= 0;
	aStarGoalPosition_.y	= 0;
	chaseCount_				= 0;
	nextTilePosition_.x		= 0;
	nextTilePosition_.y		= 0;
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine, std::shared_ptr<Stage> stage)
{
	decideTarget(charaBase);
	dicideTargetCount_++;

	distance_ = CalculateDistance<float>(charaBase->Getposition_(), routine->players[randomTarget_ - 1]->Getposition_());

	//�^�[�Q�b�g����@�łȂ����������̍s���Ɉڂ�
	if (routine->players[randomTarget_ - 1]->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(routine->players[randomTarget_ - 1]->Getstate_())
		&& dicideTargetCount_ != 150)
	{
		decideNextAction(charaBase, routine, stage);
	}
	else
	{
		//�^�[�Q�b�g���Č���
		isTarget_ = true;
		dicideTargetCount_ = 0;
	}
}

/// <summary>
/// �^�[�Q�b�g������
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
void CPUBrain::decideTarget(CharaBase* charaBase)
{
	if (isTarget_)
	{
		while (true)
		{
			randomTarget_ = GetRand(max_player_number - 1) + 1;

			if (randomTarget_ != charaBase->GetcontrolerNumber_())
			{
				isTarget_ = false;
				break;
			}
		}
	}
}

/// <summary>
/// ���̍s��������
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
/// <param name="routine">���[�`���N���X</param>
void CPUBrain::decideNextAction(CharaBase* charaBase, Routine* routine, std::shared_ptr<Stage> stage)
{
	//�T���������[�g�ŒǐՂ���
	if (charaBase->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(charaBase->Getstate_()))
	{
		//�f�o�b�O�p
		/*auto debugIt = chaseRoot_.begin();
		switch (randomTarget_)
		{
		case 1:
			DrawSphere3D(stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x], 1.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), TRUE);
			for (auto i = 0; i < chaseRoot_.size(); i++)
			{
				DrawSphere3D(stage->Getposition_()[debugIt->y][debugIt->x], 1.0f, 32, GetColor(30 * i, 0, 0), GetColor(255, 255, 255), TRUE);
				debugIt++;
			}

			break;

		case 2:
			DrawSphere3D(stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x], 1.0f, 32, GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
			for (auto i = 0; i < chaseRoot_.size(); i++)
			{
				DrawSphere3D(stage->Getposition_()[debugIt->y][debugIt->x], 1.0f, 32, GetColor(30 * i, 0, 255), GetColor(255, 255, 255), TRUE);
				debugIt++;
			}
			break;
		case 3:
			DrawSphere3D(stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x], 1.0f, 32, GetColor(255, 255, 0), GetColor(255, 255, 255), TRUE);
			for (auto i = 0; i < chaseRoot_.size(); i++)
			{
				DrawSphere3D(stage->Getposition_()[debugIt->y][debugIt->x], 1.0f, 32, GetColor(255, 255, 30 * i), GetColor(255, 255, 255), TRUE);
				debugIt++;
			}
			break;
		case 4:
			DrawSphere3D(stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x], 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
			for (auto i = 0; i < chaseRoot_.size(); i++)
			{
				DrawSphere3D(stage->Getposition_()[debugIt->y][debugIt->x], 1.0f, 32, GetColor(255, 0, 30 * i), GetColor(255, 255, 255), TRUE);
				debugIt++;
			}
			break;
		default:
			break;
		}*/

		//�ړ�
		//�ǐՃ��[�g����
		decideChaceRoot(charaBase, routine);
		auto pos = stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x];
		charaBase->decideMoveAngle(pos);
		charaBase->input.Y = 750;

		//�^�C���ɂ��ǂ蒅������ A*�֌W
		if (CalculateDistance<float>(charaBase->Getposition_(), stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x]) < distance_error)
		{
			//�擪�v�f���폜
			chaseRoot_.pop_front();
			//�V�����擪�v�f�ɂȂ������̂̍��W�����ɐi�ލ��W�Ƃ���
			auto it = chaseRoot_.begin();
			if (chaseRoot_.size() > 1)
			{
				it++;
			}
			if (it != chaseRoot_.end())
			{
				nextTilePosition_ = *it;
			}
		}
	}
	else
	{
		//��@�̎��Ɉړ�����悤��input�ɒ��ڐ��l������
		charaBase->input.Buttons[6] = 2025;
		charaBase->input.Z			= 2025;
	}
}

/// <summary>
/// �ǐՃ��[�g���� A*�֌W
/// </summary>
/// <param name="charaBase">�L�����̐e�N���X</param>
/// <param name="routine">���[�`���N���X</param>
void CPUBrain::decideChaceRoot(CharaBase* charaBase, Routine* routine)
{
	//a*�Ōo�H�T��
	aStarStartPosition_.x = charaBase->GetonTileNumberX_();
	aStarStartPosition_.y = charaBase->GetonTileNumberY_();
	aStarGoalPosition_.x = routine->players[randomTarget_ - 1]->GetonTileNumberX_();
	aStarGoalPosition_.y = routine->players[randomTarget_ - 1]->GetonTileNumberY_();
	chaseRoot_ = a_star(aStarStartPosition_, aStarGoalPosition_);
	auto it = chaseRoot_.begin();
	if (chaseRoot_.size() > 1)
	{
		it++;
	}
	if (it != chaseRoot_.end())
	{
		nextTilePosition_ = *it;
	}
}