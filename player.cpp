#include"DxLib.h"
#include"player.h"
#include<cmath>
#include"stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(const int join_number) : CharaBase(join_number)
{
	PlaySoundMem(changeFanSound_, DX_PLAYTYPE_BACK, TRUE);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	
}