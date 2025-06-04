#include"DxLib.h"
#include"player.h"

Player::Player()
{
	//3dモデル読み込み
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	MV1SetScale(openingUmbrella_, VGet(0.1f, 0.1f, 0.1f));
	MV1SetScale(closingUmbrella_, VGet(0.1f, 0.1f, 0.1f));

	//数値初期化
	reset();
}

Player::~Player()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
}

void Player::update()
{
	//テスト用モデル変更＋回転
	if (CheckHitKey(KEY_INPUT_1))
	{
		isOpening_ = true;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		isOpening_ = false;
	}
	if (CheckHitKey(KEY_INPUT_3))
	{
		MV1SetRotationXYZ(closingUmbrella_, VGet(90.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(90.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_4))
	{
		MV1SetRotationXYZ(closingUmbrella_, VGet(-90.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(-90.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	draw();
}

void Player::draw()const
{
	//仮床
	//DrawTriangle3D(VGet(-100, 0, -100), VGet(-100, 0, 100), VGet(1000, 0, -100), GetColor(0, 250, 50), TRUE);

	DrawFormatString(1000, 100, GetColor(255, 255, 255), "px:%f,py:%f,pz:%f", position_.x, position_.y, position_.z);

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

void Player::move()
{

}

void Player::action()
{
	swing();
	tackle();
	wind();
}

void Player::swing()
{

}

void Player::tackle()
{

}

void Player::wind()
{

}