#include"DxLib.h"
#include"player.h"
#include<cmath>

//コントローラー(D)用構造体変数
DINPUT_JOYSTATE input;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(const int join_number)
{
	//3dモデル読み込み
	openingUmbrella_	= MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_	= MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	fan_				= MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(fan_, VGet(scale / 10, scale / 10, scale / 10));

	//数値初期化
	reset();

	controlerNumber_ = join_number;

	//コントローラーのデッドゾーンを設定
	SetJoypadDeadZone(controlerNumber_, 0.1);
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
	//コントローラーを使えるようにする
	GetJoypadDirectInputState(controlerNumber_, &input);

	//テスト用モデル変更＋回転
	if (CheckHitKey(KEY_INPUT_1))
	{
		isOpening_ = true;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		isOpening_ = false;
	}
	
	//でばっぐリセット
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = 0.0f;
	}

	action();
	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(fan_, position_);
	draw();
}

/// <summary>
/// 描画
/// </summary>
void Player::draw()const
{
	//デバッグ用
	//DrawFormatString(0, 300, GetColor(255, 0, 0), "px:%f,py:%f,pz:%f", position_.x, position_.y, position_.z);

	if (isFan_)
	{
		MV1DrawModel(fan_);
	}
	else if (isOpening_)
	{
		MV1DrawModel(openingUmbrella_);
	}
	else if (!isOpening_)
	{
		MV1DrawModel(closingUmbrella_);
	}
}

/// <summary>
/// 変数をリセット
/// </summary>
void Player::reset()
{
	position_			= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_			= true;
	isTackle_			= false;
	tackleCount_		= 0.0f;
	tackleVector_		= VGet(0.0f, 0.0f, 0.0f);
	rotationAngleY_		= 0.0;
	rotaionMatrix_		= MGetIdent();
	isMovingtackle_		= false;
	controlerNumber_	= 0;
	isSwing_			= false;
	hp_					= max_hp;
	angleSwing_			= 0.00;
	isFan_				= true;
}

/// <summary>
/// 移動
/// </summary>
void Player::move()
{
	if (input.Y < 0)
	{
		if (!isTackle_ && !isSwing_)
		{
			position_.z += move_speed;
		}
		rotation();
	}
	if (input.Y > 0)
	{
		if (!isTackle_ && !isSwing_)
		{
			position_.z -= move_speed;
		}
		rotation();
	}
	if (input.X > 0)
	{
		if (!isTackle_ && !isSwing_)
		{
			position_.x += move_speed;
		}
		rotation();
	}
	if (input.X < 0)
	{
		if (!isTackle_ && !isSwing_)
		{
			position_.x -= move_speed;
		}
		rotation();
	}
}

/// <summary>
/// アクション
/// </summary>
void Player::action()
{
	//hpがあるとき
	if (hp_ > 0)
	{
		move();
		swing();
		tackle();
	}
	//hpがないとき
	else
	{
		wind();
	}
}

/// <summary>
/// アクション：スイング
/// </summary>
void Player::swing()
{
	//他アクションしてない時だけ
	if (!isSwing_&& input.Buttons[1] > 0 && !isTackle_)
	{
		isSwing_	= true;
		angleSwing_ = rotationAngleY_;
	}
	//スイングしてるときはy軸回転する
	else if (isSwing_)
	{
		angleSwing_ += swing_speed;
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, angleSwing_ + adjust_rotation_angle_y, 0.0f));

		//最大までスイングしたら元の角度に戻る
		if (angleSwing_ >= max_swing_angle + rotationAngleY_)
		{
			MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
			isSwing_ = false;
		}
	}
}

/// <summary>
/// アクション：タックル
/// </summary>
void Player::tackle()
{
	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingtackle_ = true;
		--tackleCount_;
		tackleMoving(rotaionMatrix_);
	}
	//Bボタンを押したら
	else if (input.Buttons[0] > 0 && !isMovingtackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			++tackleCount_;
		}
		
		//どの方向にタックルするか回転行列で決める
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);
	}

	stopTackle();

	//デバッグ用
	DrawFormatString(100, 300, GetColor(255, 255, 255), "タックル:%f", tackleCount_);
}

/// <summary>
/// タックル移動中
/// </summary>
/// <param name="rotation">どの方向にタックルするか決める回転行列</param>
void Player::tackleMoving(MATRIX rotation)
{
	VECTOR moveVector = VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotation);
	position_ = VAdd(position_, moveVector);

	//移動中は落下しずらくするようにyに補正をかける
	if (position_.y < 0.0f)
	{
		position_.y += adjust_position_y;
	}
}

/// <summary>
/// タックルをやめる
/// </summary>
void Player::stopTackle()
{
	//カウントが０なるかタックル中にBを押したらやめる
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0)
	{
		isTackle_		= false;
		isMovingtackle_ = false;
		tackleCount_	= 0;
	}
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

/// <summary>
/// コントローラーのスティックの傾きに応じた3dモデルの回転
/// </summary>
void Player::rotation()
{
	//アクションをしてない時だけ
	if (!isMovingtackle_ && !isSwing_)
	{
		//スティックの倒れてる数値から角度を求める
		rotationAngleY_ = atan2(static_cast<double>(input.Y), static_cast<double>(input.X));

		MV1SetRotationXYZ(closingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
	}
	
	//デバッグ用
	//DrawFormatString(200, 200, GetColor(255, 255, 255), "角度:%f", rotationAngle_);
}