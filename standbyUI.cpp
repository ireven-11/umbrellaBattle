#include"DxLib.h"
#include"standbyUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StandbyUI::StandbyUI()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StandbyUI::~StandbyUI()
{
}

void StandbyUI::update(bool isjoiningPlayer[], const int max_player_number)
{
	playerJoin(isjoiningPlayer, max_player_number);
}

/// <summary>
/// �v���C���[���Q������ui
/// </summary>
/// <param name="isjoiningPlayer"></param>
/// <param name="max_player_number"></param>
void StandbyUI::playerJoin(bool isjoiningPlayer[], const int max_player_number)
{
	for (int i = 0; i < max_player_number; i++)
	{
		DrawFormatString(100 + 200 * i, 200, GetColor(255, 255, 255), "%dP", i + 1);
		if (isjoiningPlayer[i])
		{
			DrawString(100 + 200 * i, 300, "�Q���I", GetColor(255, 255, 255));
		}
		else
		{
			DrawString(100 + 200 * i, 300, "�ҋ@��...", GetColor(255, 255, 255));
		}
	}

	DrawString(900, 800, "EnterKey�ŃQ�[���X�^�[�g", GetColor(255, 255, 255));
	DrawString(900, 700, "A�{�^���ŎQ���I", GetColor(255, 255, 255));
}