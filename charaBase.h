#pragma once

constexpr float	player_init_positionX = 0.0f;
constexpr float	player_init_positionY = 0.0f;
constexpr float	player_init_positionZ = 0.0f;

class CharaBase
{
public:
	CharaBase(const int join_number);
	~CharaBase();

	void update();
	void reset();
	void fall();
	void transformFan();

	VECTOR	Getposition_()const { return  position_; }
	bool	GetisFan_()const { return isFan_; }

private:
	void draw()const;
	void move();
	void action();
	void swing();
	void tackle();
	void tackleMoving(MATRIX rotation);
	void stopTackle();
	void wind();
	void moveFan();
	void rotation();

	VECTOR	position_;			//座標
	int		openingUmbrella_;	//モデルハンドル(開いた状態)
	int		closingUmbrella_;	//モデルハンドル(閉じた状態)
	bool	isOpening_;			//傘開いてるかフラグ
	int		hp_;				//hp
	bool	isPrevButton_;		//前フレームにボタンを押したかフラグ
	bool	isTackle_;			//タックルしてるかフラグ
	float	tackleCount_;		//タックルカウント
	VECTOR	tackleVector_;		//タックルのベクトル
	double	rotationAngleY_;	//回転角度
	MATRIX	rotaionMatrix_;		//回転行列を保存する変数
	bool	isMovingtackle_;	//タックル移動中かどうか
	int		controlerNumber_;	//どのコントローラかを表す数字
	bool	isSwing_;			//スイング中かどうか
	double	angleSwing_;		//スイングの角度
	int		fan_;				//扇風機
	bool	isFan_;				//扇風機かどうかフラグ
	double	fanMoveAngle_;		//扇風機の移動角度

	const float		fall_speed = 0.005f;
	const float		scale = 0.15f;
	const float		move_speed = 0.2f;
	const float		max_tackle_count = 50.0f;
	const double	agnle_shift_number = 0.75;
	const int		adjust_tackle = 50;
	const float		rotation_angle_x = -45.0f;
	const double	adjust_rotation_angle_y = -1.5;
	const float		adjust_position_y = 0.2f;
	const int		max_hp = 100;
	const double	swing_speed = 0.40;
	const double	max_swing_angle = 3.0;
	const double	fan_move_speed = 2.5;
	const float		transform_position_y = -10.0;
};