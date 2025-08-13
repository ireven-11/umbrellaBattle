#include"DxLib.h"
#include"DrawBrinkStringToHandle.h"

/// <summary>
/// �����_�ŕ`��֐�(�t�H���g�w��\)
/// </summary>
/// <param name="position">�`����W</param>
/// <param name="text">�`�悵�����e�L�X�g</param>
/// <param name="color">�����̐F</param>
/// <param name="fontHandle">�t�H���g�n���h��</param>
/// <param name="brinkSpeed">�_�ŃX�s�[�h(�f�t�H���g��2�A0������Ɠ_�ł��Ȃ�)</param>
void DrawBrinkStringToHandle(VECTOR position, const char* text, int color, int fontHandle, unsigned short brinkSpeed)
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