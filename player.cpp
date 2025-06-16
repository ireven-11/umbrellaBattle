#include"DxLib.h"
#include"player.h"
#include<cmath>

//コントローラー(D)用構造体変数
DINPUT_JOYSTATE input;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	//3dモデル読み込み
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));

	//数値初期化
	reset();

	//コントローラーのデッドゾーンを設定
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.5);
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
}

/// <summary>
/// 更新
/// </summary>
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

/// <summary>
/// 描画
/// </summary>
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

/// <summary>
/// 変数をリセット
/// </summary>
void Player::reset()
{
	position_		= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_		= true;
}

/// <summary>
/// 移動
/// </summary>
void Player::move()
{
	//コントローラーを使えるようにする
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//キーボード用（デバッグ)
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
	//コントローラー用
	if (input.Y < 0)
	{
		position_.z += move_speed;
		rotation();
	}
	if (input.Y > 0)
	{
		position_.z -= move_speed;
		rotation();
	}
	if (input.X > 0)
	{
		position_.x += move_speed;
		rotation();
	}
	if (input.X < 0)
	{
		position_.x -= move_speed;
		rotation();
	}
}

/// <summary>
/// アクション
/// </summary>
void Player::action()
{
	swing();
	tackle();
	wind();
}

/// <summary>
/// アクション：スイング
/// </summary>
void Player::swing()
{

}

/// <summary>
/// アクション：タックル
/// </summary>
void Player::tackle()
{

}

/// <summary>
/// アクション：風
/// </summary>
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

//回転がうまくいってない。要修正
void Player::rotation()
{
	GetJoypadAnalogInput(&input.X, &input.Y, DX_INPUT_PAD1);

	//スティックの倒れてる向きから角度を求める
	float angleRad		= atan2(input.Y, input.X);
	float angleRotation = angleRad * (180.0f / DX_PI);

	MV1SetRotationXYZ(closingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, angleRotation - 90.0f, 0.0f));
	MV1SetRotationXYZ(openingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, angleRotation - 90.0f, 0.0f));
}