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
	MV1DeleteModel(fan_);
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
	rotaionMatrix_	= MGetRotY(rotationAngleY_ + agnle_shift_number);
	moveVector_		= VTransform(moveVector_, rotaionMatrix_);
	position_		= VAdd(position_, moveVector_);

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
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0)
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

void CharaBase::pushBackWithChara(std::shared_ptr<CharaBase> otherChara)
{
	if (state_ != fanState_())
	{
		float dx = otherChara->GetcollisionCenterPosition_().x - collisionCenterPosition_.x;
		float dy = otherChara->GetcollisionCenterPosition_().y - collisionCenterPosition_.y;
		float dz = otherChara->GetcollisionCenterPosition_().z - collisionCenterPosition_.z;
		float distance = CalculateDistance<float>(collisionCenterPosition_, otherChara->GetcollisionCenterPosition_());

		if (distance < collision_radius * 2)
		{
			//// 衝突の法線ベクトル
			//float nx = dx / distance;
			//float ny = dy / distance;
			//float nz = dz / distance;

			//// 2球間の相対速度
			//float vx_rel = GetmoveVector_().x - moveVector_.x;
			//float vy_rel = GetmoveVector_().y - moveVector_.y;
			//float vz_rel = GetmoveVector_().z - moveVector_.z;

			//// 法線方向の相対速度
			//float velocityAlongNormal = vx_rel * nx + vy_rel * ny + vz_rel * nz;

			//// 反発係数（完全弾性衝突と仮定）
			//if (velocityAlongNormal > 0) return;  // すでに離れようとしている場合は何もしない

			//// 衝突後の速度更新（弾性衝突）
			//float restitution = 1.0f; // 完全弾性衝突

			//// 質量の比に基づいて速度の変化量を計算
			//float impulse = -(1.0f + restitution) * velocityAlongNormal / (1.0f / mass_ + 1.0f / otherChara->Getmass_());
			//float impulseX = impulse * nx;
			//float impulseZ = impulse * nz;

			//// 速度の更新
			//moveVector_.x -= impulseX / mass_;
			//moveVector_.z -= impulseZ / mass_;

			////タックル中だったら相手を吹っ飛ばす
			//float overlap = collision_radius * 2 - distance;
			//if (isMovingtackle_)
			//{
			//	otherChara->blownAway(nx, nz, overlap, impulseX, impulseZ);

			//	//タックルをやめる
			//	isTackle_ = false;
			//	isMovingtackle_ = false;
			//	tackleCount_ = 0;
			//}
			//else
			//{
			//	// 衝突後の位置調整（重なりを解消）
			//	otherChara->positionAdjustmentAfterHit(nx, nz, overlap, impulseX, impulseZ);
			//	collisionCenterPosition_.x -= nx * overlap / 2;
			//	collisionCenterPosition_.z -= nz * overlap / 2;
			//	position_.x -= nx * overlap / 2;
			//	position_.z -= nz * overlap / 2;
			//}

			// 衝突の法線ベクトル
			float nx = dx / distance;
			float ny = dy / distance;
			float nz = dz / distance;

			// 両者の速度ベクトル
			VECTOR myVelocity = moveVector_;
			VECTOR otherVelocity = otherChara->GetmoveVector_();

			// 相対速度ベクトル
			VECTOR relativeVelocity = {
				otherVelocity.x - myVelocity.x,
				otherVelocity.y - myVelocity.y,
				otherVelocity.z - myVelocity.z
			};

			// 法線方向の相対速度
			float velocityAlongNormal = relativeVelocity.x * nx +
				relativeVelocity.y * ny +
				relativeVelocity.z * nz;

			// すでに離れようとしているなら何もしない
			if (velocityAlongNormal > 0) return;

			// 弾性係数（1.0 = 完全弾性）
			float restitution = 5.0f;

			// 質量取得
			float m1 = mass_;
			float m2 = otherChara->Getmass_();

			// インパルススカラー
			float impulseScalar = -(1.0f + restitution) * velocityAlongNormal / (1.0f / m1 + 1.0f / m2);

			// インパルスベクトル
			float impulseX = impulseScalar * nx;
			float impulseY = impulseScalar * ny;
			float impulseZ = impulseScalar * nz;

			// 自キャラへの反発速度適用
			moveVector_.x -= (impulseX / m1);
			moveVector_.y -= (impulseY / m1);
			moveVector_.z -= (impulseZ / m1);

			position_ = VAdd(position_, moveVector_);

			float overlap = collision_radius * 2 - distance;

			// 相手キャラへの反発速度適用
			otherChara->AddImpulse(impulseX / m2, impulseY / m2, impulseZ / m2);

			// 重なり解消のための位置補正
			collisionCenterPosition_.x -= nx * overlap / 2;
			collisionCenterPosition_.z -= nz * overlap / 2;

			position_.x -= nx * overlap / 2;
			position_.z -= nz * overlap / 2;

			otherChara->AdjustPositionAfterCollision(nx, ny, nz, overlap / 2);
		}
	}
}

void CharaBase::positionAdjustmentAfterHit(float nx, float nz, float overlap, float impulseX, float impulseZ)
{
	moveVector_.x -= impulseX * mass_;
	moveVector_.z -= impulseZ * mass_;
	collisionCenterPosition_.x += nx * overlap / 2;
	collisionCenterPosition_.z += nz * overlap / 2;
	position_.x += nx * overlap / 2;
	position_.z += nz * overlap / 2;
}

/// <summary>
/// 吹っ飛ばされる
/// </summary>
void CharaBase::blownAway(float nx, float nz, float overlap, float impulseX, float impulseZ)
{
	moveVector_.x -= impulseX * mass_;
	moveVector_.z -= impulseZ * mass_;

	collisionCenterPosition_.x += nx * overlap * blow_away_percent;
	collisionCenterPosition_.z += nz * overlap * blow_away_percent;
	position_.x += nx * overlap * blow_away_percent;
	position_.z += nz * overlap * blow_away_percent;
}

void CharaBase::AddImpulse(float impulseX, float impulseY, float impulseZ)
{
	moveVector_.x += impulseX;
	moveVector_.z += impulseZ;

	position_ = VAdd(position_, moveVector_);
}

void CharaBase::AdjustPositionAfterCollision(float nx, float ny, float nz, float amount)
{
	collisionCenterPosition_.x += nx * amount;
	collisionCenterPosition_.z += nz * amount;

	position_.x += nx * amount;
	position_.z += nz * amount;
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