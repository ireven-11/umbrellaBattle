#include"Dxlib.h"
#include"charaBase.h"
#include"cpuBrain.h"
#include"cpu.h"
#include"stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="join_number">��P���̐���</param>
CPU::CPU(const int join_number) : CharaBase(join_number)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CPU::~CPU()
{
}

void CPU::update(Routine* routine, std::shared_ptr<Stage> stage)
{
	//�R���g���[���[�̓��͏�Ԃ��擾����
	GetJoypadDirectInputState(controlerNumber_, &input);

	//��Ԃɂ���čs����ς���
	brain_->update(this, routine, stage);
	state_->update(this);

	//�ł΂������Z�b�g
	if (CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.y = 0.0f;
	}

	MV1SetPosition(openingUmbrella_, position_);
	MV1SetPosition(closingUmbrella_, position_);
	MV1SetPosition(fan_, position_);
	draw();
}

void CPU::wind()
{
	//���𔭐�������
	if (canSpawnWind_)
	{
		canSpawnWind_ = false;
		windPosition_ = position_;
		windMoveVector_ = VSub(stage_center, position_);
		windAngle_ = fanAngle_;
		PlaySoundMem(windSound_, DX_PLAYTYPE_BACK, TRUE);
	}
	//�ړ�
	if (!canSpawnWind_)
	{
		++windCount_;
		windPosition_ = VAdd(windPosition_, VGet(windMoveVector_.x / 35, windMoveVector_.y / 35, windMoveVector_.z / 35));

		//��������
		if (max_wind_count < windCount_)
		{
			canSpawnWind_	= true;
			windCount_		= 0;
			StopSoundMem(windSound_);
		}
	}
}