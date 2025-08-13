#include"DxLib.h"
#include"standbyUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StandbyUI::StandbyUI(const char* fontName)
{
	fontHandle_			= CreateFontToHandle(fontName, 50, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	fontHandleSize100_	= CreateFontToHandle(fontName, 90, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
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


	DrawStringToHandle(900, 800, "EnterKey�ŃQ�[���X�^�[�g", GetColor(255, 255, 255), fontHandle_);
}

/// <summary>
/// �����_�ŕ`��֐�(�t�H���g�w��\)
/// </summary>
/// <param name="position">�`����W</param>
/// <param name="text">�`�悵�����e�L�X�g</param>
/// <param name="color">�����̐F</param>
/// <param name="fontHandle">�t�H���g�n���h��</param>
/// <param name="brinkSpeed">�_�ŃX�s�[�h(�f�t�H���g��2�A0������Ɠ_�ł��Ȃ�)</param>
void DrawBrinkStringToHandle(VECTOR position, const char* text, int color, int fontHandle = 0, unsigned short brinkSpeed = 2)
{
	//�_�ŃX�s�[�h��0��������_�ł��Ȃ�
	if (brinkSpeed == 0)
	{
		DrawStringToHandle(position.x, position.y, text, color, fontHandle);
	}
	else
	{
		//�_�ŃJ�E���g
		static int brinkCount;
		brinkCount += 1 * brinkSpeed;
		if (brinkCount > 100)
		{
			brinkCount = 0;
		}

		//�_�ŃJ�E���g�����l�ȉ��̂Ƃ������`�悷��
		if (brinkCount > 100 / brinkSpeed)
		{
			DrawStringToHandle(position.x, position.y, text, color, fontHandle);
		}
	}
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
		DrawFormatStringToHandle(player_number_position.x + player_number_gap * i, player_number_position.y, GetColor(255, 255, 255), fontHandle_, "%dP", i + 1);
		if (isjoiningPlayer[i])
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "�Q���I", GetColor(255, 255, 255), fontHandle_);
		}
		else
		{
			DrawStringToHandle(wait_or_join_position.x + player_number_gap * i, wait_or_join_position.y, "�ҋ@��...", GetColor(255, 255, 255), fontHandle_);
		}
	}

	DrawBrinkStringToHandle(join_player_position, "A�{�^���ŎQ���I", GetColor(255, 50, 0), fontHandleSize100_);
	//DrawStringToHandle(join_player_position.x, join_player_position.y, "A�{�^���ŎQ���I", GetColor(255, 50, 0), fontHandleSize100_);
}