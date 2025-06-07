#include"DxLib.h"
#include"stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			//���s�Ƌ����s�ō��W��x���W�����炷
			if (j % 2 == 0)
			{
				position_[j][i] = VGet(init_posX + i * shifting_number, 0.0f, init_posZ + j * (shifting_number));
			}
			else
			{
				position_[j][i] = VGet(init_posX + i * shifting_number - shifting_number / 2, 0.0f, init_posZ + j * shifting_number);
			}
			modelHandle_[j][i] = MV1LoadModel("3dmodel/stage/hex_grass.mv1");
			MV1SetScale(modelHandle_[j][i], VGet(scale, scale, scale));
		}
	}

	reset();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			MV1DeleteModel(modelHandle_[j][i]);
		}
	}
}

/// <summary>
/// �X�V
/// </summary>
void Stage::update()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			MV1SetPosition(modelHandle_[j][i], position_[j][i]);
		}
	}
	draw();
	vanishTile();
}

/// <summary>
/// �X�e�[�W��`��
/// </summary>
void Stage::draw()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			if (canExsist_[j][i])
			{
				MV1DrawModel(modelHandle_[j][i]);
				//�f�o�b�O�p
				//DrawFormatString(100 * i, 40 * j, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[j][i].x, position_[j][i].y, position_[j][i].z);
			}
		}
	}

	DrawFormatString(100, 100, GetColor(255, 255, 255), "�X�e�[�W�J�E���g�F%d", vanishingCount_);
}

/// <summary>
/// �ϐ������Z�b�g
/// </summary>
void Stage::reset()
{
	vanishingCount_ = 0;
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			canExsist_[j][i] = true;
		}
	}
}

/// <summary>
/// ���Ԍo�߂Ń^�C���������Ă���
/// </summary>
void Stage::vanishTile()
{
	if (vanishingCount_ <= vanishing_timing * (all_tile_number - 1))
	{
		++vanishingCount_;
	}
	//���J�E���g���ƂɃ����_�ȏꏊ�̃^�C���������Ă���
	if (vanishingCount_ % vanishing_timing == 0 && vanishingCount_ != 0)
	{
		while (true)
		{
			int tempRandomJ = GetRand(4);
			int tempRandomI = GetRand(4);

			if (canExsist_[tempRandomJ][tempRandomI])
			{
				canExsist_[tempRandomJ][tempRandomI] = false;
				break;
			}
		}
	}
}