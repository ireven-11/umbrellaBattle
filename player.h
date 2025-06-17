#pragma once

const float player_init_positionX = 0.0f;
const float player_init_positionY = 0.0f;
const float player_init_positionZ = 0.0f;

class Player
{
public:
	Player();
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
	void wind();
	void rotation();
	void tackleMoving();

	VECTOR	position_;			//���W
	int		openingUmbrella_;	//���f���n���h��(�J�������)
	int		closingUmbrella_;	//���f���n���h��(�������)
	bool	isOpening_;			//�P�J���Ă邩�t���O
	int		hp_;				//hp
	bool	isPrevButton_;		//�O�t���[���Ƀ{�^�������������t���O
	bool	isTackle_;			//�^�b�N�����Ă邩�t���O
	int		tackleCount_;		//�^�b�N���J�E���g

	const float fall_speed	= 0.01f;
	const float scale		= 0.15f;
	const float move_speed	= 0.2f;
};