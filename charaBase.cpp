#include"Dxlib.h"
//#include"YuiLib/YuiLib.h"
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

	//���l������
	reset();

	//�R���g���[���[�̃f�b�h�]�[����ݒ�
	SetJoypadDeadZone(controlerNumber_, 0.1);

	//�X�e�[�g�C���X�^���X��
	state_ = openState_();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharaBase::~CharaBase()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
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

	//�ł΂������Z�b�g
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
	else if (state_ == std::dynamic_pointer_cast<CharaState::CloseState>(state_))
	{
		MV1DrawModel(closingUmbrella_);
	}
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
	onTilePosition_ = VGet(0.0f, 0.0f, 0.0f);
	moveVector_		= VGet(0.0f, 0.0f, 0.0f);
	collisionCenterPosition_ = VGet(0.0f, 0.0f, 0.0f);
}

/// <summary>
/// �ړ�
/// </summary>
void CharaBase::move()
{
	auto isNoneAction = !isTackle_ && !isSwing_;

	//�������^�[��
	if (input.X == 0 && input.Y == 0)
	{
		return;
	}

	moveVector_ = VGet(0.0f, 0.0f, 0.0f);
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
	/*if (input.Y != 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}
	if (input.X != 0 && isNoneAction)
	{
		moveVector = VAdd(moveVector, VGet(move_speed, 0.0f, move_speed));
	}*/

	//�X�e�B�b�N�̌X������ǂ̂��炢���f������]�����邩����
	rotation();

	//�X�e�B�b�N���X���Ă�����Ɉړ�
	rotaionMatrix_	= MGetRotY(rotationAngleY_ + agnle_shift_number);
	moveVector_		= VTransform(moveVector_, rotaionMatrix_);
	position_		= VAdd(position_, moveVector_);

	//DrawFormatString(100,800,)
	//DrawFormatString(100, 700, GetColor(255, 255, 255), "���[�u�x�N�^�[ x:%f y:%f z:%f", moveVector.x, moveVector.y, moveVector.z);
}

/// <summary>
/// �A�N�V�����F�X�C���O
/// </summary>
void CharaBase::swing()
{
	//���A�N�V�������ĂȂ�������
	if (!isSwing_ && input.Buttons[1] > 0 && !isTackle_)
	{
		isSwing_ = true;
		angleSwing_ = rotationAngleY_;
	}
	//�X�C���O���Ă�Ƃ���y����]����
	else if (isSwing_)
	{
		angleSwing_ += swing_speed;
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, angleSwing_ + adjust_rotation_angle_y, 0.0f));

		//�ő�܂ŃX�C���O�����猳�̊p�x�ɖ߂�
		if (angleSwing_ >= max_swing_angle + rotationAngleY_)
		{
			MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
			isSwing_ = false;
		}
	}
}

/// <summary>
/// �A�N�V�����F�^�b�N��
/// </summary>
void CharaBase::tackle()
{
	//�{�^���������Ă͂Ȃ�����
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingtackle_ = true;
		--tackleCount_;
		tackleMoving();
	}
	//B�{�^������������
	else if (input.Buttons[0] > 0 && !isMovingtackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			++tackleCount_;
		}

		//�ǂ̕����Ƀ^�b�N�����邩Y���̉�]�s��Ō��߂�
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);
	}

	//�^�b�N������߂�
	stopTackle();

	//�f�o�b�O�p
	DrawFormatString(100, 300, GetColor(255, 255, 255), "�^�b�N��:%f", tackleCount_);
}

/// <summary>
/// �^�b�N���ړ���
/// </summary>
/// <param name="rotation">�ǂ̕����Ƀ^�b�N�����邩���߂��]�s��</param>
void CharaBase::tackleMoving()
{
	moveVector_ = VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotaionMatrix_);
	position_ = VAdd(position_, moveVector_);

	//�ړ����͗��������炭����悤��y�ɕ␳��������
	if (position_.y < 0.0f)
	{
		position_.y += adjust_position_y;
	}
}

/// <summary>
/// �^�b�N������߂�
/// </summary>
void CharaBase::stopTackle()
{
	//�J�E���g���O�Ȃ邩�^�b�N������B�����������߂�
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0)
	{
		isTackle_ = false;
		isMovingtackle_ = false;
		tackleCount_ = 0;
	}
}

/// <summary>
/// �A�N�V�����F��
/// </summary>
void CharaBase::wind()
{
	//ZR��ZL�ňړ�
	moveFan();

	//�f�o�b�O�p
	DrawFormatString(100, 500, GetColor(255, 255, 255), "%f", fanMoveAngle_);
}

/// <summary>
/// ��@�ړ�
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
	//�X�e�[�W�̒��S�������悤�Ƀ��f������]
	MV1SetRotationXYZ(fan_, VGet(0.0f, tempRotation + DX_PI, 0.0f));
}

/// <summary>
/// ����
/// </summary>
void CharaBase::fall()
{
	position_.y -= fall_speed;
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

		MV1SetRotationXYZ(closingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
		MV1SetRotationXYZ(openingUmbrella_, VGet(rotation_angle_x * DX_PI_F / 180.0f, rotationAngleY_ + adjust_rotation_angle_y, 0.0f));
	}

	//�f�o�b�O�p
	DrawFormatString(200, 200, GetColor(255, 255, 255), "�p�x:%f", rotationAngleY_);
}

/// <summary>
/// ��@�ɕϐg
/// </summary>
void CharaBase::transformFan()
{
	//���̍����܂ŗ�������
	if (position_.y < transform_position_y)
	{
		//state_ = make_shared<CharaState::FanState>();
		state_ = fanState_();
		position_.y = player_init_positionY;
		//�������u�Ԃɐ�@�̈ړ������Đ�@�̈ʒu��ݒ肷��
		input.Buttons[6] = 1;
		moveFan();
	}
}

/// <summary>
/// �J������Ԃ��������Ԃ�
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
/// ������Ԃ���J������Ԃ�
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
/// �^�C���̏�ɂ���Ƃ��̃^�C�����W��ۑ�����
/// </summary>
/// <param name="tilePosition">�^�C�����W</param>
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
		float dx = otherChara->Getposition_().x - position_.x;
		float dy = otherChara->Getposition_().y - position_.y;
		float dz = otherChara->Getposition_().z - position_.z;
		float distance = CalculateDistance<float>(position_, otherChara->Getposition_());

		if (distance < collision_radius * 2)
		{
			// �Փ˂̖@���x�N�g��
			float nx = dx / distance;
			float ny = dy / distance;
			float nz = dz / distance;

			// 2���Ԃ̑��Α��x
			float vx_rel = move_speed - move_speed;
			float vy_rel = 0.0f - 0.0f;
			float vz_rel = move_speed - move_speed;

			// �@�������̑��Α��x
			float velocityAlongNormal = vx_rel * nx + vy_rel * ny + vz_rel * nz;

			// �����W���i���S�e���Փ˂Ɖ���j
			if (velocityAlongNormal > 0) return;  // ���łɗ���悤�Ƃ��Ă���ꍇ�͉������Ȃ�

			// �Փˌ�̑��x�X�V�i�e���Փˁj
			float restitution = 1.0f; // ���S�e���Փ�

			// ���ʂ̔�Ɋ�Â��đ��x�̕ω��ʂ��v�Z
			float impulse = 2 * velocityAlongNormal;
			float impulseX = impulse * nx;
			float impulseZ = impulse * nz;

			// ���x�̍X�V
			moveVector_.x += impulseX;
			moveVector_.z += impulseZ;

			// �Փˌ�̈ʒu�����i�d�Ȃ�������j
			float overlap = collision_radius * 2 - distance;
			otherChara->positionAdjustmentAfterHit(distance, nx, nz, overlap, impulseX, impulseZ);
			position_.x -= nx * overlap / 2;
			position_.z -= nz * overlap / 2;
		}
	}
}

void CharaBase::positionAdjustmentAfterHit(float distance, float nx, float nz, float overlap, float impulseX, float impulseZ)
{
	moveVector_.x -= impulseX;
	moveVector_.z -= impulseZ;
	position_.x += nx * overlap / 2;
	position_.z += nz * overlap / 2;
}