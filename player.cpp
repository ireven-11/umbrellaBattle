#include"DxLib.h"
#include"player.h"
#include<cmath>

//�R���g���[���[(D)�p�\���̕ϐ�
DINPUT_JOYSTATE input;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(const int join_number)
{
	//3d���f���ǂݍ���
	openingUmbrella_	= MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_	= MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	fan_				= MV1LoadModel("3dmodel/fan/fanWithTile.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(fan_, VGet(scale / 10, scale / 10, scale / 10));

	//���l������
	reset();

	controlerNumber_ = join_number;

	//�R���g���[���[�̃f�b�h�]�[����ݒ�
	SetJoypadDeadZone(controlerNumber_, 0.1);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	MV1DeleteModel(openingUmbrella_);
	MV1DeleteModel(closingUmbrella_);
}

/// <summary>
/// �X�V
/// </summary>
void Player::update()
{
	//�R���g���[���[���g����悤�ɂ���
	GetJoypadDirectInputState(controlerNumber_, &input);

	//�e�X�g�p���f���ύX�{��]
	if (CheckHitKey(KEY_INPUT_1))
	{
		isOpening_ = true;
	}
	if (CheckHitKey(KEY_INPUT_2))
	{
		isOpening_ = false;
	}
	
	//�ł΂������Z�b�g
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
/// �`��
/// </summary>
void Player::draw()const
{
	//�f�o�b�O�p
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
/// �ϐ������Z�b�g
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
/// �ړ�
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
/// �A�N�V����
/// </summary>
void Player::action()
{
	//hp������Ƃ�
	if (hp_ > 0)
	{
		move();
		swing();
		tackle();
	}
	//hp���Ȃ��Ƃ�
	else
	{
		wind();
	}
}

/// <summary>
/// �A�N�V�����F�X�C���O
/// </summary>
void Player::swing()
{
	//���A�N�V�������ĂȂ�������
	if (!isSwing_&& input.Buttons[1] > 0 && !isTackle_)
	{
		isSwing_	= true;
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
void Player::tackle()
{
	//�{�^���������Ă͂Ȃ�����
	if (tackleCount_ > 0 && input.Buttons[0] == 0)
	{
		isMovingtackle_ = true;
		--tackleCount_;
		tackleMoving(rotaionMatrix_);
	}
	//B�{�^������������
	else if (input.Buttons[0] > 0 && !isMovingtackle_)
	{
		isTackle_ = true;
		if (max_tackle_count > tackleCount_)
		{
			++tackleCount_;
		}
		
		//�ǂ̕����Ƀ^�b�N�����邩��]�s��Ō��߂�
		rotaionMatrix_ = MGetRotY(rotationAngleY_ + agnle_shift_number);
	}

	stopTackle();

	//�f�o�b�O�p
	DrawFormatString(100, 300, GetColor(255, 255, 255), "�^�b�N��:%f", tackleCount_);
}

/// <summary>
/// �^�b�N���ړ���
/// </summary>
/// <param name="rotation">�ǂ̕����Ƀ^�b�N�����邩���߂��]�s��</param>
void Player::tackleMoving(MATRIX rotation)
{
	VECTOR moveVector = VTransform(VGet(tackleCount_ / adjust_tackle, 0.0f, tackleCount_ / adjust_tackle), rotation);
	position_ = VAdd(position_, moveVector);

	//�ړ����͗��������炭����悤��y�ɕ␳��������
	if (position_.y < 0.0f)
	{
		position_.y += adjust_position_y;
	}
}

/// <summary>
/// �^�b�N������߂�
/// </summary>
void Player::stopTackle()
{
	//�J�E���g���O�Ȃ邩�^�b�N������B�����������߂�
	if (tackleCount_ == 0 && isMovingtackle_ || isMovingtackle_ && input.Buttons[0] > 0)
	{
		isTackle_		= false;
		isMovingtackle_ = false;
		tackleCount_	= 0;
	}
}

/// <summary>
/// �A�N�V�����F��
/// </summary>
void Player::wind()
{

}

/// <summary>
/// ����
/// </summary>
void Player::fall()
{
	position_.y -= fall_speed;
}

/// <summary>
/// �R���g���[���[�̃X�e�B�b�N�̌X���ɉ�����3d���f���̉�]
/// </summary>
void Player::rotation()
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
	//DrawFormatString(200, 200, GetColor(255, 255, 255), "�p�x:%f", rotationAngle_);
}