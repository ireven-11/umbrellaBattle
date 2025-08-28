#include"Dxlib.h"
#include"charaBase.h"
#include<cmath>
#include"stage.h"
#include"routine.h"
#include"calculateDistance.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="join_number">��P����\������</param>
CharaBase::CharaBase(const int join_number)
{
	//3d���f���ǂݍ���
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

	//���l������
	reset();

	//��������
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

	//�R���g���[���[�̃f�b�h�]�[����ݒ�
	SetJoypadDeadZone(controlerNumber_, 0.1);

	onConstructFrame_ = true;
}

/// <summary>
/// �f�X�g���N�^
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
/// �ϐ������Z�b�g
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
/// �X�V
/// </summary>
void CharaBase::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	//�R���g���[���[�̓��͏�Ԃ��擾����
	GetJoypadDirectInputState(controlerNumber_, &input);

	//��Ԃɂ���čs����ς���
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
/// �`��
/// </summary>
void CharaBase::draw()const
{
	//�f�o�b�O�p
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
/// �ړ�
/// </summary>
void CharaBase::move()
{
	auto isNoneAction = !isTackle_ && !isSwing_;

	//�������^�[��
	if (input.X == 0 && input.Y == 0 || isKnockBack_ || position_.y < 0.0f)
	{
		return;
	}

	//�X�e�B�b�N���X������ړ�������
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

	//�X�e�B�b�N�̌X������ǂ̂��炢���f������]�����邩����
	rotation();

	//�X�e�B�b�N���X���Ă�����Ɉړ�
	rotaionMatrix_		= MGetRotY(rotationAngleY_ + agnle_shift_number);
	moveVector_			= VTransform(moveVector_, rotaionMatrix_);
	position_			= VAdd(position_, moveVector_);
}

/// <summary>
/// �A�N�V�����F�^�b�N��
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

	//�{�^���������Ă͂Ȃ�����
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

		//�A�N�V���������hp������
		subHp();
	}
	//B�{�^������������
	else if (isChargeTackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			tackleCount_++;
		}

		//�ǂ̕����Ƀ^�b�N�����邩Y���̉�]�s��Ō��߂�
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);

		if (!canLoopSound_)
		{
			PlaySoundMem(chargeSound_, DX_PLAYTYPE_LOOP, TRUE);
			canLoopSound_ = true;
		}
	}

	//�^�b�N������߂�
	stopTackle();

	//�f�o�b�O�p
	//DrawFormatString(100, 300, GetColor(255, 255, 255), "�^�b�N��:%f", tackleCount_);
}

/// <summary>
/// �^�b�N���ړ���
/// </summary>
/// <param name="rotation">�ǂ̕����Ƀ^�b�N�����邩���߂��]�s��</param>
void CharaBase::tackleMoving()
{
	moveVector_		= VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotaionMatrix_);
	position_		= VAdd(position_, moveVector_);
	mass_			= tackle_mass;
	isMovingTackle_ = true;
}

/// <summary>
/// �^�b�N������߂�
/// </summary>
void CharaBase::stopTackle()
{
	//�J�E���g���O�Ȃ邩�^�b�N������B�����������߂�
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
/// �A�N�V�����F��
/// </summary>
void CharaBase::wind()
{
	//���𔭐�������
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

	//�ړ�
	if (!canSpawnWind_)
	{
		++windCount_;
		windPosition_ = VAdd(windPosition_, VGet(windMoveVector_.x / 35, windMoveVector_.y / 35, windMoveVector_.z / 35));

		//��������
		if (max_wind_count < windCount_)
		{
			canSpawnWind_	= true;
			windCount_		= 0;
			StopSoundMem(windSound_);
		}
	}
}

/// <summary>
/// ��@�ړ�
/// </summary>
void CharaBase::moveFan()
{
	//�~�^������
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
	//�X�e�[�W�̒��S�������悤�Ƀ��f������]
	MV1SetRotationXYZ(fan_, VGet(0.0f, fanAngle_ + DX_PI, 0.0f));

	//�I�[�o�[�t���[�΍�
	if (fanMoveAngle_ > 452.5 || fanMoveAngle_ < -270.5)
	{
		fanMoveAngle_ = 92.5f;
	}
}

/// <summary>
/// ����
/// </summary>
void CharaBase::fall()
{
	position_.y -= fall_speed;
	isFalling_	= true;
}

/// <summary>
/// �R���g���[���[�̃X�e�B�b�N�̌X���ɉ�����3d���f���̉�]
/// </summary>
void CharaBase::rotation()
{
	//�A�N�V���������ĂȂ�������
	if (!isMovingtackle_ && !isSwing_)
	{
		//�X�e�B�b�N�̓|��Ă鐔�l����p�x�����߂�
		rotationAngleY_ = atan2(static_cast<double>(input.Y), static_cast<double>(input.X));

		//MV1SetRotationXYZ(closingUmbrella_, VGet(0.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
	}

	//�f�o�b�O�p
	//DrawFormatString(200, 200, GetColor(255, 255, 255), "�p�x:%f", rotationAngleY_);
}

/// <summary>
/// ��@�ɕϐg
/// </summary>
void CharaBase::transformFan()
{
	//���̍����܂ŗ�������
	if (position_.y < transform_position_y)
	{
		changeFan();
	}
}

void CharaBase::changeFan()
{
	state_ = fanState_();
	position_.y = player_init_positionY;

	//�������u�Ԃɐ�@�̈ړ������Đ�@�̈ʒu��ݒ肷��
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
/// ���Ԗڂ̃^�C���ɂ��邩�Z�b�g�i�w�jA*�֌W
/// </summary>
/// <param name="tileNumberX">�^�C�������Ԗڂ���</param>
void CharaBase::SetonTilePositionX_(short tileNumberX)
{
	onTileNumberX_ = tileNumberX;
}

/// <summary>
/// ���Ԗڂ̃^�C���ɂ��邩���Z�b�g�i�x�jA*�֌W
/// </summary>
/// <param name="tileNumberY">�^�C�������Ԗڂ���</param>
void CharaBase::SetonTilePositionY_(short tileNumberY)
{
	onTileNumberY_ = tileNumberY;
}

/// <summary>
/// �m�b�N�o�b�N�����肷��
/// </summary>
/// <param name="otherChara">���肷��ق��̃L����</param>
void CharaBase::decideKnockBackWithChara(std::shared_ptr<CharaBase> otherChara)
{
	//�J����Ԃ̂Ƃ��ɔ��������
	if (state_== openState_())
	{
		//2�_�Ԃ̋������o��
		float dx		= otherChara->GetcollisionCenterPosition_().x - collisionCenterPosition_.x;
		float dz		= otherChara->GetcollisionCenterPosition_().z - collisionCenterPosition_.z;
		float distance	= CalculateDistance<float>(collisionCenterPosition_, otherChara->GetcollisionCenterPosition_());

		//���������a������������
		if (distance < collision_radius * 2 && otherChara->Getstate_() == openState_())
		{
			// �Փ˂̖@���x�N�g��
			VECTOR normalLine = VGet(0.0f, 0.0f, 0.0f);
			normalLine.x = dx / distance;
			normalLine.z = dz / distance;

			//�߂荞�ݗ�
			float overlap = collision_radius * 2 - distance;

			// �d�Ȃ�����̂��߂̈ʒu�␳
			VECTOR knockBackVector	= VScale(normalLine, overlap);
			knockBackVector			= VNorm(knockBackVector);
			collisionCenterPosition_.x -= knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent;
			collisionCenterPosition_.z -= knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent;

			// ���L�����ւ̔������x�K�p
			moveVector_.x = -(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent);
			moveVector_.z = -(knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);
			
			//����L�����̓����蔻��̍��W�������߂�
			otherChara->AdjustPositionAfterCollision(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent, knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);
			// ����L�����ւ̔������x�K�p
			otherChara->AddImpulse(knockBackVector.x / 2 * otherChara->Getmass_() * blow_away_percent, knockBackVector.z / 2 * otherChara->Getmass_() * blow_away_percent);

			//�q�b�g��
			PlaySoundMem(hitSound_, DX_PLAYTYPE_BACK, TRUE);

			//�t���O��true��
			changeHitNowFlag();
			otherChara->changeHitNowFlag();

			//�R���g���[���[��U��������
			StartJoypadVibration(controlerNumber_, vibration_power, vibration_time);
			StartJoypadVibration(otherChara->GetcontrolerNumber_(), vibration_power, vibration_time);
		}
		
		//�q�b�g���I���̂��J�E���g�ő҂�
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
/// �ړ��ʂɂӂ��Ƃ΂��ʂ������
/// </summary>
/// <param name="impulseX">�ӂ��Ƃ΂��ʂ�</param>
/// <param name="impulseZ">�ӂ��Ƃ΂��ʂ�</param>
void CharaBase::AddImpulse(float impulseX, float impulseZ)
{
	moveVector_.x = impulseX;
	moveVector_.z = impulseZ;
}

/// <summary>
/// �R���W�����̍��W�𒲐�
/// </summary>
/// <param name="amountX">�����ʂ�</param>
/// <param name="amountZ">�����ʂ�</param>
void CharaBase::AdjustPositionAfterCollision(float amountX, float amountZ)
{
	collisionCenterPosition_.x += amountX;
	collisionCenterPosition_.z += amountZ;
}

/// <summary>
/// �m�b�N�o�b�N����
/// </summary>
void CharaBase::knockBackNow()
{
	if(isKnockBack_)
	{
		//�J�E���g�����ɂȂ邩�^�b�N���ړ�����������m�b�N�o�b�N����߂�
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
/// �����蔻����Rd���f���ɉ����ĉ�]������
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
	//�����������Ă���Ƃ��ő��肪�J���Ă����Ԃ̂Ƃ�����
	if (!canSpawnWind_ && otherChara->Getstate_() == openState_() && state_ == fanState_())
	{
		float distance = CalculateDistance<float>(windPosition_, otherChara->GetcollisionCenterPosition_());

		//������2�̔��a�𑫂������l������������
		if (distance < collision_radius + collision_radius_wind)
		{
			//���ŉ����o��
			otherChara->hitWind(windMoveVector_);

			//�R���g���[���[��U��������
			StartJoypadVibration(otherChara->GetcontrolerNumber_(), vibration_power, vibration_time);
			
			//�G��hp�����炷
			otherChara->subHp();
			otherChara->subHp();

			//�������W���Z�b�g
			respawnPosition_ = decideRespawnPosition(stage);

			//�G��|�������̏���
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
	//�����t���O��true�������畜��
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
	//�g�����y�b�g�ɂȂ������ƂȂ�������
	if (!wasTrumpet_)
	{
		//������X�e�[�W�O�ɉ����o����hp���O�ɂ���
		if (!stage->GetcanExist_()[otherChara->GetonTileNumberY_()][otherChara->GetonTileNumberX_()] ||
			otherChara->Gethp_() <= 0)
		{
			canRespawn_ = true;
		}
	}
}

/// <summary>
/// hp������
/// </summary>
void CharaBase::subHp()
{
	--hp_;
}

/// <summary>
/// ���b�p�����ɂȂ�
/// </summary>
void CharaBase::changeTrumpet()
{
	//hp��0�ȉ��ɂȂ������b�p�ɂȂ�
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
/// �v���C���[���U������
/// </summary>
void CharaBase::vibration()
{
	rad_ += static_cast<float>((DX_PI / 180) * 100);

	position_.x = position_.x + sinf(rad_);
	position_.z = position_.z + sinf(rad_);
}

/// <summary>
/// �R���X�g���N�^�����t���[�����I��鎞��\���֐�
/// </summary>
void CharaBase::constructFrameEnd()
{
	onConstructFrame_ = false;
}

void CharaBase::decideMoveAngle(VECTOR movePosition)
{
	rotationAngleY_ = atan2(static_cast<double>(movePosition.x - position_.x), static_cast<double>(movePosition.z - position_.z)) - 90 * DX_PI /180;
}