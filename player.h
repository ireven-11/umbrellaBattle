#pragma once

class Player
{
public:
	Player();
	~Player();

	void update();
	void reset();

private:
	void draw()const;
	void move();
	void action();
	void swing();
	void tackle();
	void wind();

	VECTOR	position_;			//���W
	int		openingUmbrella_;	//���f���n���h��(�J�������)
	int		closingUmbrella_;	//���f���n���h��(�������)
	bool	isOpening_;			//�P�J���Ă邩�t���O
	int		hp_;				//hp
	bool	isPrevButton_;		//�O�t���[���Ƀ{�^�������������t���O
};