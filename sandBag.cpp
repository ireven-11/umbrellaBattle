#include"DxLib.h"
#include"charaBase.h"
#include"stage.h"
#include"routine.h"
#include"sandBag.h"

SandBag::SandBag(const int join_number) : CharaBase(join_number)
{
	modelHandle_	= MV1LoadModel("3dmodel/punchingBag/punchingBag.mv1");
	MV1SetScale(modelHandle_, VGet(1.5f, 1.0f, 1.5f));
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

SandBag::~SandBag()
{
	MV1DeleteModel(modelHandle_);
}

void SandBag::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	position_ = VGet(collisionCenterPosition_.x,position_.y,collisionCenterPosition_.z);

	//ステージの外に出たら元に戻す
	if (position_.y < -10.0f)
	{
		position_ = VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_ = VGet(0.0f, 0.0f, 0.0f);
	}

	MV1SetPosition(modelHandle_, position_);
}

void SandBag::draw()const
{
	MV1DrawModel(modelHandle_);
}