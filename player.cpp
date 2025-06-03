#include"DxLib.h"
#include"player.h"

Player::Player()
{
	//3dÉÇÉfÉãì«Ç›çûÇ›
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	MV1SetScale(openingUmbrella_, VGet(0.1f, 0.1f, 0.1f));
	MV1SetScale(closingUmbrella_, VGet(0.1f, 0.1f, 0.1f));

	//êîílèâä˙âª
	reset();
}

Player::~Player()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
}

void Player::update()
{
	if (CheckHitKey(KEY_INPUT_1))
	{
		isOpening_ = true;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		isOpening_ = false;
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	draw();
}

void Player::draw()const
{
	//âºè∞
	DrawTriangle3D(VGet(-100, 0, -100), VGet(-100, 0, 100), VGet(1000, 0, -100), GetColor(0, 250, 50), TRUE);

	if (isOpening_)
	{
		MV1DrawModel(openingUmbrella_);
	}
	else
	{
		MV1DrawModel(closingUmbrella_);
	}
}

void Player::reset()
{
	position_	= VGet(0.0f, 0.0f, 0.0f);
	isOpening_	= true;
}