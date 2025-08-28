#pragma once
#include<memory>
#include"IState.h"
#include"openState.h"
#include"fanState.h"
#include"trumpetState.h"

constexpr float	player_init_positionX	= 0.0f;
constexpr float	player_init_positionY	= 0.0f;
constexpr float	player_init_positionZ	= 0.0f;
constexpr float collision_radius		= 2.0f;
constexpr float collision_radius_stage	= 0.2f;
constexpr float	collision_radius_wind	= 4.0f;
constexpr int	max_hp					= 200;
constexpr int	vibration_power			= 200;
constexpr int	vibration_time			= 200;
constexpr short	max_wind_count			= 120;

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
	virtual void transformFan();
	virtual void move();
	virtual void tackle();
	virtual void moveFan();
	void SetonTilePositionX_(short tileNumberX);
	void SetonTilePositionY_(short tileNumberY);
	void decideKnockBackWithChara(std::shared_ptr<CharaBase> otherChara);
	void collisionRotation();
	void AdjustPositionAfterCollision(float amountX, float amountZ);
	void AddImpulse(float impulseX, float impulseZ);
	void knockBackNow();
	virtual void draw()const;
	void changeHitNowFlag();
	void collisionWindWithChara(std::shared_ptr<CharaBase> otherChara, std::shared_ptr<Stage> stage);
	void respawn();
	void changeTrumpet();
	void changeFan();
	void vibration();
	void stopSound();
	void cannotChangeFan();
	void constructFrameEnd();
	void setPosition();
	virtual void wind();
	void decideMoveAngle(VECTOR movePosition);

	DINPUT_JOYSTATE input;		//�R���g���[���[(D)�p�\���̕ϐ�

	VECTOR								Getposition_()const { return  position_; }
	std::shared_ptr<StateMachine::IState>	Getstate_()const { return state_; }
	short								GetcontrolerNumber_()const { return controlerNumber_; }
	float								GettackleCount_()const { return tackleCount_; }
	float								Getmax_tackle_count()const { return max_tackle_count; }
	short								GetonTileNumberX_()const { return onTileNumberX_; }
	short								GetonTileNumberY_()const { return onTileNumberY_; }
	VECTOR								GetcollisionCenterPosition_()const { return collisionCenterPosition_; }
	short								Getmass_()const { return mass_; }
	VECTOR								GetmoveVector_()const { return moveVector_; }
	bool								GetisChargeTackle_()const { return isChargeTackle_; }
	bool								GetisHit_()const { return isHit_; }
	bool								GetisFalling_()const { return isFalling_; }
	bool								GetisMovingTackle_()const { return isMovingTackle_; }
	VECTOR								GetwindPosition_()const { return windPosition_; }
	double								GetwindAngle_()const { return windAngle_; }
	bool								GetcanSpawnWind_()const { return canSpawnWind_; }
	int									Gethp_()const { return hp_; }
	bool								GetcanRespawn_()const { return canRespawn_; }
	VECTOR								GetrespawnPosition_()const { return respawnPosition_; }
	bool								GetcanChangeFan_()const { return canChangeFan_; }
	bool								GetonConstructFrame_()const { return onConstructFrame_; }
	int									GetchargeSound_()const { return chargeSound_; }
	short								GetwindCount_()const noexcept { return windCount_; }
	double								GetrotationAngleY_()const noexcept { return rotationAngleY_; }
	VECTOR								GettackleEffectPos_()const { return tackleEffectPos_; }
	
private:
	const float		fall_speed				= 0.25f;
	const float		scale					= 0.15f;
	const float		max_tackle_count		= 50.0f;
	const int		adjust_tackle			= 40;
	const float		adjust_position_y		= 0.2f;
	const double	swing_speed				= 0.40;
	const double	max_swing_angle			= 3.0;
	const double	fan_move_speed			= 3.5;
	const float		transform_position_y	= -10.0f;
	const VECTOR	player1_init_position	= VGet(-10.0f, 0.0f, 20.0f);
	const VECTOR	player2_init_position	= VGet(-10.0f, 0.0f, 0.0f);
	const VECTOR	player3_init_position	= VGet(10.0f, 0.0f, 20.0f);
	const VECTOR	player4_init_position	= VGet(10.0f, 0.0f, 0.0f);
	const VECTOR	collision_adjust_position = VGet(1.5f, 0.0f, 1.0f);
	const short		init_mass				= 1;
	const short		tackle_mass				= 3;
	const float		blow_away_percent		= 1.4f;
	const short		hit_sound_volume		= 185;
	const short		knock_back_max_count	= 4;
	const short		charge_sound_volume		= 215;
	const short		wind_sound_volume		= 200;
	const short		respawn_sound_volume	= 255;
	const short		inverse_sound_volume	= 255;
	const short		change_fan_sound_volume = 200;
	
protected:
	void tackleMoving();
	virtual void stopTackle();
	virtual void rotation();
	void hitWind(VECTOR windVector);
	VECTOR decideRespawnPosition(std::shared_ptr<Stage> stage);
	void onBeatedChara(std::shared_ptr<CharaBase> otherChara, std::shared_ptr<Stage> stage);
	void subHp();
	
	VECTOR	position_;			//���W
	int		openingUmbrella_;	//���f���n���h��(�J�������)
	int		closingUmbrella_;	//���f���n���h��(�������)
	int		inverseUmbrella_;	//���f���n���h��(���b�p���)
	int		hp_;				//hp
	bool	isPrevButton_;		//�O�t���[���Ƀ{�^�������������t���O
	bool	isTackle_;			//�^�b�N�����Ă邩�t���O
	float	tackleCount_;		//�^�b�N���J�E���g
	VECTOR	tackleVector_;		//�^�b�N���̃x�N�g��
	double	rotationAngleY_;	//��]�p�x
	MATRIX	rotaionMatrix_;		//��]�s���ۑ�����ϐ�
	bool	isMovingtackle_;	//�^�b�N���ړ������ǂ���
	short	controlerNumber_;	//�ǂ̃R���g���[������\������
	bool	isSwing_;			//�X�C���O�����ǂ���
	double	angleSwing_;		//�X�C���O�̊p�x
	int		fan_;				//��@
	double	fanMoveAngle_;		//��@�̈ړ��p�x
	short	onTileNumberX_;		//����Ă���^�C���̔z��̗v�f��x
	short	onTileNumberY_;		//����Ă���^�C���̔z��̗v�f��y
	VECTOR  moveVector_;		//�ړ��x�N�g��
	VECTOR	collisionCenterPosition_;//�R���W�����̒��S���W
	short	mass_;				//����
	int		hitSound_;			//�q�b�g���ʉ�
	bool	isChargeTackle_;	//�^�b�N���`���[�W���Ă邩
	int		chargeSound_;		//�`���[�W��
	bool	canLoopSound_;		//�������[�v�ł��邩
	bool	isHit_;				//���������ǂ���
	bool	isKnockBack_;		//�m�b�N�o�b�N����
	bool	isFalling_;			//��������
	short	knockBackCount_;	//�m�b�N�o�b�N�J�E���g
	bool	isMovingTackle_;	//�^�b�N���ړ���
	VECTOR	windPosition_;		//���̍��W
	bool	canSpawnWind_;		//���𔭐�������邩
	VECTOR  windMoveVector_;	//���̈ړ���
	double	fanAngle_;			//��@�̉�]
	double	windAngle_;			//���̊p�x
	short	windCount_;			//���J�E���g
	bool	canRespawn_;		//���X�|�[���ł��邩
	VECTOR	respawnPosition_;	//�X�|�[�����W
	bool	wasTrumpet_;		//�g�����y�b�g�ɂȂ������ǂ���
	float   rad_;				//�U���p
	int		windSound_;			//���̉�
	int		respawnSound_;		//���X�|�[����
	int		inverseSound_;		//�Ђ�����Ԃ鉹
	bool	canChangeFan_;		//�ϐg�t���O
	int		changeFanSound_;	//�ϐg��
	bool	onConstructFrame_;	//�R���X�g���N�^�����t���[�����ǂ���
	char	waitHitCount_;		//�q�b�g��҂J�E���g
	VECTOR	tackleEffectPos_;	//�^�b�N���G�t�F�N�g���W

	const float		move_speed				= 0.3f;
	const double	agnle_shift_number		= 0.75;
	const double	adjust_rotation_angle_y = agnle_shift_number * -2;
	const float		rotation_angle_x		= -45.0f;

	//���
	std::shared_ptr<StateMachine::IState>	state_;
	//�ǂ̏�Ԃ�\�����Ԃ�static�֐�
	static std::shared_ptr<CharaState::OpenState> openState_()
	{
		static std::shared_ptr<CharaState::OpenState> state = std::make_shared<CharaState::OpenState>();
		return state;
	}
	static std::shared_ptr<CharaState::FanState> fanState_()
	{
		static std::shared_ptr<CharaState::FanState> state = std::make_shared<CharaState::FanState>();
		return state;
	}
	static std::shared_ptr<CharaState::TrumpetState> TrumpetState_()
	{
		static std::shared_ptr<CharaState::TrumpetState> state = std::make_shared<CharaState::TrumpetState>();
		return state;
	}
};