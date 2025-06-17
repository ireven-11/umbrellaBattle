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
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.1);
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
	
	//でばっぐリセット
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = player_init_positionY;
	}

	action();
	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	draw();
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
	position_			= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_			= true;
	isTackle_			= false;
	tackleCount_		= 0;
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
		if (!isTackle_)
		{
			position_.z += move_speed;
		}
		rotation();
	}
	if (input.Y > 0)
	{
		if (!isTackle_)
		{
			position_.z -= move_speed;
		}
		rotation();
	}
	if (input.X > 0)
	{
		if (!isTackle_)
		{
			position_.x += move_speed;
		}
		rotation();
	}
	if (input.X < 0)
	{
		if (!isTackle_)
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
	move();
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
	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		--tackleCount_;
		tackleMoving();

		//カウントが０になったらタックルを辞める
		if (tackleCount_ == 0)
		{
			isTackle_ = false;
		}
	}
	//Bボタンを押したら
	else if (input.Buttons[0] > 0)
	{
		isTackle_ = true;
		++tackleCount_;
	}

	//デバッグ用
	DrawFormatString(100, 300, GetColor(255, 255, 255), "タックル:%d", tackleCount_);
}

void Player::tackleMoving()
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
	//スティックの倒れてる数値から角度を求める
	double angleRad	= atan2(static_cast<double>(-input.Y), static_cast<double>(input.X));
	
	MV1SetRotationXYZ(closingUmbrella_, VGet(-45.0f * DX_PI_F / 180.0f, -angleRad - 1.5, 0.0f));
	MV1SetRotationXYZ(openingUmbrella_, VGet(-45.0f * DX_PI_F / 180.0f, -angleRad - 1.5, 0.0f));

	//デバッグ用
	DrawFormatString(200, 200, GetColor(255, 255, 255), "角度:%f", angleRad);
}