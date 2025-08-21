#include"DxLib.h"
#include"stage.h"
#include"player.h"
#include<math.h>
#include"fanState.h"
#include"AStar.h"
#include"calculateDistance.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage()
{
	//�X�e�[�W�w�i���Z�b�g
	skydomeHandle_ = MV1LoadModel("3dmodel/Skydome/�X�J�C�h�[��_�J��PP3/Skydome_PP3/Dome_PP301.pmx");
	MV1SetScale(skydomeHandle_, VGet(scale * 1.5, scale * 1.5, scale * 1.5));

	fallSound_ = LoadSoundMem("sound/fall.mp3");
	ChangeVolumeSoundMem(fall_sound_volume, fallSound_);

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
			if (i == 0 || i == tile_number - 1 || j == 0 || j == tile_number - 1)
			{
				//�X�e�[�W�̒[�����̕��͉����ǂݍ��܂Ȃ��悤�ɂ���
				modelHandle_[j][i] = 0;
			}
			else if (i == 1 && j == 1)
			{
				//����3d���f�����g���܂킹��悤�ɂ���
				modelHandle_[j][i]	= MV1LoadModel("3dmodel/stage/hex_grass.mv1");
				MV1SetScale(modelHandle_[j][i], VGet(scale, scale, scale));
			}
			else
			{
				modelHandle_[j][i] = MV1DuplicateModel(modelHandle_[1][1]);
				MV1SetScale(modelHandle_[j][i], VGet(scale, scale, scale));
			}	
		}
	}

	reset();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(skydomeHandle_);
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			MV1DeleteModel(modelHandle_[j][i]);
		}
	}
	DeleteSoundMem(fallSound_);
}

/// <summary>
/// �X�V
/// </summary>
void Stage::update()
{
	MV1SetPosition(skydomeHandle_, VGet(0, 0, 0));
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			MV1SetPosition(modelHandle_[j][i], position_[j][i]);
			mapChipUpdate(canExist_[j][i], j, i);
		}
	}
}

void Stage::updateGimmick(std::vector<std::shared_ptr<CharaBase>>player)
{
	addvanishingCount();
	change3dModelColor();
	vanishTile();
	collisionWithPlayer(player);
}

/// <summary>
/// �X�e�[�W��`��
/// </summary>
void Stage::draw()
{
	MV1DrawModel(skydomeHandle_);
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
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "�X�e�[�W�J�E���g�F%d", vanishingCount_);
	//DrawSphere3D(stage_center, 2.0f, 64, GetColor(255, 0, 0), GetColor(255,0,0), true);
}

/// <summary>
/// �ϐ������Z�b�g
/// </summary>
void Stage::reset()
{
	vanishingCount_		= 0;
	dicideRandomTileJ_	= 0;
	dicideRandomTileI_	= 0;
	tileCount_			= 0;
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			if (i == 0 || i == tile_number - 1 || j == 0 || j == tile_number - 1)
			{
				canExist_[j][i] = false;
			}
			else
			{
				canExist_[j][i] = true;
			}
		}
	}
}

/// <summary>
/// ���Ԍo�߂Ń^�C���������Ă���
/// </summary>
void Stage::vanishTile()
{
	//���J�E���g���ƂɃ����_�ȏꏊ�̃^�C���������Ă���
	if (vanishingCount_ == vanishing_timing && tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
		canExist_[dicideRandomTileJ_][dicideRandomTileI_] = false;
		vanishingCount_ = 0;
		tileCount_++;
	}
}

// 2D�p�̊O�ρiz�������̂݁j
float Cross2D(VECTOR a, VECTOR b) {
	return a.x * b.z - a.z * b.x;
}

 //�_���O�p�`ABC�̓����ɂ��邩�i�ӏ���܂ށj
bool HitTriangleAndPixel(VECTOR A, VECTOR B, VECTOR C, VECTOR P) {
	VECTOR AB = { B.x - A.x, 0, B.z - A.z };
	VECTOR BC = { C.x - B.x, 0, C.z - B.z };
	VECTOR CA = { A.x - C.x, 0, A.z - C.z };

	VECTOR AP = { P.x - A.x, 0, P.z - A.z };
	VECTOR BP = { P.x - B.x, 0, P.z - B.z };
	VECTOR CP = { P.x - C.x, 0, P.z - C.z };

	float c1 = Cross2D(AB, AP);
	float c2 = Cross2D(BC, BP);
	float c3 = Cross2D(CA, CP);

	// ���ׂē��������Ȃ�����i0�͕ӏ�j
	if ((c1 >= 0 && c2 >= 0 && c3 >= 0) || (c1 <= 0 && c2 <= 0 && c3 <= 0)) {
		return true;
	}

	return false;
}

bool CheckHitCircleWithTriangle(VECTOR trianglePos1, VECTOR trianglePos2, VECTOR trianglePos3, VECTOR circlePos, float radius)
{
	VECTOR edge;				//����
	VECTOR edgeStartToCirclePos;//�����̎n�_����~�̍��W�܂ŐL�т�x�N�g��
	VECTOR edgeEndToCirclePos;	//�����̏I�_����~�̍��W�܂ŐL�т�x�N�g��
	VECTOR crossProduct;		//�O��
	float shortestDistance;		//�����Ƃ̍ŒZ����
	for (auto i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			edge = VSub(trianglePos2, trianglePos1);
			edgeStartToCirclePos = VSub(circlePos, trianglePos1);
			edgeEndToCirclePos = VSub(circlePos, trianglePos2);
			crossProduct = VCross(edge, edgeStartToCirclePos);
			shortestDistance = CalculateDistance<float>(crossProduct) / CalculateDistance<float>(edge);
			break;
		case 1:
			edge = VSub(trianglePos3, trianglePos2);
			edgeStartToCirclePos = VSub(circlePos, trianglePos2);
			edgeEndToCirclePos = VSub(circlePos, trianglePos3);
			crossProduct = VCross(edge, edgeStartToCirclePos);
			shortestDistance = CalculateDistance<float>(crossProduct) / CalculateDistance<float>(edge);
			break;
		case 2:
			edge = VSub(trianglePos1, trianglePos3);
			edgeStartToCirclePos = VSub(circlePos, trianglePos3);
			edgeEndToCirclePos = VSub(circlePos, trianglePos1);
			crossProduct = VCross(edge, edgeStartToCirclePos);
			shortestDistance = CalculateDistance<float>(crossProduct) / CalculateDistance<float>(edge);
			break;
		}

		//�ŒZ���������a��菬���������瓖�����Ă�\��������
		if (shortestDistance <= radius)
		{
			//�����̊O�ɉ~�̒��S������Ƃ��͊p�x�������݊p�������瓖�����Ă�
			if (VDot(edge, edgeStartToCirclePos) * VDot(edge, edgeEndToCirclePos) <= 0)
			{
				return true;
			}

			//���a���~�ւ̃x�N�g���̋������傫�������瓖�����Ă�
			if (radius > CalculateDistance<float>(edgeStartToCirclePos) || radius > CalculateDistance<float>(edgeEndToCirclePos))
			{
				return true;
			}
		}

		//�O�p�`�̒��ɉ~�̒��S�_�����邩
		if (HitTriangleAndPixel(trianglePos1, trianglePos2, trianglePos3, circlePos))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 3d��ɘZ�p�`�𕽖ʕ`�悷��֐�
/// </summary>
/// <param name="standardPosition">�Z�p�`�̊�ƂȂ���W</param>
/// <param name="sideX">�Z�p�`�̂��̒���</param>
/// <param name="sideZ">�Z�p�`�̂��̒���</param>
/// <param name="sideZ2">�Z�p�`�̉��ł����΂����񂾂�A�����A��Ɖ��̎O�p�`�̕������邶���B�����܂ł̂��̒������Ă����΂����̂��H</param>
/// <param name="color"></param>
/// <param name="fill"></param>
void DrawHexagon3D(VECTOR standardPosition, float sideX, float sideZ, float sideZ2, int color, bool fill)
{
	const float width_adjust	= 2.0f;
	const float height_adjust	= 1.5f;
	DrawTriangle3D(VGet(standardPosition.x - sideX / width_adjust, 0.0f, standardPosition.z + sideZ2 / height_adjust),
		VGet(standardPosition.x + sideX / width_adjust, 0.0f, standardPosition.z + sideZ2 / height_adjust),
		VGet(standardPosition.x, 0.0f, standardPosition.z + sideZ / height_adjust), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / width_adjust, 0.0f, standardPosition.z + sideZ2 / height_adjust),
		VGet(standardPosition.x + sideX / width_adjust, 0.0f, standardPosition.z + sideZ2 / height_adjust),
		VGet(standardPosition.x + sideX / width_adjust, 0.0f, standardPosition.z - sideZ2 / height_adjust), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / width_adjust, 0.0f, standardPosition.z + sideZ2 / height_adjust),
		VGet(standardPosition.x - sideX / width_adjust, 0.0f, standardPosition.z - sideZ2 / height_adjust),
		VGet(standardPosition.x + sideX / width_adjust, 0.0f, standardPosition.z - sideZ2 / height_adjust), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / width_adjust, 0.0f, standardPosition.z - sideZ2 / height_adjust),
		VGet(standardPosition.x + sideX / width_adjust, 0.0f, standardPosition.z - sideZ2 / height_adjust),
		VGet(standardPosition.x, 0.0f, standardPosition.z - sideZ / height_adjust), color, fill);
}

/// <summary>
/// �v���C���[�Ɠ����蔻��
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
void Stage::collisionWithPlayer(std::vector<std::shared_ptr<CharaBase>>player)
{
	//�v���C���[��vector�i���I�z��)�ɂ��Ă�̂�3�d���[�v�ɂȂ邯�ǂ��Ⴀ�Ȃ�
	for (const auto& p : player)
	{
		//�v���C���[����@�o�Ȃ�������
		if (p->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(p->Getstate_()))
		{
			for (int i = 0; i < tile_number; i++)
			{
				for (int j = 0; j < tile_number; j++)
				{
					//�Z�p�`�̒��ɂ��邩�ǂ���
					const float width_adjust	= 2.0f;
					const float height_adjust	= 1.5f;
					VECTOR trianglePos1 = VGet(position_[j][i].x - shifting_numberX / width_adjust, 0.0f, position_[j][i].z + triangle_pointZ / height_adjust);
					VECTOR trianglePos2 = VGet(position_[j][i].x + shifting_numberX / width_adjust, 0.0f, position_[j][i].z + triangle_pointZ / height_adjust);
					VECTOR trianglePos3 = VGet(position_[j][i].x, 0.0f, position_[j][i].z + shifting_numberZ / height_adjust);
					VECTOR trianglePos4 = VGet(position_[j][i].x + shifting_numberX / width_adjust, 0.0f, position_[j][i].z - triangle_pointZ / height_adjust);
					VECTOR trianglePos5 = VGet(position_[j][i].x - shifting_numberX / width_adjust, 0.0f, position_[j][i].z - triangle_pointZ / height_adjust);
					VECTOR trianglePos6 = VGet(position_[j][i].x, 0.0f, position_[j][i].z - shifting_numberZ / height_adjust);
					if (CheckHitCircleWithTriangle(trianglePos1, trianglePos2, trianglePos3, p->Getposition_(), collision_radius_stage) ||
						CheckHitCircleWithTriangle(trianglePos1, trianglePos2, trianglePos4, p->Getposition_(), collision_radius_stage) ||
						CheckHitCircleWithTriangle(trianglePos1, trianglePos5, trianglePos4, p->Getposition_(), collision_radius_stage) ||
						CheckHitCircleWithTriangle(trianglePos5, trianglePos4, trianglePos6, p->Getposition_(), collision_radius_stage))
					{
						//�^�C�����Ȃ������痎����
						if (!canExist_[j][i] || i == 0 || i == tile_number - 1 || j == 0 || j == tile_number - 1)
						{
							if (p->Getposition_().y >= player_init_positionY && !p->GetisMovingTackle_())
							{
								p->fall();
							}
						}

						//�L�������ǂ̃^�C����ɂ��邩�����W��ۑ����Ă���
						p->SetonTilePosition(position_[j][i]);
						p->SetonTilePositionX_(i);
						p->SetonTilePositionY_(j);
						//p->SetonTilePositionY_((j - 6) * -1);
					}
				
					//�f�o�b�O�p
					//DrawFormatString(i * 270, j * 20, GetColor(255, 255, 255), "%d&%d x:%f,z:%f", j, i, position_[j][i].x, position_[j][i].z);

					//�f�o�b�O�p�Z�p�`�`��
					/*if (canExist_[j][i])
					{
						DrawHexagon3D(position_[j][i], shifting_numberX, shifting_numberZ, triangle_pointZ, GetColor(255, 255, 255), false);
					}*/
				}
			}

			//�v���C���[���X�e�[�W�O�o���痎������܂��͈�x���������
			if (p->Getposition_().x < position_[0][0].x || p->Getposition_().x > position_[tile_number - 1][tile_number - 1].x - shifting_numberX / 2
				|| p->Getposition_().z < position_[0][0].z || p->Getposition_().z > position_[tile_number - 1][tile_number - 1].z || p->Getposition_().y < player_init_positionY)
			{
				if (!p->GetisMovingTackle_())
				{
					p->fall();
				}
			}

			if (p->Getposition_().y > -2.0f && p->Getposition_().y < 0.0f)
			{
				PlaySoundMem(fallSound_, DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}
}

//�����J�E���g�𑝂₷
void Stage::addvanishingCount()
{
	if (tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
		++vanishingCount_;
	}
}

//3d���f���̐F��ς���
void Stage::change3dModelColor()
{
	//���J�E���g���ƂɃ����_�ȏꏊ�̃^�C���������Ă���
	if (vanishingCount_ == change_color_timing && tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
		//�܂������ĂȂ��^�C���������_���ɑI��ŏ���
		while (true)
		{
			dicideRandomTileJ_ = GetRand(tile_number - 1);
			dicideRandomTileI_ = GetRand(tile_number - 1);

			if (canExist_[dicideRandomTileJ_][dicideRandomTileI_])
			{
				MV1SetDifColorScale(modelHandle_[dicideRandomTileJ_][dicideRandomTileI_], GetColorF(2.0f, 2.0f, 2.0f, 1.0f));
				break;
			}
		}
	}
}