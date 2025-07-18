#include"Dxlib.h"
#include"charaBase.h"
#include<cmath>
#include"stage.h"
#include"routine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="join_number">何Pかを表す数字</param>
CharaBase::CharaBase(const int join_number)
{
	//3dモデル読み込み
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(fan_, VGet(scale / 12, scale / 12, scale / 12));

	controlerNumber_ = join_number;

	//数値初期化
	reset();

	//コントローラーのデッドゾーンを設定
	SetJoypadDeadZone(controlerNumber_, 0.1);

	//ステートインスタンス化
	state_ = openState_();
}

/// <summary>
/// デストラクタ
/// </summary>
CharaBase::~CharaBase()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
}

/// <summary>
/// 更新
/// </summary>
void CharaBase::update(Routine* routine, shared_ptr<Stage> stage)
{
	//コントローラーの入力状態を取得する
	GetJoypadDirectInputState(controlerNumber_, &input);

	//状態によって行動を変える
	state_->update(this);

	//でばっぐリセット
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = 0.0f;
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(fan_, position_);
	draw();
}

/// <summary>
/// 描画
/// </summary>
void CharaBase::draw()const
{
	//デバッグ用
	//DrawFormatString(0, 300, GetColor(255, 0, 0), "px:%f,py:%f,pz:%f", position_.x, position_.y, position_.z);

	if (state_ == std::dynamic_pointer_cast<CharaState::FanState>(state_))
	{
		MV1DrawModel(fan_);
	}
	else if (state_ == std::dynamic_pointer_cast<CharaState::OpenState>(state_))
	{
		MV1DrawModel(openingUmbrella_);
	}
	else if (state_ == std::dynamic_pointer_cast<CharaState::CloseState>(state_))
	{
		MV1DrawModel(closingUmbrella_);
	}
}

/// <summary>
/// 変数をリセット
/// </summary>
void CharaBase::reset()
{
	if (controlerNumber_ == 1)
	{
		position_ = player1_init_position;
	}
	else if (controlerNumber_ == 2)
	{
		position_ = player2_init_position;
	}
	else if (controlerNumber_ == 3)
	{
		position_ = player3_init_position;
	}
	else if (controlerNumber_ == 4)
	{
		position_ = player4_init_position;
	}
	isTackle_		= false;
	tackleCount_	= 0.0f;
	tackleVector_	= VGet(0.0f, 0.0f, 0.0f);
	rotationAngleY_ = 0.0;
	rotaionMatrix_	= MGetIdent();
	isMovingtackle_ = false;
	isSwing_		= false;
	hp_				= max_hp;
	angleSwing_		= 0.00;
	fanMoveAngle_	= 90.0;
	isPrevButton_	= false;
	onTilePosition_ = VGet(0.0f, 0.0f, 0.0f);
}

/// <summary>
/// 移動
/// </summary>
void CharaBase::move()
{
	auto isNoneAction = !isTackle_ && !isSwing_;

	//早期リターン
	if (input.X == 0 && input.Y == 0)
	{
		return;
	}

	//スティックを傾けたら移動を決定
	VECTOR moveVector = VGet(0.0f, 0.0f, 0.0f);
	if (input.Y != 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.Y > 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.X > 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.X < 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	/*if (input.Y != 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	if (input.X != 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}*/

	//スティックの傾きからどのくらいモデルを回転させるか決定
	rotation();

	//スティックを傾けてる向きに移動
	rotaionMatrix_	= MGetRotY(rotationAngleY_ + agnle_shift_number);
	moveVector		= VTransform(moveVector, rotaionMatrix_);
	position_		= VAdd(position_, moveVector);

	//DrawFormatString(100,800,)
	//DrawFormatString(100, 700, GetColor(255, 255, 255), "ムーブベクター x:%f y:%f z:%f", moveVector.x, moveVector.y, moveVector.z);
}

/// <summary>
/// アクション：スイング
/// </summary>
void CharaBase::swing()
{
	//他アクションしてない時だけ
	if (!isSwing_ && input.Buttons[1] > 0 && !isTackle_)
	{
		isSwing_ = true;
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
void CharaBase::tackle()
{
	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingtackle_ = true;
		--tackleCount_;
		tackleMoving();
	}
	//Bボタンを押したら
	else if (input.Buttons[0] > 0 && !isMovingtackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			++tackleCount_;
		}

		//どの方向にタックルするかY軸の回転行列で決める
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);
	}

	//タックルをやめる
	stopTackle();

	//デバッグ用
	DrawFormatString(100, 300, GetColor(255, 255, 255), "タックル:%f", tackleCount_);
}

/// <summary>
/// タックル移動中
/// </summary>
/// <param name="rotation">どの方向にタックルするか決める回転行列</param>
void CharaBase::tackleMoving()
{
	VECTOR moveVector = VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotaionMatrix_);
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
void CharaBase::stopTackle()
{
	//カウントが０なるかタックル中にBを押したらやめる
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0)
	{
		isTackle_ = false;
		isMovingtackle_ = false;
		tackleCount_ = 0;
	}
}

/// <summary>
/// アクション：風
/// </summary>
void CharaBase::wind()
{
	//ZRとZLで移動
	moveFan();

	//デバッグ用
	DrawFormatString(100, 500, GetColor(255, 255, 255), "%f", fanMoveAngle_);
}

/// <summary>
/// 扇風機移動
/// </summary>
void CharaBase::moveFan()
{
	double radiun = fanMoveAngle_ * DX_PI / 180.0;
	if (input.Buttons[6] > 0)
	{
		double addAngleX = cos(radiun) * stage_radius;
		double addAngleZ = sin(radiun) * stage_radius;
		fanMoveAngle_ += fan_move_speed;
		position_.x = stage_center.x + addAngleX;
		position_.z = stage_center.z + addAngleZ;
	}
	if (input.Buttons[7] > 0)
	{
		double addAngleX = cos(radiun) * stage_radius;
		double addAngleZ = sin(radiun) * stage_radius;
		fanMoveAngle_ -= fan_move_speed;
		position_.x = stage_center.x + addAngleX;
		position_.z = stage_center.z + addAngleZ;
	}

	double tempRotation = atan2(position_.x, position_.z);
	//ステージの中心を向くようにモデルを回転
	MV1SetRotationXYZ(fan_, VGet(0.0f, tempRotation + DX_PI, 0.0f));
}

/// <summary>
/// 落下
/// </summary>
void CharaBase::fall()
{
	position_.y -= fall_speed;
}

/// <summary>
/// コントローラーのスティックの傾きに応じた3dモデルの回転
/// </summary>
void CharaBase::rotation()
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
	DrawFormatString(200, 200, GetColor(255, 255, 255), "角度:%f", rotationAngleY_);
}

/// <summary>
/// 扇風機に変身
/// </summary>
void CharaBase::transformFan()
{
	//一定の高さまで落ちたら
	if (position_.y < transform_position_y)
	{
		//state_ = make_shared<CharaState::FanState>();
		state_ = fanState_();
		position_.y = player_init_positionY;
		//落ちた瞬間に扇風機の移動をして扇風機の位置を設定する
		input.Buttons[6] = 1;
		moveFan();
	}
}

/// <summary>
/// 開いた状態から閉じた状態へ
/// </summary>
void CharaBase::changeOpenToClose()
{
	if (input.Buttons[2] > 0)
	{
		if (!isPrevButton_ && !isTackle_)
		{
			//state_ = make_shared<CharaState::CloseState>();
			state_ = closeState_();
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_ = false;
	}
}

/// <summary>
/// 閉じた状態から開いた状態へ
/// </summary>
void CharaBase::changeCloseToOpen()
{
	if (input.Buttons[2] > 0)
	{
		if (!isPrevButton_)
		{
			//state_ = make_shared<CharaState::OpenState>();
			state_ = openState_();
		}
		isPrevButton_ = true;
	}
	else
	{
		isPrevButton_ = false;
	}
}

/// <summary>
/// タイルの上にいるときのタイル座標を保存する
/// </summary>
/// <param name="tilePosition">タイル座標</param>
void CharaBase::SetonTilePosition(VECTOR tilePosition)
{
	onTilePosition_ = VGet(tilePosition.x, tilePosition.y, tilePosition.z);
}

void CharaBase::SetonTilePositionX_(short tileNumberX)
{
	onTileNumberX_ = tileNumberX;
}

void CharaBase::SetonTilePositionY_(short tileNumberY)
{
	onTileNumberY_ = tileNumberY;
}