#include"DxLib.h"
#include"player.h"

Player::Player()
{
	//3d���f���ǂݍ���
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");

	//���l������
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
	position_	= VGet(0, 0, 0);
	isOpening_	= true;
}