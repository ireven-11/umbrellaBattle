#pragma once

constexpr float init_Y = 30.0f;
constexpr float init_z = -30.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void virtualUpdate(VECTOR upPosition);

	bool GetwasZoomUP_()const { return wasZoomUp_; }

private:
	VECTOR	position_;				//�J�����|�W�V����
	VECTOR	targetPosition_;		//�J�����̃^�[�Q�b�g�|�W�V����
	bool	wasZoomUp_;				//�Y�[���A�b�v�������ǂ���
	bool	wasZoomUPXYZ_[3];		//�Y�[���A�b�v�������ǂ���xyz
	
	const float		move_speed			= 0.3f;						//�ړ��X�s�[�h
	const VECTOR	zoom_out_position	= VGet(0.0f, 10.0f, 8.0f);	//�Y�[���A�E�g���W
	const float		error				= 0.3;						//�덷
};