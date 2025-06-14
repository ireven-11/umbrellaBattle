#pragma once
#include<memory>
#include<vector>
using namespace std;

constexpr int	tile_number			= 7;
constexpr int	all_tile_number		= tile_number * tile_number;
constexpr float init_posX			= -25.0f;
constexpr float init_posZ			= -10.0f;
constexpr float scale				= 0.05;
constexpr float shifting_numberX	= 185.0f * scale;
constexpr float shifting_numberZ	= shifting_numberX * 0.85f;
constexpr float triangle_pointZ		= shifting_numberX * 0.45f;
constexpr int	vanishing_timing	= 200;
constexpr int	change_color_timing = 150;

class Player;

class Stage
{
public:
	Stage();
	~Stage();

	void update(vector<shared_ptr<Player>>player);
	void draw();
	void reset();
	void collisionWithPlayer(vector<shared_ptr<Player>>player);

private:
	void vanishTile();
	void addvanishingCount();
	void change3dModelColor();

	int		modelHandle_[tile_number][tile_number];	//モデルハンドル
	VECTOR	position_[tile_number][tile_number];	//座標
	bool	canExist_[tile_number][tile_number];	//存在できるかフラグ
	int		vanishingCount_;						//消えるカウント
	int		skydomeHandle_;							//スカイドームハンドル
	int		dicideRandomTileJ_;						//タイル用ランダム変数j
	int		dicideRandomTileI_;						//タイル用ランダム変数i
};

bool HitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos);
void DrawHexagon3D(VECTOR standardPosition, float sideX, float sideZ, float sideZ2, int color, bool fill);