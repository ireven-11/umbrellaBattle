#pragma once

const float init_Y = 20.0f;
const float init_z = -30.0f;

class Camera
{
public:
	Camera();
	~Camera();

	void update();

private:
	VECTOR position_;		//�J�����|�W�V����
	VECTOR targetPosition_;	//�J�����̃^�[�Q�b�g�|�W�V����
};