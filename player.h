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

	VECTOR	position_;			//座標
	int		openingUmbrella_;	//モデルハンドル(開いた状態)
	int		closingUmbrella_;	//モデルハンドル(閉じた状態)
	bool	isOpening_;			//傘開いてるかフラグ
	int		hp_;				//hp
	bool	isPrevButton_;		//前フレームにボタンを押したかフラグ
	bool	isTackle_;			//タックルしてるかフラグ
	int		tackleCount_;		//タックルカウント

	const float fall_speed	= 0.01f;
	const float scale		= 0.15f;
	const float move_speed	= 0.2f;
};