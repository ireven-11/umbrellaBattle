#include"DxLib.h"
#include"stage.h"
#include"player.h"
#include<math.h>

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
				position_[j][i] = VGet(init_posX + i * shifting_numberX, 0.0f, init_posZ + j * shifting_numberZ);
			}
			else
			{
				position_[j][i] = VGet(init_posX + i * shifting_numberX - shifting_numberX / 2, 0.0f, init_posZ + j * shifting_numberZ);
			}
			//����3d���f�����g���܂킹��悤�ɂ���
			if (i == 0 && j == 0)
			{
				modelHandle_[j][i] = MV1LoadModel("3dmodel/stage/hex_grass.mv1");
			}
			else
			{
				modelHandle_[j][i] = MV1DuplicateModel(modelHandle_[0][0]);
			}
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
void Stage::update(shared_ptr<Player> player)
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
	collisionWithPlayer(player);
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
			if (canExist_[j][i])
			{
				MV1DrawModel(modelHandle_[j][i]);
				//�f�o�b�O�p
				//DrawFormatString(100 * i, 40 * j, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[j][i].x, position_[j][i].y, position_[j][i].z);
			}
		}
	}

	//�f�o�b�O�p
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
			canExist_[j][i] = true;
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

			if (canExist_[tempRandomJ][tempRandomI])
			{
				canExist_[tempRandomJ][tempRandomI] = false;
				break;
			}
		}
	}
}

/// <summary>
/// ��_���O�p�`�̒��ɂ��邩�m�F����
/// </summary>
/// <param name="trianglePos0"></param>
/// <param name="trianglePos1"></param>
/// <param name="trianglePos2"></param>
/// <param name="pixelPos"></param>
/// <returns></returns>
bool Stage::hitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos)
{
	return true;
}

/// <summary>
/// �v���C���[�Ɠ����蔻��
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
void Stage::collisionWithPlayer(shared_ptr<Player> player)
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			if (canExist_[j][i])
			{
				if (hitTriangleAndPixel(VGet(position_[j][i].x - shifting_numberX * scale, 0.0f,position_[j][i].z),
					VGet(position_[j][i].x + shifting_numberX * scale, 0.0f, position_[j][i].z),
					VGet(position_[j][i].x, 0.0f, position_[j][i].z + shifting_numberZ * scale), player->Getposition_()) ||
					hitTriangleAndPixel(VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z), player->Getposition_()) ||
					hitTriangleAndPixel(VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z), player->Getposition_()) ||
					hitTriangleAndPixel(VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z - shifting_numberZ * scale), player->Getposition_()))
				{
					//���݂���^�C����ɂ���Ȃ牽�����Ȃ�
				}
				else
				{
					player->fall();
				}
				DrawTriangle3D(VGet(position_[j][i].x - shifting_numberX, 0.0f, position_[j][i].z + triangle_pointZ),
					VGet(position_[j][i].x + shifting_numberX, 0.0f, position_[j][i].z + triangle_pointZ),
					VGet(position_[j][i].x, 0.0f, position_[j][i].z + shifting_numberZ), GetColor(255, 255, 255), TRUE);
				DrawTriangle3D(VGet(position_[j][i].x - shifting_numberX, 0.0f, position_[j][i].z + triangle_pointZ),
					VGet(position_[j][i].x + shifting_numberX, 0.0f, position_[j][i].z + triangle_pointZ),
					VGet(position_[j][i].x + shifting_numberX, 0.0f, position_[j][i].z - triangle_pointZ), GetColor(255, 255, 255), TRUE);
				DrawTriangle3D(VGet(position_[j][i].x - shifting_numberX, 0.0f, position_[j][i].z + triangle_pointZ),
						VGet(position_[j][i].x - shifting_numberX, 0.0f, position_[j][i].z - triangle_pointZ),
						VGet(position_[j][i].x + shifting_numberX, 0.0f, position_[j][i].z - triangle_pointZ), GetColor(255, 255, 255), TRUE);
				DrawTriangle3D(VGet(position_[j][i].x - shifting_numberX, 0.0f, position_[j][i].z - triangle_pointZ),
					VGet(position_[j][i].x + shifting_numberX, 0.0f, position_[j][i].z - triangle_pointZ),
					VGet(position_[j][i].x, 0.0f, position_[j][i].z - shifting_numberZ), GetColor(255, 255, 255), TRUE);
			}
		}
	}
}