#include"Dxlib.h"
#include"charaBase.h"
#include"cpuBrain.h"
#include"cpu.h"

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

void CPU::update(Routine* routine)
{
	//�R���g���[���[�̓��͏�Ԃ��擾����
	GetJoypadDirectInputState(controlerNumber_, &input);

	//��Ԃɂ���čs����ς���
	brain_->update(this, routine);
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