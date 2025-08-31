#include"DxLib.h"
#include"camera.h"
#include"EffekseerForDXLib.h"
#include"calculateDistance.h"
#include <cmath>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	//�X�e�[�W�w�i���Z�b�g
	skydomeHandle_ = MV1LoadModel("3dmodel/Skydome/�X�J�C�h�[��_�J��PP3/Skydome_PP3/Dome_PP301.pmx");
	MV1SetScale(skydomeHandle_, VGet(scale, scale, scale));
	MV1SetUseZBuffer(skydomeHandle_, FALSE);

	position_				= VGet(0.0f, init_Y, init_z);
	targetPosition_			= VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_				= false;
	acceleration_			= 0.0f;
	for (auto i = 0; i < 3; i++)
	{
		wasZoomUPXYZ_[i] = false;
	}

	//�[�b�g�o�b�t�@��L���ɂ���
	SetUseZBufferFlag(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	SetUseSetDrawScreenSettingReset(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
	MV1DeleteModel(skydomeHandle_);
}

void Camera::reset()
{
	position_		= VGet(0.0f, init_Y, init_z);
	targetPosition_ = VGet(0.0f, 0.0f, 0.0f);
	wasZoomUp_		= false;
	acceleration_	= 0.0f;
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

	//�X�J�C�{�b�N�X�`��
	MV1SetPosition(skydomeHandle_, VGet(position_.x, position_.y - 30.0f, position_.z));
	MV1DrawModel(skydomeHandle_);
	
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

void Camera::virtualUpdate(VECTOR upPosition)
{
	//���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.00f, 500.00f);

	//�����_���ړ�
	if (targetPosition_.x != upPosition.x ||
		targetPosition_.y != upPosition.y ||
		targetPosition_.z != upPosition.z)
	{
		targetPosition_.x = std::lerp(targetPosition_.x, upPosition.x, acceleration_);
		targetPosition_.y = std::lerp(targetPosition_.y, upPosition.y, acceleration_);
		targetPosition_.z = std::lerp(targetPosition_.z, upPosition.z, acceleration_);
	}

	//�J�������W���ړ�
	if (position_.x != upPosition.x ||
		position_.y != upPosition.y ||
		position_.z != upPosition.z)
	{
		//�Y�[�����I����ĂȂ���Ή����x�𑬂�����
		if (!wasZoomUp_)
		{
			acceleration_ += add_move_speed;

			position_.x = std::lerp(position_.x, upPosition.x, acceleration_);
			position_.y = std::lerp(position_.y, upPosition.y + zoom_out_position.y, acceleration_);
			position_.z = std::lerp(position_.z, upPosition.z - zoom_out_position.z, acceleration_);
		}

		//�Y�[���A�b�v�I���
		if (CalculateDistance<float>(position_,upPosition) < distance_error)
		{
			wasZoomUp_ = true;
		}
	}

	//�X�J�C�{�b�N�X�`��
	MV1SetPosition(skydomeHandle_, VGet(position_.x, position_.y, position_.z));
	MV1DrawModel(skydomeHandle_);

	//�J�����̒����_��ݒ�
	SetCameraPositionAndTarget_UpVecY(position_, targetPosition_);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}