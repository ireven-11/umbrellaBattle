#include"DxLib.h"
#include<math.h>
#include"calculateDistance.h"
#include"charaBase.h"
#include"routine.h"
#include"cpuBrain.h"
#include"stage.h"

CPUBrain::CPUBrain()
{
	isTarget_ = true;
	randomTarget_ = 0;
	distance_ = 0.0f;
	canCharge_ = true;
	doActionRandom_ = 0;
	dicideActionCount_ = 0;
	actionState_ = chaseState_();
	dicideTargetCount_ = 0;
	aStarStartPosition_.x = 0;
	aStarStartPosition_.y = 0;
	aStarGoalPosition_.x = 0;
	aStarGoalPosition_.y = 0;
	chaseCount_ = 0;
	nextTilePosition_.x = 0;
	nextTilePosition_.y = 0;
}

CPUBrain::~CPUBrain()
{
}

void CPUBrain::update(CharaBase* charaBase, Routine* routine, shared_ptr<Stage> stage)
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

	actionState_->update(charaBase);
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
			randomTarget_ = GetRand(3) + 1;

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
void CPUBrain::decideNextAction(CharaBase* charaBase, Routine* routine, shared_ptr<Stage> stage)
{
	//距離によってどの行動をするか変える
	if (distance_ < 3)//スイング
	{
		int doActionRandom_ = GetRand(100);

		if (doActionRandom_ > 50)
		{
			charaBase->input.Buttons[1] = 128;
		}
	}
	else if (distance_ > 20 && charaBase->GettackleCount_() <= charaBase->Getmax_tackle_count() && canCharge_)//タックル
	{
		//doActionRandom_ = GetRand(50);
		//if (charaBase->GettackleCount_() == charaBase->Getmax_tackle_count() - doActionRandom_)
		//{
		//	canCharge_ = false;
		//}

		////if (random > 30)
		//{
		//	charaBase->input.Buttons[0] = 128;
		//	VECTOR stickVector = VGet(0.0f, 0.0f, 0.0f);
		//	if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
		//	{
		//		//charaBase->input.X = 635;
		//		stickVector.x += 635.0f;
		//	}
		//	else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
		//	{
		//		//charaBase->input.X = -745;
		//		stickVector.x += -745.0f;
		//	}
		//	if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
		//	{
		//		//charaBase->input.Y = -830;
		//		stickVector.y += -830.0f;
		//	}
		//	else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
		//	{
		//		//charaBase->input.Y = 750;
		//		stickVector.y += 750.0f;
		//	}

		//	double targetAngle = atan2(static_cast<double>(routine->players[randomTarget_ - 1]->Getposition_().x - charaBase->Getposition_().x),
		//		static_cast<double>(routine->players[randomTarget_ - 1]->Getposition_().z - charaBase->Getposition_().z));
		//	MATRIX rotationMatrix = MGetRotY(targetAngle);
		//	stickVector = VTransform(stickVector, rotationMatrix);

		//	charaBase->input.X = stickVector.x;
		//	charaBase->input.Y = stickVector.y;
		//}
	}
	else//移動
	{
		//追跡ルート決定
		decideChaceRoot(charaBase, routine);

		//探索したルートで追跡する
		//nextTilePosition_ = chaseRoot_.front();
		if (charaBase->Getposition_().x < stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x].x)
		{
			charaBase->input.X = 635;
		}
		else if (charaBase->Getposition_().x > stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x].x)
		{
			charaBase->input.X = -745;
		}
		if (charaBase->Getposition_().z < stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x].z)
		{
			charaBase->input.Y = -830;
		}
		else if (charaBase->Getposition_().z > stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x].z)
		{
			charaBase->input.Y = 750;
		}

		//タイルにたどり着いたら
		if (CalculateDistance<float>(charaBase->Getposition_(), stage->Getposition_()[nextTilePosition_.y][nextTilePosition_.x]) < 0.05f)
		{
			//先頭要素を削除
			chaseRoot_.pop_front();//バグあり（emptyの部分を消そうとする）

			//新しく先頭要素になったものの座標を次に進む座標とする
			auto it = chaseRoot_.begin();
			if (chaseRoot_.size() > 1)
			{
				it++;
			}

			nextTilePosition_ = *it;
		}

		/*if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
		{
			charaBase->input.X = 635;
		}
		else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
		{
			charaBase->input.X = -745;
		}
		if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
		{
			charaBase->input.Y = -830;
		}
		else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
		{
			charaBase->input.Y = 750;
		}*/
		/*else//逃走
		{
			if (charaBase->Getposition_().x < routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = -745;
			}
			else if (charaBase->Getposition_().x > routine->players[randomTarget_ - 1]->Getposition_().x)
			{
				charaBase->input.X = 635;
			}
			if (charaBase->Getposition_().z < routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = 750;
			}
			else if (charaBase->Getposition_().z > routine->players[randomTarget_ - 1]->Getposition_().z)
			{
				charaBase->input.Y = -830;
			}
		}*/

		//actionState_ = chaseState_();
	}

	if (charaBase->GettackleCount_() == 0)
	{
		canCharge_ = true;
	}
}

/// <summary>
/// 追跡ルート決定
/// </summary>
/// <param name="charaBase">キャラの親クラス</param>
/// <param name="routine">ルーチンクラス</param>
void CPUBrain::decideChaceRoot(CharaBase* charaBase, Routine* routine)
{
	//毎フレーム探索すると処理が重くなりそうなので3fに一回にする
	++chaseCount_;
	if (chaseCount_ > 3)
	{
		chaseCount_ = 0;
	}
	if (chaseCount_ == 3)
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
		nextTilePosition_ = *it;
	}
}