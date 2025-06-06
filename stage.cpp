#include"DxLib.h"
#include"stage.h"

Stage::Stage()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			//奇数列行と偶数行で座標をx座標をずらす
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
}

void Stage::draw()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			if (canExsist_[j][i])
			{
				MV1DrawModel(modelHandle_[j][i]);
				//デバッグ用
				DrawFormatString(100 * i, 40 * j, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[j][i].x, position_[j][i].y, position_[j][i].z);
			}
		}
	}
}

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