#pragma once
#include<memory>
using namespace std;

constexpr int	tile_number			= 5;
constexpr int	all_tile_number		= tile_number * tile_number;
constexpr float init_posX			= -20.0f;
constexpr float init_posZ			= 0.0f;
constexpr float scale				= 0.05;
constexpr float shifting_numberX	= 200.0f * scale;
constexpr float shifting_numberZ	= shifting_numberX * 0.85f;
constexpr float triangle_pointZ		= shifting_numberX * 0.45f;
constexpr int	vanishing_timing	= 200;

class Player;

class Stage
{
public:
	Stage();
	~Stage();

	void update(shared_ptr<Player> player);
	void draw();
	void reset();
	void collisionWithPlayer(shared_ptr<Player> player);

private:
	void vanishTile();
	bool hitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos);

	int		modelHandle_[tile_number][tile_number];	//モデルハンドル
	VECTOR	position_[tile_number][tile_number];	//座標
	bool	canExist_[tile_number][tile_number];	//存在できるかフラグ
	int		vanishingCount_;						//消えるカウント
};