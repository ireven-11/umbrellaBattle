#pragma once

constexpr float init_Y = 30.0f;
constexpr float init_z = -35.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void virtualUpdate(VECTOR upPosition);
	void reset();

	bool GetwasZoomUP_()const { return wasZoomUp_; }

private:
	VECTOR	position_;				//�J�����|�W�V����
	VECTOR	targetPosition_;		//�J�����̃^�[�Q�b�g�|�W�V����
	bool	wasZoomUp_;				//�Y�[���A�b�v�������ǂ���
	bool	wasZoomUPXYZ_[3];		//�Y�[���A�b�v�������ǂ���xyz
	int		skydomeHandle_;			//�X�J�C�h�[���n���h��
	float	acceleration_;			//�����x
	
	const VECTOR	zoom_out_position	= VGet(0.0f, 10.0f, 8.0f);	//�Y�[���A�E�g���W
	const float		error				= 0.3;						//�덷
	const float		scale				= 0.1;						//�X�J�C�h�[���̃X�P�[��
	const float		add_move_speed		= 0.0075;					//�J�����̉����x
};