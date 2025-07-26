#pragma once
#include<memory>
#include"IState.h"
#include"openState.h"
#include"closeState.h"
#include"fanState.h"
#include"trumpetState.h"

constexpr float	player_init_positionX	= 0.0f;
constexpr float	player_init_positionY	= 0.0f;
constexpr float	player_init_positionZ	= 0.0f;
constexpr float collision_radius		= 2.0;

class Routine;
class Stage;

class CharaBase
{
public:
	CharaBase(const int join_number);
	~CharaBase();

	virtual void update(Routine* routine, std::shared_ptr<Stage> stage);
	void reset();
	void fall();
	virtual void changeOpenToClose();
	virtual void changeCloseToOpen();
	virtual void transformFan();
	virtual void move();
	virtual void swing();
	virtual void tackle();
	void wind();
	virtual void moveFan();
	void SetonTilePosition(VECTOR tilePosition);
	void SetonTilePositionX_(short tileNumberX);
	void SetonTilePositionY_(short tileNumberY);
	void pushBackWithChara(std::shared_ptr<CharaBase> otherChara);
	void positionAdjustmentAfterHit(float nx, float nz, float overlap, float impulseX, float impulseZ);
	void collisionRotation();
	void blownAway(float nx, float nz, float overlap, float impulseX, float impulseZ);
	void AdjustPositionAfterCollision(float nx, float ny, float nz, float amount);
	void AddImpulse(float impulseX, float impulseY, float impulseZ);
	DINPUT_JOYSTATE input;		//コントローラー(D)用構造体変数
	VECTOR								Getposition_()const { return  position_; }
	std::shared_ptr<StateMachine::IState>	Getstate_()const { return state_; }
	int									GetcontrolerNumber_()const { return controlerNumber_; }
	float								GettackleCount_()const { return tackleCount_; }
	float								Getmax_tackle_count()const { return max_tackle_count; }
	VECTOR								GetonTilePosition_()const { return onTilePosition_; }
	short								GetonTileNumberX_()const { return onTileNumberX_; }
	short								GetonTileNumberY_()const { return onTileNumberY_; }
	VECTOR								GetcollisionCenterPosition_()const { return collisionCenterPosition_; }
	short								Getmass_()const { return mass_; }
	VECTOR								GetmoveVector_()const { return moveVector_; }
	bool								GetisChargeTackle_()const { return isChargeTackle_; }

private:
	const float		fall_speed = 0.005f;
	const float		scale = 0.15f;
	const float		move_speed = 0.2f;
	const float		max_tackle_count = 50.0f;
	const double	agnle_shift_number = 0.75;
	const int		adjust_tackle = 50;
	const float		rotation_angle_x = -45.0f;
	const double	adjust_rotation_angle_y = agnle_shift_number * -2;
	const float		adjust_position_y = 0.2f;
	const int		max_hp = 100;
	const double	swing_speed = 0.40;
	const double	max_swing_angle = 3.0;
	const double	fan_move_speed = 2.5;
	const float		transform_position_y = -10.0;
	const VECTOR	player1_init_position = VGet(-10.0f, 0.0f, 20.0f);
	const VECTOR	player2_init_position = VGet(-10.0f, 0.0f, 0.0f);
	const VECTOR	player3_init_position = VGet(0.0f, 0.0f, 20.0f);
	const VECTOR	player4_init_position = VGet(0.0f, 0.0f, 0.0f);
	const VECTOR	collision_adjust_position = VGet(1.5f, 0.0f, 1.0f);
	const short		init_mass	= 1;
	const short		tackle_mass = 5;
	const short		blow_away_percent = 10;
	const short		hit_sound_volume = 255;

protected:
	void draw()const;
	void tackleMoving();
	virtual void stopTackle();
	virtual void rotation();

	VECTOR	position_;			//座標
	int		openingUmbrella_;	//モデルハンドル(開いた状態)
	int		closingUmbrella_;	//モデルハンドル(閉じた状態)
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
	double	fanMoveAngle_;		//扇風機の移動角度
	VECTOR	onTilePosition_;	//乗っているタイルの座標
	short	onTileNumberX_;		//乗っているタイルの配列の要素数x
	short	onTileNumberY_;		//乗っているタイルの配列の要素数y
	VECTOR  moveVector_;		//移動ベクトル
	VECTOR	collisionCenterPosition_;//コリジョンの中心座標
	short	mass_;				//質量
	int		hitSound_;			//ヒット効果音
	bool	isChargeTackle_;	//タックルチャージしてるか
	int		chargeSound_;		//チャージ音
	bool	canLoopSound_;

	//状態
	std::shared_ptr<StateMachine::IState>	state_;
	static std::shared_ptr<CharaState::OpenState> openState_()
	{
		static std::shared_ptr<CharaState::OpenState> state = std::make_shared<CharaState::OpenState>();
		return state;
	}
	static std::shared_ptr<CharaState::CloseState> closeState_()
	{
		static std::shared_ptr<CharaState::CloseState> state = std::make_shared<CharaState::CloseState>();
		return state;
	}
	static std::shared_ptr<CharaState::FanState> fanState_()
	{
		static std::shared_ptr<CharaState::FanState> state = std::make_shared<CharaState::FanState>();
		return state;
	}
};