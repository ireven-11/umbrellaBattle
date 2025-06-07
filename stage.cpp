#include"DxLib.h"
#include"stage.h"
#include"player.h"
#include<math.h>

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			//奇数列行と偶数行で座標をx座標をずらす
			if (j % 2 == 0)
			{
				position_[j][i] = VGet(init_posX + i * shifting_numberX, 0.0f, init_posZ + j * shifting_numberZ);
			}
			else
			{
				position_[j][i] = VGet(init_posX + i * shifting_numberX - shifting_numberX / 2, 0.0f, init_posZ + j * shifting_numberZ);
			}
			//同じ3dモデルを使いまわせるようにする
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
/// デストラクタ
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
/// 更新
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
/// ステージを描画
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
				//デバッグ用
				//DrawFormatString(100 * i, 40 * j, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[j][i].x, position_[j][i].y, position_[j][i].z);
			}
		}
	}

	//デバッグ用
	DrawFormatString(100, 100, GetColor(255, 255, 255), "ステージカウント：%d", vanishingCount_);
}

/// <summary>
/// 変数をリセット
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
/// 時間経過でタイルが消えていく
/// </summary>
void Stage::vanishTile()
{
	if (vanishingCount_ <= vanishing_timing * (all_tile_number - 1))
	{
		++vanishingCount_;
	}
	//一定カウントごとにランダな場所のタイルをけしていく
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
/// 一点が三角形の中にあるか確認する
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
/// プレイヤーと当たり判定
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
					//存在するタイル上にいるなら何もしない
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