#include"DxLib.h"
#include"charaBase.h"
#include"stage.h"
#include"routine.h"
#include"sandBag.h"

SandBag::SandBag(const int join_number) : CharaBase(join_number)
{
	modelHandle_	= MV1LoadModel("3dmodel/punchingBag/punchingBag.mv1");
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

SandBag::~SandBag()
{
	MV1DeleteModel(modelHandle_);
}

void SandBag::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	position_ = collisionCenterPosition_;

	//ステージの外に出たら元に戻す
	if (stage->Getposition_()[0][0].x > position_.x)
	{
		position_					= VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_	= VGet(0.0f, 0.0f, 0.0f);
	}
	if (stage->Getposition_()[tile_number - 1][tile_number - 1].x < position_.x) 
	{
		position_					= VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_	= VGet(0.0f, 0.0f, 0.0f);
	}
	if (stage->Getposition_()[0][0].z > position_.z)
	{
		position_					= VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_	= VGet(0.0f, 0.0f, 0.0f);
	}
	if (stage->Getposition_()[tile_number - 1][tile_number - 1].z < position_.z)
	{
		position_					= VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_	= VGet(0.0f, 0.0f, 0.0f);
	}

	MV1SetPosition(modelHandle_, position_);
}

void SandBag::draw()const
{
	MV1DrawModel(modelHandle_);
}