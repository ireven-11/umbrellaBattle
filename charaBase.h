#pragma once
#include<memory>
#include"IState.h"
#include"openState.h"
#include"closeState.h"
#include"fanState.h"
#include"trumpetState.h"
using namespace std;

constexpr float	player_init_positionX = 0.0f;
constexpr float	player_init_positionY = 0.0f;
constexpr float	player_init_positionZ = 0.0f;

class CharaBase
{
public:
	CharaBase(const int join_number);
	~CharaBase();

	virtual void update();
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

	VECTOR								Getposition_()const { return  position_; }
	shared_ptr<StateMachine::IState>	Getstate_()const { return state_; }
	int									GetcontrolerNumber_()const { return controlerNumber_; }

private:
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
	const VECTOR	player1_init_position = VGet(-10.0f, 0.0f, 20.0f);
	const VECTOR	player2_init_position = VGet(-10.0f, 0.0f, 0.0f);
	const VECTOR	player3_init_position = VGet(0.0f, 0.0f, 20.0f);
	const VECTOR	player4_init_position = VGet(0.0f, 0.0f, 0.0f);

protected:
	void draw()const;
	void tackleMoving();
	virtual void stopTackle();
	virtual void rotation();

	DINPUT_JOYSTATE input;		//�R���g���[���[(D)�p�\���̕ϐ�
	VECTOR	position_;			//���W
	int		openingUmbrella_;	//���f���n���h��(�J�������)
	int		closingUmbrella_;	//���f���n���h��(�������)
	int		hp_;				//hp
	bool	isPrevButton_;		//�O�t���[���Ƀ{�^�������������t���O
	bool	isTackle_;			//�^�b�N�����Ă邩�t���O
	float	tackleCount_;		//�^�b�N���J�E���g
	VECTOR	tackleVector_;		//�^�b�N���̃x�N�g��
	double	rotationAngleY_;	//��]�p�x
	MATRIX	rotaionMatrix_;		//��]�s���ۑ�����ϐ�
	bool	isMovingtackle_;	//�^�b�N���ړ������ǂ���
	int		controlerNumber_;	//�ǂ̃R���g���[������\������
	bool	isSwing_;			//�X�C���O�����ǂ���
	double	angleSwing_;		//�X�C���O�̊p�x
	int		fan_;				//��@
	double	fanMoveAngle_;		//��@�̈ړ��p�x

	//���
	shared_ptr<StateMachine::IState>	state_;
	static shared_ptr<CharaState::OpenState> openState_()
	{
		static shared_ptr<CharaState::OpenState> state = make_shared<CharaState::OpenState>();
		return state;
	}
	static shared_ptr<CharaState::CloseState> closeState_()
	{
		static shared_ptr<CharaState::CloseState> state = make_shared<CharaState::CloseState>();
		return state;
	}
	static shared_ptr<CharaState::FanState> fanState_()
	{
		static shared_ptr<CharaState::FanState> state = make_shared<CharaState::FanState>();
		return state;
	}
};