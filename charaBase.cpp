#include"Dxlib.h"
#include"charaBase.h"
#include<cmath>
#include"stage.h"
#include"routine.h"
#include"calculateDistance.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="join_number">何Pかを表す数字</param>
CharaBase::CharaBase(const int join_number)
{
	//3dモデル読み込み
	switch (join_number)
	{
	case 1:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 2:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen2.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose2.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 3:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen3.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose3.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 4:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen4.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose4.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;
	}
	
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(fan_, VGet(scale / 12, scale / 12, scale / 12));

	chargeSound_ = LoadSoundMem("sound/charge.mp3");
	ChangeVolumeSoundMem(charge_sound_volume, chargeSound_);

	controlerNumber_ = join_number;

	//数値初期化
	reset();

	hitSound_ = LoadSoundMem("sound/hit.mp3");
	ChangeVolumeSoundMem(hit_sound_volume, hitSound_);

	//コントローラーのデッドゾーンを設定
	SetJoypadDeadZone(controlerNumber_, 0.1);
}

/// <summary>
/// デストラクタ
/// </summary>
CharaBase::~CharaBase()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
	MV1DeleteModel(fan_);
	DeleteSoundMem(hitSound_);
	DeleteSoundMem(chargeSound_);
}

/// <summary>
/// 更新
/// </summary>
void CharaBase::update(Routine* routine, std::shared_ptr<Stage> stage)
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
	moveVector_		= VGet(0.0f, 0.0f, 0.0f);
	collisionCenterPosition_ = VGet(0.0f, 0.0f, 0.0f);
	mass_			= init_mass;
	isChargeTackle_ = false;
	canLoopSound_	= false;
	isHit_			= false;
	state_			= openState_();
	isKnockBack_	= false;
	isFalling_		= false;
	knockBackCount_ = 0;
}

/// <summary>
/// 移動
/// </summary>
void CharaBase::move()
{
	auto isNoneAction = !isTackle_ && !isSwing_;

	//早期リターン
	if (input.X == 0 && input.Y == 0 || isKnockBack_ /*|| position_.y < 0.0f*/)
	{
		return;
	}

	//スティックを傾けたら移動を決定
	moveVector_ = VGet(0.0f, 0.0f, 0.0f);
	if (input.Y != 0 && isNoneAction)
	{
		moveVector_ = VAdd(moveVector_, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.Y > 0 && isNoneAction)
	{
		moveVector_ = VAdd(moveVector_, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.X > 0 && isNoneAction)
	{
		moveVector_ = VAdd(moveVector_, VGet(move_speed, 0.0f, move_speed));
	}
	else if (input.X < 0 && isNoneAction)
	{
		moveVector_ = VAdd(moveVector_, VGet(move_speed, 0.0f, move_speed));
	}

	//スティックの傾きからどのくらいモデルを回転させるか決定
	rotation();

	//スティックを傾けてる向きに移動
	rotaionMatrix_		= MGetRotY(rotationAngleY_ + agnle_shift_number);
	moveVector_			= VTransform(moveVector_, rotaionMatrix_);
	position_			= VAdd(position_, moveVector_);

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
	if (input.Buttons[0] > 0 && !isMovingtackle_)
	{
		isChargeTackle_ = true;
	}
	else
	{
		isChargeTackle_ = false;
	}

	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingtackle_ = true;
		StopSoundMem(chargeSound_);
		canLoopSound_	= false;
		--tackleCount_;
		tackleMoving();
	}
	//Bボタンを押したら
	else if (isChargeTackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			++tackleCount_;
		}

		//どの方向にタックルするかY軸の回転行列で決める
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);

		if (!canLoopSound_)
		{
			PlaySoundMem(chargeSound_, DX_PLAYTYPE_LOOP, TRUE);
			canLoopSound_ = true;
		}
	}

	//タックルをやめる
	stopTackle();

	//デバッグ用
	//DrawFormatString(100, 300, GetColor(255, 255, 255), "タックル:%f", tackleCount_);
}

/// <summary>
/// タックル移動中
/// </summary>
/// <param name="rotation">どの方向にタックルするか決める回転行列</param>
void CharaBase::tackleMoving()
{
	moveVector_ = VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotaionMatrix_);
	position_	= VAdd(position_, moveVector_);
	mass_		= tackle_mass;

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
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0 || isHit_)
	{
		isTackle_		= false;
		isMovingtackle_ = false;
		tackleCount_	= 0;
		mass_			= init_mass;
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
	//DrawFormatString(100, 500, GetColor(255, 255, 255), "%f", fanMoveAngle_);
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

	//オーバーフロー対策
	if (fanMoveAngle_ > 452.5 || fanMoveAngle_ < -270.5)
	{
		fanMoveAngle_ = 92.5f;
	}
}

/// <summary>
/// 落下
/// </summary>
void CharaBase::fall()
{
	position_.y -= fall_speed;
	isFalling_	= true;
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
	//DrawFormatString(200, 200, GetColor(255, 255, 255), "角度:%f", rotationAngleY_);
}

/// <summary>
/// 扇風機に変身
/// </summary>
void CharaBase::transformFan()
{
	//一定の高さまで落ちたら
	if (position_.y < transform_position_y)
	{
		state_ = fanState_();
		position_.y = player_init_positionY;

		//落ちた瞬間に扇風機の移動をして扇風機の位置を設定する
		input.Buttons[6] = 1;
		moveFan();

		isChargeTackle_ = false;
		isHit_			= false;
		isFalling_		= false;
		StopSoundMem(chargeSound_);
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

void CharaBase::decideKnockWithChara(std::shared_ptr<CharaBase> otherChara)
{
	if (state_ != fanState_())
	{
		//2点間の距離を出す
		float dx = otherChara->GetcollisionCenterPosition_().x - collisionCenterPosition_.x;
		float dz = otherChara->GetcollisionCenterPosition_().z - collisionCenterPosition_.z;
		float distance = CalculateDistance<float>(collisionCenterPosition_, otherChara->GetcollisionCenterPosition_());

		//距離が直径未満だったら
		if (distance < collision_radius * 2)
		{
			// 衝突の法線ベクトル
			float nx = dx / distance;
			float nz = dz / distance;

			//めり込み量
			float overlap = collision_radius * 2 - distance;

			// 重なり解消のための位置補正
			collisionCenterPosition_.x -= nx * overlap / blow_away_percent;
			collisionCenterPosition_.z -= nz * overlap / blow_away_percent;

			// 自キャラへの反発速度適用
			moveVector_.x -= nx * overlap / blow_away_percent;
			moveVector_.z -= nz * overlap / blow_away_percent;
		
			//相手キャラの座標を押し戻す
			otherChara->AdjustPositionAfterCollision(nx, nz, overlap / blow_away_percent);
			// 相手キャラへの反発速度適用
			otherChara->AddImpulse(nx * overlap / blow_away_percent, nz * overlap / blow_away_percent);

			//ヒット音
			PlaySoundMem(hitSound_, DX_PLAYTYPE_BACK, TRUE);

			//フラグをtrueに
			isHit_			= true;
			isKnockBack_	= true;
		}
		else
		{
			isHit_ = false;
		}
	}
}

void CharaBase::AddImpulse(float impulseX, float impulseZ)
{
	moveVector_.x	+= impulseX;
	moveVector_.z	+= impulseZ;
}

void CharaBase::AdjustPositionAfterCollision(float nx, float nz, float amount)
{
	collisionCenterPosition_.x += nx * amount;
	collisionCenterPosition_.z += nz * amount;
}

void CharaBase::knockBackNow()
{
	if(isKnockBack_)
	{
		position_ = VAdd(position_, VGet(moveVector_.x, 0.0f, moveVector_.z));

		//カウントが一定になるまでノックバックする
		++knockBackCount_;
		if (knockBackCount_ > knock_back_max_count)
		{
			knockBackCount_ = 0;
			isKnockBack_	= false;
		}
	}
}

/// <summary>
/// 当たり判定を３dモデルに応じて回転させる
/// </summary>
void CharaBase::collisionRotation()
{
	MATRIX tempMatrix = MGetRotY(rotationAngleY_);
	VECTOR tempVector = VTransform(collision_adjust_position, rotaionMatrix_);
	collisionCenterPosition_ = VAdd(position_, tempVector);
}