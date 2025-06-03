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

	VECTOR	position_;			//座標
	int		openingUmbrella_;	//モデルハンドル(開いた状態)
	int		closingUmbrella_;	//モデルハンドル(閉じた状態)
	bool	isOpening_;			//傘開いてるかフラグ
	int		hp_;				//hp
	bool	isPrevButton_;		//前フレームにボタンを押したかフラグ
};