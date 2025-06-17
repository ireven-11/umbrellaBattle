#include"DxLib.h"
#include"stage.h"
#include"player.h"
#include<math.h>

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
{
	//ステージ背景をセット
	skydomeHandle_ = MV1LoadModel("3dmodel/Skydome/スカイドーム_雨空PP3/Skydome_PP3/Dome_PP301.pmx");
	MV1SetScale(skydomeHandle_, VGet(scale, scale, scale));

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
			if (i == 0 || i == tile_number - 1 || j == 0 || j == tile_number - 1)
			{
				//ステージの端っこの方は何も読み込まないようにする
				modelHandle_[j][i] = 0;
			}
			else if (i == 1 && j == 1)
			{
				//同じ3dモデルを使いまわせるようにする
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
/// デストラクタ
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
}

/// <summary>
/// 更新
/// </summary>
void Stage::update(vector<shared_ptr<Player>>player)
{
	MV1SetPosition(skydomeHandle_, VGet(0, 0, 0));
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			MV1SetPosition(modelHandle_[j][i], position_[j][i]);
		}
	}
	draw();
	addvanishingCount();
	change3dModelColor();
	vanishTile();
	collisionWithPlayer(player);
}

/// <summary>
/// ステージを描画
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
				//デバッグ用
				//DrawFormatString(100 * i, 40 * j, GetColor(255, 255, 255), "x:%f,y:%f,z:%f", position_[j][i].x, position_[j][i].y, position_[j][i].z);
			}
		}
	}

	////デバッグ用
	//position_[1][1] = VGet(0, 0, 0);
	//MV1SetPosition(modelHandle_[1][1], position_[1][1]);
	//MV1DrawModel(modelHandle_[1][1]);

	//デバッグ用
	DrawFormatString(100, 100, GetColor(255, 255, 255), "ステージカウント：%d", vanishingCount_);
}

/// <summary>
/// 変数をリセット
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
/// 時間経過でタイルが消えていく
/// </summary>
void Stage::vanishTile()
{
	//一定カウントごとにランダな場所のタイルをけしていく
	if (vanishingCount_ == vanishing_timing && tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
		canExist_[dicideRandomTileJ_][dicideRandomTileI_] = false;
		vanishingCount_ = 0;
		tileCount_++;
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
bool HitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos)
{
	VECTOR vec0;
	vec0.x = trianglePos1.x - trianglePos0.x;
	vec0.z = trianglePos1.z - trianglePos0.z;
	float length0 = sqrt(vec0.x * vec0.x + vec0.z * vec0.z);

	VECTOR vec1;
	vec1.x = trianglePos2.x - trianglePos0.x;
	vec1.z = trianglePos2.z - trianglePos0.z;
	float length1 = sqrt(vec1.x * vec1.x + vec1.z * vec1.z);

	VECTOR boxVerTex0AndCursorVec;
	boxVerTex0AndCursorVec.x = pixelPos.x - trianglePos0.x;
	boxVerTex0AndCursorVec.z = pixelPos.z - trianglePos0.z;
	float cursorLength0 = sqrt(boxVerTex0AndCursorVec.x * boxVerTex0AndCursorVec.x + boxVerTex0AndCursorVec.z * boxVerTex0AndCursorVec.z);

	float innerProduct0 = vec0.x * vec1.x + vec0.z * vec1.z; //ABとACのなす角を求める
	float radian0 = innerProduct0 / length0 / length1;
	float degree0 = acos(radian0) / 3.14159f * 180.0f;

	float innerProduct1 = vec0.x * boxVerTex0AndCursorVec.x + vec0.z * boxVerTex0AndCursorVec.z; //ABとAPのなす角を求める
	float radian1 = innerProduct1 / length0 / cursorLength0;
	float degree1 = acos(radian1) / 3.14159f * 180.0f;

	if (degree1 > degree0) return false;

	float innerProduct2 = vec1.x * boxVerTex0AndCursorVec.x + vec1.z * boxVerTex0AndCursorVec.z; //ACとAPのなす角を求める
	float radian2 = innerProduct2 / length1 / cursorLength0;
	float degree2 = acos(radian2) / 3.14159f * 180.0f;

	if (degree2 > degree0) return false;

	VECTOR vec2;
	vec2.x = trianglePos2.x - trianglePos1.x;
	vec2.z = trianglePos2.z - trianglePos1.z;
	float length2 = sqrt(vec2.x * vec2.x + vec2.z * vec2.z);

	VECTOR vec3;
	vec3.x = trianglePos0.x - trianglePos1.x;
	vec3.z = trianglePos0.z - trianglePos1.z;
	float length3 = sqrt(vec3.x * vec3.x + vec3.z * vec3.z);

	VECTOR boxVerTex1AndCursorVec;
	boxVerTex1AndCursorVec.x = pixelPos.x - trianglePos1.x;
	boxVerTex1AndCursorVec.z = pixelPos.z - trianglePos1.z;
	float cursorLength1 = sqrt(boxVerTex1AndCursorVec.x * boxVerTex1AndCursorVec.x + boxVerTex1AndCursorVec.z * boxVerTex1AndCursorVec.z);

	float innerProduct3 = vec2.x * vec3.x + vec2.z * vec3.z;  //BCとBAのなす角を求める
	float radian3 = innerProduct3 / length2 / length3;
	float degree3 = acos(radian3) / 3.14159f * 180.0f;

	float innerProduct4 = vec2.x * boxVerTex1AndCursorVec.x + vec2.z * boxVerTex1AndCursorVec.z; //BCとBPのなす角を求める
	float radian4 = innerProduct4 / length2 / cursorLength1;
	float degree4 = acos(radian4) / 3.14159f * 180.0f;

	if (degree4 > degree3) return false;

	float innerProduct5 = vec3.x * boxVerTex1AndCursorVec.x + vec3.z * boxVerTex1AndCursorVec.z; //BAとBPのなす角を求める
	float radian5 = innerProduct5 / length3 / cursorLength1;
	float degree5 = acos(radian5) / 3.14159f * 180.0f;

	if (degree5 > degree3) return false;

	return true;
}


/// <summary>
/// 3d上に六角形を平面描画する関数
/// </summary>
/// <param name="standardPosition">六角形の基準となる座標</param>
/// <param name="sideX">六角形のｘの長さ</param>
/// <param name="sideZ">六角形のｚの長さ</param>
/// <param name="sideZ2">六角形の何でいえばいいんだろ、こう、上と下の三角形の部分あるじゃん。そこまでのｚの長さっていえばいいのか？</param>
/// <param name="color"></param>
/// <param name="fill"></param>
void DrawHexagon3D(VECTOR standardPosition, float sideX, float sideZ, float sideZ2, int color, bool fill)
{
	DrawTriangle3D(VGet(standardPosition.x - sideX / 2, 0.0f, standardPosition.z + sideZ2 / 1.5f),
		VGet(standardPosition.x + sideX / 2, 0.0f, standardPosition.z + sideZ2 / 1.5f),
		VGet(standardPosition.x, 0.0f, standardPosition.z + sideZ / 1.5f), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / 2, 0.0f, standardPosition.z + sideZ2 / 1.5f),
		VGet(standardPosition.x + sideX / 2, 0.0f, standardPosition.z + sideZ2 / 1.5f),
		VGet(standardPosition.x + sideX / 2, 0.0f, standardPosition.z - sideZ2 / 1.5f), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / 2, 0.0f, standardPosition.z + sideZ2 / 1.5f),
		VGet(standardPosition.x - sideX / 2, 0.0f, standardPosition.z - sideZ2 / 1.5f),
		VGet(standardPosition.x + sideX / 2, 0.0f, standardPosition.z - sideZ2 / 1.5f), color, fill);
	DrawTriangle3D(VGet(standardPosition.x - sideX / 2, 0.0f, standardPosition.z - sideZ2 / 1.5f),
		VGet(standardPosition.x + sideX / 2, 0.0f, standardPosition.z - triangle_pointZ / 1.5f),
		VGet(standardPosition.x, 0.0f, standardPosition.z - sideZ / 1.5f), color, fill);
}

/// <summary>
/// プレイヤーと当たり判定
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
void Stage::collisionWithPlayer(vector<shared_ptr<Player>>player)
{
	for (int i = 0; i < tile_number; i++)
	{
		for (int j = 0; j < tile_number; j++)
		{
			//プレイヤーをvector（動的配列)にしてるので3重ループになるけどしゃあない
			for (const auto& p:player)
			{
				if (HitTriangleAndPixel(VGet(position_[j][i].x - shifting_numberX / 2, 0.0f, position_[j][i].z + triangle_pointZ / 1.5f),
					VGet(position_[j][i].x + shifting_numberX / 2, 0.0f, position_[j][i].z + triangle_pointZ / 1.5f),
					VGet(position_[j][i].x, 0.0f, position_[j][i].z + shifting_numberZ / 1.5f), p->Getposition_()) ||
					HitTriangleAndPixel(VGet(position_[j][i].x - shifting_numberX / 2, 0.0f, position_[j][i].z + triangle_pointZ / 1.5f),
						VGet(position_[j][i].x + shifting_numberX / 2, 0.0f, position_[j][i].z + triangle_pointZ / 1.5f),
						VGet(position_[j][i].x + shifting_numberX / 2, 0.0f, position_[j][i].z - triangle_pointZ / 1.5f), p->Getposition_()) ||
					HitTriangleAndPixel(VGet(position_[j][i].x - shifting_numberX / 2, 0.0f, position_[j][i].z + triangle_pointZ / 1.5f),
						VGet(position_[j][i].x - shifting_numberX / 2, 0.0f, position_[j][i].z - triangle_pointZ / 1.5f),
						VGet(position_[j][i].x + shifting_numberX / 2, 0.0f, position_[j][i].z - triangle_pointZ / 1.5f), p->Getposition_()) ||
					HitTriangleAndPixel(VGet(position_[j][i].x - shifting_numberX / 2, 0.0f, position_[j][i].z - triangle_pointZ / 1.5f),
						VGet(position_[j][i].x + shifting_numberX / 2, 0.0f, position_[j][i].z - triangle_pointZ / 1.5f),
						VGet(position_[j][i].x, 0.0f, position_[j][i].z - shifting_numberZ / 1.5f), p->Getposition_()))
				{
					//タイルがなかったら落ちる
					if (!canExist_[j][i] || i == 0 || i == tile_number - 1 || j == 0 || j == tile_number - 1)
					{
						p->fall();
					}
				}
				//プレイヤーが一度落下すると落ちる
				else if (p->Getposition_().y < player_init_positionY)
				{
					p->fall();
				}
			}

			//デバッグ用
			//DrawFormatString(i * 270, j * 20, GetColor(255, 255, 255), "%d&%d x:%f,z:%f", j, i, position_[j][i].x, position_[j][i].z);

			if (canExist_[j][i])
			{
				//デバッグ用六角形描画
				DrawHexagon3D(position_[j][i], shifting_numberX, shifting_numberZ, triangle_pointZ, GetColor(255, 255, 255), false);
			}
		}
	}
}

//消すカウントを増やす
void Stage::addvanishingCount()
{
	if (tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
		//++vanishingCount_;
	}
}

//3dモデルの色を変える
void Stage::change3dModelColor()
{
	//一定カウントごとにランダな場所のタイルをけしていく
	if (vanishingCount_ == change_color_timing && tileCount_ < (tile_number - 2) * (tile_number - 2) - 1)
	{
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