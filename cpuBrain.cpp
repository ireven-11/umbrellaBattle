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

	//ターゲットが扇風機でない時だけ次の行動に移る
	if (routine->players[randomTarget_ - 1]->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(routine->players[randomTarget_ - 1]->Getstate_())
		&& dicideTargetCount_ != 150)
	{
		decideNextAction(charaBase, routine, stage);
	}
	else
	{
		//ターゲットを再決定
		isTarget_ = true;
		dicideTargetCount_ = 0;
	}
}

/// <summary>
/// ターゲットを決定
/// </summary>
/// <param name="charaBase">キャラの親クラス</param>
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
/// 次の行動を決定
/// </summary>
/// <param name="charaBase">キャラの親クラス</param>
/// <param name="routine">ルーチンクラス</param>
void CPUBrain::decideNextAction(CharaBase* charaBase, Routine* routine, std::shared_ptr<Stage> stage)
{
	//探索したルートで追跡する
	if (charaBase->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(charaBase->Getstate_()))
	{
		//デバッグ用
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

		//移動
		//追跡ルート決定
		decideChaceRoot(charaBase, routine);
		auto pos = stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x];
		charaBase->decideMoveAngle(pos);
		charaBase->input.Y = 750;

		//タイルにたどり着いたら A*関係
		if (CalculateDistance<float>(charaBase->Getposition_(), stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x]) < distance_error)
		{
			//先頭要素を削除
			chaseRoot_.pop_front();
			//新しく先頭要素になったものの座標を次に進む座標とする
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
		//扇風機の時に移動するようにinputに直接数値を入れる
		charaBase->input.Buttons[6] = 2025;
		charaBase->input.Z			= 2025;
	}
}

/// <summary>
/// 追跡ルート決定 A*関係
/// </summary>
/// <param name="charaBase">キャラの親クラス</param>
/// <param name="routine">ルーチンクラス</param>
void CPUBrain::decideChaceRoot(CharaBase* charaBase, Routine* routine)
{
	//a*で経路探索
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