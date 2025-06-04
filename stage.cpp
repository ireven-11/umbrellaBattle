#include"DxLib.h"
#include"stage.h"

Stage::Stage()
{
	vanishingCount_ = 0;
	
	for (int i = 0; i < tile_number; i++)
	{
		position_[i]	= VGet(0.0f + i * 10, 0.0f, 0.0f);
		canExsist_[i]	= true;
		modelHandle_[i] = MV1LoadModel("3dmodel/stage/hex_grass.mv1");
		MV1SetScale(modelHandle_[i], VGet(0.1f, 0.1f, 0.1f));
	}

}

Stage::~Stage()
{
	for (int i = 0; i < tile_number; i++)
	{
		MV1DeleteModel(modelHandle_[i]);
	}
}

void Stage::update()
{
	for (int i = 0; i < tile_number; i++)
	{
		MV1SetPosition(modelHandle_[i], position_[i]);
	}
	draw();
}

void Stage::draw()
{
	for (int i = 0; i < tile_number; i++)
	{
		if (canExsist_)
		{
			MV1DrawModel(modelHandle_[i]);
			DrawFormatString(100, 40 * i+10, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[i].x, position_[i].y, position_[i].z);
		}
	}
}