#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	position_				= VGet(0.0f, init_Y, init_z);
	targetPosition_			= VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_				= false;
	for (auto i = 0; i < 3; i++)
	{
		wasZoomUPXYZ_[i] = false;
	}

	//�[�b�g�o�b�t�@��L���ɂ���
	SetUseZBufferFlag(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

void Camera::reset()
{
	position_ = VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_ = false;
	for (auto i = 0; i < 3; i++)
	{
		wasZoomUPXYZ_[i] = false;
	}
}

/// <summary>
/// �X�V
/// </summary>
void Camera::update()
{
	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 500.00f);

	//�J�����̒����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

void Camera::virtualUpdate(VECTOR upPosition)
{
	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 500.00f);

	//�J�����̒����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	//�����_���ړ�
	if (targetPosition_.x - upPosition.x > error || targetPosition_.x - upPosition.x < -error)//�덷��ݒ�
	{
		if (targetPosition_.x < upPosition.x)
		{
			targetPosition_.x += move_speed;
		}
		else if (targetPosition_.x > upPosition.x)
		{
			targetPosition_.x -= move_speed;
		}
	}
	if (targetPosition_.z - upPosition.z > error || targetPosition_.z - upPosition.z < -error)//�덷��ݒ�
	{
		if (targetPosition_.z < upPosition.z)
		{
			targetPosition_.z += move_speed;
		}
		else if (targetPosition_.z > upPosition.z)
		{
			targetPosition_.z -= move_speed;
		}
	}

	//�J�������W���ړ�
	if (position_.x - upPosition.x > error ||
		position_.x - upPosition.x < -error)//�덷��ݒ�
	{
		if (position_.x < upPosition.x)
		{
			position_.x += move_speed;
		}
		else if (position_.x > upPosition.x)
		{
			position_.x -= move_speed;
		}
	}
	else
	{
		wasZoomUPXYZ_[0] = true;
	}
	if (position_.y > upPosition.y + zoom_out_position.y)
	{
		position_.y -= move_speed;
	}
	else
	{
		wasZoomUPXYZ_[1] = true;
	}
	if (position_.z - upPosition.z + zoom_out_position.z > error ||
		position_.z - upPosition.z + zoom_out_position.z < -error)//�덷��ݒ�
	{
		if (position_.z < upPosition.z + zoom_out_position.z)
		{
			position_.z += move_speed;
		}
		else if (position_.z > upPosition.z + zoom_out_position.z)
		{
			position_.z -= move_speed;
		}
	}
	else
	{
		wasZoomUPXYZ_[2] = true;
	}

	//�Y�[���I����\��
	if (wasZoomUPXYZ_[0] && wasZoomUPXYZ_[1] && wasZoomUPXYZ_[2])
	{
		wasZoomUp_ = true;
	}

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}