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
		inverseUmbrella_ = MV1LoadModel("3dmodel/umbrella/inverseUmbllera.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 2:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen2.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose2.mv1");
		inverseUmbrella_ = MV1LoadModel("3dmodel/umbrella/inverseUmbllera2.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 3:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen3.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose3.mv1");
		inverseUmbrella_ = MV1LoadModel("3dmodel/umbrella/inverseUmbllera3.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;

	case 4:
		openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen4.mv1");
		closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose4.mv1");
		inverseUmbrella_ = MV1LoadModel("3dmodel/umbrella/inverseUmbllera4.mv1");
		fan_ = MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
		break;
	}
	
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(inverseUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(fan_, VGet(scale / 12, scale / 12, scale / 12));

	controlerNumber_ = join_number;

	//数値初期化
	reset();

	//音初期化
	chargeSound_	= LoadSoundMem("sound/charge.mp3");
	ChangeVolumeSoundMem(charge_sound_volume, chargeSound_);
	hitSound_		= LoadSoundMem("sound/hit.mp3");
	ChangeVolumeSoundMem(hit_sound_volume, hitSound_);
	windSound_		= LoadSoundMem("sound/wind.mp3");
	ChangeVolumeSoundMem(wind_sound_volume, windSound_);
	respawnSound_	= LoadSoundMem("sound/respawn.mp3");
	ChangeVolumeSoundMem(respawn_sound_volume, respawnSound_);
	inverseSound_	= LoadSoundMem("sound/inverseUmbrella.mp3");
	ChangeVolumeSoundMem(inverse_sound_volume, inverseSound_);
	changeFanSound_ = LoadSoundMem("sound/changeFan.mp3");
	ChangeVolumeSoundMem(change_fan_sound_volume, changeFanSound_);
	tackleSound_	= LoadSoundMem("sound/tackle.mp3");
	ChangeVolumeSoundMem(tackle_sound_volume, tackleSound_);

	//コントローラーのデッドゾーンを設定
	SetJoypadDeadZone(controlerNumber_, 0.1);

	onConstructFrame_ = true;
}

/// <summary>
/// デストラクタ
/// </summary>
CharaBase::~CharaBase()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
	MV1DeleteModel(inverseUmbrella_);
	MV1DeleteModel(fan_);
	DeleteSoundMem(hitSound_);
	DeleteSoundMem(chargeSound_);
	DeleteSoundMem(windSound_);
	DeleteSoundMem(respawnSound_);
	DeleteSoundMem(inverseSound_);
	DeleteSoundMem(changeFanSound_);
	DeleteSoundMem(tackleSound_);
	state_ = nullptr;
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
	moveVector_		= VGet(0.0f, 0.0f, 0.0f);
	collisionCenterPosition_ = VGet(0.0f, 0.0f, 0.0f);
	mass_			= init_mass;
	isChargeTackle_ = false;
	canLoopSound_	= false;
	isHit_			= false;
	state_			= openState_();
	isFalling_		= false;
	knockBackCount_ = 0;
	isMovingTackle_ = false;
	isKnockBack_	= false;
	windPosition_	= VGet(0.0f, 0.0f, 0.0f);
	canSpawnWind_	= true;
	windMoveVector_ = VGet(0.0f, 0.0f, 0.0f);
	fanAngle_		= 0.0;
	windAngle_		= 0.0;
	windCount_		= 0;
	canRespawn_		= false;
	respawnPosition_= VGet(0.0f, 0.0f, 0.0f);
	wasTrumpet_		= false;
	rad_			= 0.0f;
	canChangeFan_	= false;
	onConstructFrame_ = false;
	waitHitCount_	= 0;
	tackleEffectPos_ = VGet(0.0f, 0.0f, 0.0f);
	isOneSE_		= false;
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

	setPosition();
}

void CharaBase::setPosition()
{
	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(inverseUmbrella_, position_);
	MV1SetPosition(fan_, position_);
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
	else
	{
		MV1DrawModel(inverseUmbrella_);
	}
}


/// <summary>
/// 移動
/// </summary>
void CharaBase::move()
{
	auto isNoneAction = !isTackle_ && !isSwing_;

	//早期リターン
	if (input.X == 0 && input.Y == 0 || isKnockBack_ || position_.y < 0.0f)
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
}

/// <summary>
/// アクション：タックル
/// </summary>
void CharaBase::tackle()
{
	if (input.Buttons[1] > 0 && !isMovingtackle_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input.Buttons[0] > 0 && !isMovingtackle_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		input.Buttons[0] > 0 && !isMovingtackle_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE)
	{
		isChargeTackle_ = true;
	}
	else
	{
		isChargeTackle_ = false;
	}

	//ボタンを押してはなしたら
	if (tackleCount_ > 0 && input.Buttons[1] == 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		tackleCount_ > 0 && input.Buttons[0] == 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		tackleCount_ > 0 && input.Buttons[0] == 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE)
	{
		isMovingtackle_ = true;
		StopSoundMem(chargeSound_);
		canLoopSound_	= false;
		--tackleCount_;
		tackleMoving();

		if (!isOneSE_)
		{
			PlaySoundMem(tackleSound_, DX_PLAYTYPE_BACK);
			isOneSE_ = true;
		}

		//アクションするとhpが減る
		subHp();
	}
	//Bボタンを押したら
	else if (isChargeTackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			tackleCount_++;
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
	moveVector_		= VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotaionMatrix_);
	position_		= VAdd(position_, moveVector_);
	mass_			= tackle_mass;
	isMovingTackle_ = true;
}

/// <summary>
/// タックルをやめる
/// </summary>
void CharaBase::stopTackle()
{
	//カウントが０なるかタックル中にBを押したらやめる
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[1] > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE)
	{
		isTackle_		= false;
		isMovingtackle_ = false;
		tackleCount_	= 0;
		mass_			= init_mass;
		isMovingTackle_ = false;
		StopSoundMem(tackleSound_);
		isOneSE_		= false;
	}
}

/// <summary>
/// アクション：風
/// </summary>
void CharaBase::wind()
{
	//風を発生させる
	if (input.Buttons[1] > 0 && canSpawnWind_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input.Buttons[0] > 0 && canSpawnWind_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		input.Buttons[0] > 0 && canSpawnWind_ && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE)
	{
		canSpawnWind_	= false;
		windPosition_	= position_;
		windMoveVector_ = VSub(stage_center, position_);
		windAngle_		= fanAngle_;
		PlaySoundMem(windSound_, DX_PLAYTYPE_BACK, TRUE);
	}

	//移動
	if (!canSpawnWind_)
	{
		++windCount_;
		windPosition_ = VAdd(windPosition_, VGet(windMoveVector_.x / 35, windMoveVector_.y / 35, windMoveVector_.z / 35));

		//風を消す
		if (max_wind_count < windCount_)
		{
			canSpawnWind_	= true;
			windCount_		= 0;
			StopSoundMem(windSound_);
		}
	}
}

/// <summary>
/// 扇風機移動
/// </summary>
void CharaBase::moveFan()
{
	//円運動する
	double radiun = fanMoveAngle_ * DX_PI / 180.0;
	if (input.Buttons[6] > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input.Z > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		input.Z > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE ||
		input.Z > 2000 ||
		input.Buttons[6] > 2000)
	{
		double addAngleX = cos(radiun) * stage_radius;
		double addAngleZ = sin(radiun) * stage_radius;
		fanMoveAngle_ += fan_move_speed;
		position_.x = stage_center.x + addAngleX;
		position_.z = stage_center.z + addAngleZ;
	}
	if (input.Buttons[7] > 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_SWITCH_PRO_CTRL ||
		input.Z < 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_360 ||
		input.Z < 0 && GetJoypadType(controlerNumber_) == DX_PADTYPE_XBOX_ONE)
	{
		double addAngleX = cos(radiun) * stage_radius;
		double addAngleZ = sin(radiun) * stage_radius;
		fanMoveAngle_ -= fan_move_speed;
		position_.x = stage_center.x + addAngleX;
		position_.z = stage_center.z + addAngleZ;
	}

	fanAngle_ = atan2(position_.x - stage_center.x, position_.z - stage_center.z);
	//ステージの中心を向くようにモデルを回転
	MV1SetRotationXYZ(fan_, VGet(0.0f, fanAngle_ + DX_PI, 0.0f));

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

		//MV1SetRotationXYZ(closingUmbrella_, VGet(0.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
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
		changeFan();
	}
}

void CharaBase::changeFan()
{
	state_ = fanState_();
	position_.y = player_init_positionY;

	//落ちた瞬間に扇風機の移動をして扇風機の位置を設定する
	input.Buttons[6]	= 2025;
	input.Z				= 2025;
	moveFan();

	isChargeTackle_ = false;
	isHit_			= false;
	isFalling_		= false;
	canSpawnWind_	= true;
	canChangeFan_	= true;
	windCount_		= 0;
	StopSoundMem(chargeSound_);
	PlaySoundMem(changeFanSound_, DX_PLAYTYPE_BACK, TRUE);
}

void CharaBase::cannotChangeFan()
{
	canChangeFan_ = false;
}

/// <summary>
/// 何番目のタイルにいるかセット（Ｘ）A*関係
/// </summary>
/// <param name="tileNumberX">タイルが何番目かｘ</param>
void CharaBase::SetonTilePositionX_(short tileNumberX)
{
	onTileNumberX_ = tileNumberX;
}

/// <summary>
/// 何番目のタイルにいるかをセット（Ｙ）A*関係
/// </summary>
/// <param name="tileNumberY">タイルが何番目かｙ</param>
void CharaBase::SetonTilePositionY_(short tileNumberY)
{
	onTileNumberY_ = tileNumberY;
}

/// <summary>
/// ノックバックを決定する
/// </summary>
/// <param name="otherChara">判定するほかのキャラ</param>
void CharaBase::decideKnockBackWithChara(std::shared_ptr<CharaBase> otherChara)
{
	//開き状態のときに判定をする
	if (state_== openState_())
	{
		//2点間の距離を出す
		float dx		= otherChara->GetcollisionCenterPosition_().x - collisionCenterPosition_.x;
		float dz		= otherChara->GetcollisionCenterPosition_().z - collisionCenterPosition_.z;
		float distance	= CalculateDistance<float>(collisionCenterPosition_, otherChara->GetcollisionCenterPosition_());

		//距離が直径未満だったら
		if (distance < collision_radius * 2 && otherChara->Getstate_() == openState_())
		{
			// 衝突の法線ベクトル
			VECTOR normalLine = VGet(0.0f, 0.0f, 0.0f);
			normalLine.x = dx / distance;
			normalLine.z = dz / distance;

			//めり込み量
			float overlap = collision_radius * 2 - distance;

			// 重なり解消のための位置補正
			VECTOR knockBackVector	= VScale(normalLine, overlap);
			knockBackVector			= VNorm(knockBackVector);
			collisionCenterPosition_.x -= knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent;
			collisionCenterPosition_.z -= knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent;

			// 自キャラへの反発速度適用
			moveVector_.x = -(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent);
			moveVector_.z = -(knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);
			
			//相手キャラの当たり判定の座標を押し戻す
			otherChara->AdjustPositionAfterCollision(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent, knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);
			// 相手キャラへの反発速度適用
			otherChara->AddImpulse(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent, knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);

			//ヒット音
			PlaySoundMem(hitSound_, DX_PLAYTYPE_BACK, TRUE);

			//フラグをtrueに
			changeHitNowFlag();
			otherChara->changeHitNowFlag();

			//コントローラーを振動させる
			StartJoypadVibration(controlerNumber_, vibration_power, vibration_time);
			StartJoypadVibration(otherChara->GetcontrolerNumber_(), vibration_power, vibration_time);
		}
		
		//ヒットが終わるのをカウントで待つ
		if (isHit_)
		{
			++waitHitCount_;
		}
		if(waitHitCount_ > 3)
		{
			isHit_			= false;
			waitHitCount_	= 0;
		}
	}
}

/// <summary>
/// 移動量にふっとばし量をいれる
/// </summary>
/// <param name="impulseX">ふっとばし量ｘ</param>
/// <param name="impulseZ">ふっとばし量ｚ</param>
void CharaBase::AddImpulse(float impulseX, float impulseZ)
{
	moveVector_.x = impulseX;
	moveVector_.z = impulseZ;
}

/// <summary>
/// コリジョンの座標を調整
/// </summary>
/// <param name="amountX">調整量ｘ</param>
/// <param name="amountZ">調整量ｚ</param>
void CharaBase::AdjustPositionAfterCollision(float amountX, float amountZ)
{
	collisionCenterPosition_.x += amountX;
	collisionCenterPosition_.z += amountZ;
}

/// <summary>
/// ノックバックする
/// </summary>
void CharaBase::knockBackNow()
{
	if(isKnockBack_)
	{
		//カウントが一定になるかタックル移動中だったらノックバックをやめる
		++knockBackCount_;
		if (knockBackCount_ > knock_back_max_count || isMovingTackle_)
		{
			knockBackCount_	= 0;
			isKnockBack_	= false;
			return;
		}

		position_ = VAdd(position_, moveVector_);
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
	VECTOR tempVector2 = VTransform(VScale(collision_adjust_position, 2.0f), rotaionMatrix_);
	tackleEffectPos_ = VAdd(position_, tempVector2);
}

void CharaBase::changeHitNowFlag()
{
	isKnockBack_	= true;
	isHit_			= true;
}

void CharaBase::collisionWindWithChara(std::shared_ptr<CharaBase> otherChara, std::shared_ptr<Stage> stage)
{
	//風が発生しているときで相手が開いている状態のときだけ
	if (!canSpawnWind_ && otherChara->Getstate_() == openState_() && state_ == fanState_())
	{
		float distance = CalculateDistance<float>(windPosition_, otherChara->GetcollisionCenterPosition_());

		//距離が2つの半径を足した数値未満だったら
		if (distance < collision_radius + collision_radius_wind)
		{
			//風で押し出す
			otherChara->hitWind(windMoveVector_);

			//コントローラーを振動させる
			StartJoypadVibration(otherChara->GetcontrolerNumber_(), vibration_power, vibration_time);
			
			//敵のhpを減らす
			otherChara->subHp();
			otherChara->subHp();

			//復活座標をセット
			respawnPosition_ = decideRespawnPosition(stage);

			//敵を倒した時の処理
			onBeatedChara(otherChara, stage);
		}
	}
}

void CharaBase::hitWind(VECTOR windVector)
{
	position_ = VAdd(position_, VScale(windVector, 0.017f));
	collisionCenterPosition_ = VAdd(collisionCenterPosition_, VScale(windVector, 0.017f));
}

VECTOR CharaBase::decideRespawnPosition(std::shared_ptr<Stage> stage)
{
	VECTOR tempPosition = VGet(0.0f, 0.0f, 0.0f);

	while (true)
	{
		short randomTileX = GetRand(tile_number - 1) + 1;
		short randomTileY = GetRand(tile_number - 1) + 1;

		if (stage->GetcanExist_()[randomTileY][randomTileX])
		{
			tempPosition = stage->Getposition_()[randomTileY][randomTileX];
			break;
		}
	}

	return tempPosition;
}

void CharaBase::respawn()
{
	//復活フラグがtrueだったら復活
	if (canRespawn_)
	{
		canRespawn_ = false;

		position_	= respawnPosition_;
		state_		= openState_();

		PlaySoundMem(respawnSound_, DX_PLAYTYPE_BACK, TRUE);
	}
}

void CharaBase::onBeatedChara(std::shared_ptr<CharaBase> otherChara, std::shared_ptr<Stage> stage)
{
	//トランペットになったことなかったら
	if (!wasTrumpet_)
	{
		//相手をステージ外に押し出すかhpを０にする
		if (!stage->GetcanExist_()[otherChara->GetonTileNumberY_()][otherChara->GetonTileNumberX_()] ||
			otherChara->Gethp_() <= 0)
		{
			canRespawn_ = true;
		}
	}
}

/// <summary>
/// hpが減る
/// </summary>
void CharaBase::subHp()
{
	--hp_;
}

/// <summary>
/// ラッパがさになる
/// </summary>
void CharaBase::changeTrumpet()
{
	//hpが0以下になったラッパになる
	if (hp_ <= 0)
	{
		state_		= TrumpetState_();
		wasTrumpet_ = true;
		PlaySoundMem(inverseSound_, DX_PLAYTYPE_BACK, TRUE);
		isMovingTackle_ = false;
	}
}

void CharaBase::stopSound()
{
	StopSoundMem(inverseSound_);
}

/// <summary>
/// プレイヤーが振動する
/// </summary>
void CharaBase::vibration()
{
	rad_ += static_cast<float>((DX_PI / 180) * 100);

	position_.x = position_.x + sinf(rad_);
	position_.z = position_.z + sinf(rad_);
}

/// <summary>
/// コンストラクタしたフレームが終わる時を表す関数
/// </summary>
void CharaBase::constructFrameEnd()
{
	onConstructFrame_ = false;
}

void CharaBase::decideMoveAngle(VECTOR movePosition)
{
	rotationAngleY_ = atan2(static_cast<double>(movePosition.x - position_.x), static_cast<double>(movePosition.z - position_.z)) - 90 * DX_PI /180;
}