#include"DxLib.h"
#include"player.h"
#include<cmath>

//�R���g���[���[(D)�p�\���̕ϐ�
DINPUT_JOYSTATE input;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	//3d���f���ǂݍ���
	openingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraopen.mv1");
	closingUmbrella_ = MV1LoadModel("3dmodel/umbrella/umblleraclose.mv1");
	MV1SetScale(openingUmbrella_, VGet(scale, scale, scale));
	MV1SetScale(closingUmbrella_, VGet(scale, scale, scale));

	//���l������
	reset();

	//�R���g���[���[�̃f�b�h�]�[����ݒ�
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.5);
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
	//�e�X�g�p���f���ύX�{��]
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
	//�ł΂������Z�b�g
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
/// �`��
/// </summary>
void Player::draw()const
{
	//�f�o�b�O�p
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
/// �ϐ������Z�b�g
/// </summary>
void Player::reset()
{
	position_		= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_		= true;
}

/// <summary>
/// �ړ�
/// </summary>
void Player::move()
{
	//�R���g���[���[���g����悤�ɂ���
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//�L�[�{�[�h�p�i�f�o�b�O)
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
	//�R���g���[���[�p
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
/// �A�N�V����
/// </summary>
void Player::action()
{
	swing();
	tackle();
	wind();
}

/// <summary>
/// �A�N�V�����F�X�C���O
/// </summary>
void Player::swing()
{

}

/// <summary>
/// �A�N�V�����F�^�b�N��
/// </summary>
void Player::tackle()
{

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

//��]�����܂������ĂȂ��B�v�C��
void Player::rotation()
{
	GetJoypadAnalogInput(&input.X, &input.Y, DX_INPUT_PAD1);

	//�X�e�B�b�N�̓|��Ă��������p�x�����߂�
	float angleRad		= atan2(input.Y, input.X);
	float angleRotation = angleRad * (180.0f / DX_PI);

	MV1SetRotationXYZ(closingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, angleRotation - 90.0f, 0.0f));
	MV1SetRotationXYZ(openingUmbrella_, VGet(-40.0f * DX_PI_F / 180.0f, angleRotation - 90.0f, 0.0f));
}