#include"DxLib.h"
#include"charaBase.h"
#include"stage.h"
#include"routine.h"
#include"sandBag.h"

SandBag::SandBag(const int join_number) : CharaBase(join_number)
{
	modelHandle_	= MV1LoadModel("3dmodel/punchingBag/punchingBag.mv1");
	MV1SetScale(modelHandle_, VGet(0.2f, 0.15f, 0.2f));
	position_					= VGet(0.0f, 0.0f, 0.0f);
	collisionCenterPosition_	= VGet(0.0f, 0.0f, -5.5f);
	isDrawing_ = false;
}

SandBag::~SandBag()
{
	MV1DeleteModel(modelHandle_);
}

void SandBag::reset()
{
	MV1SetScale(modelHandle_, VGet(0.2f, 0.15f, 0.2f));
	position_ = VGet(0.0f, 0.0f, 0.0f);
	collisionCenterPosition_ = VGet(0.0f, 0.0f, -5.5f);
	isDrawing_ = false;
}

void SandBag::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	collisionCenterPosition_ = position_;

	//ステージの外に出たら元に戻す
	if (position_.y < -10.0f)
	{
		position_ = VGet(0.0f, 0.0f, 0.0f);
		collisionCenterPosition_ = VGet(0.0f, 0.0f, 0.0f);
	}

	if (onHitStop_)
	{
		hitStopNow();
	}
	
	MV1SetPosition(modelHandle_, position_);
}

void SandBag::draw()
{
	//カメラに入ってないときは描画しない
	isDrawing_ = false;
	if (CheckCameraViewClip(position_))return;

	isDrawing_ = true;
	MV1DrawModel(modelHandle_);
}