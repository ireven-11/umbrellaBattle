#pragma once

constexpr float		player_init_positionX	= 0.0f;
constexpr float		player_init_positionY	= 0.0f;
constexpr float		player_init_positionZ	= 0.0f;

class Player
{
public:
	Player(const int join_number);
	~Player();

	void update();
	void reset();
	void fall();

	VECTOR Getposition_()const { return  position_; }

private:
	void draw()const;
	void move();
	void action();
	void swing();
	void tackle();
	void tackleMoving(MATRIX rotation);
	void stopTackle();
	void wind();
	void rotation();

	VECTOR	position_;			//���W
	int		openingUmbrella_;	//���f���n���h��(�J�������)
	int		closingUmbrella_;	//���f���n���h��(�������)
	bool	isOpening_;			//�P�J���Ă邩�t���O
	int		hp_;				//hp
	bool	isPrevButton_;		//�O�t���[���Ƀ{�^�������������t���O
	bool	isTackle_;			//�^�b�N�����Ă邩�t���O
	float	tackleCount_;		//�^�b�N���J�E���g
	VECTOR	tackleVector_;		//�^�b�N���̃x�N�g��
	double	rotationAngleY_;	//��]�p�x
	MATRIX	rotaionMatrix_;		//��]�s���ۑ�����ϐ�
	bool	isMovingtackle_;	//�^�b�N���ړ������ǂ���
	int		controlerNumber_;	//�ǂ̃R���g���[������\������

	const float		fall_speed				= 0.005f;
	const float		scale					= 0.15f;
	const float		move_speed				= 0.2f;
	const float		max_tackle_count		= 50.0f;
	const double	agnle_shift_number		= 0.75;
	const int		adjust_tackle			= 50;
	const float		rotation_angle_x		= -45.0f;
	const double	adjust_rotation_angle_y = -1.5;
	const float		adjust_position_y		= 0.2f;
};