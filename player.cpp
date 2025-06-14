#include"DxLib.h"
#include"player.h"

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
	position_	= VGet(player_init_positionX, player_init_positionY, player_init_positionZ);
	isOpening_	= true;
}

/// <summary>
/// �ړ�
/// </summary>
void Player::move()
{
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