#include"DxLib.h"
#include"player.h"

Player::Player()
{
	//3dモデル読み込み
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));

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
		MV1SetRotationXYZ(closingUmbrella_, VGet(40.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(40.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}
	if (CheckHitKey(KEY_INPUT_4))
	{
		MV1SetRotationXYZ(closingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}
	//でばっぐリセット
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = player_init_positionY;
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	draw();
	move();
}

void Player::draw()const
{
	//デバッグ用
	//DrawFormatString(0, 300, GetColor(255, 0, 0), "px:%f,py:%f,pz:%f", position_.x, position_.y, position_.z);

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
	position_	= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_	= true;
}

void Player::move()
{
	if (CheckHitKey(KEY_INPUT_UP) == true)
	{
		position_.z += move_speed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == true)
	{
		position_.z -= move_speed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == true)
	{
		position_.x += move_speed;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == true)
	{
		position_.x -= move_speed;
	}
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

/// <summary>
/// 落下
/// </summary>
void Player::fall()
{
	position_.y -= fall_speed;
}