#pragma once

constexpr int	tile_number		= 4;
constexpr float init_posX		= -20.0f;
constexpr float init_posZ		= 0.0f;
constexpr float shifting_number	= 10.0f;
constexpr float scale			= 0.05;

class Stage
{
public:
	Stage();
	~Stage();

	void update();
	void draw();
	void reset();

private:
	int		modelHandle_[tile_number][tile_number];	//モデルハンドル
	VECTOR	position_[tile_number][tile_number];	//座標
	bool	canExsist_[tile_number][tile_number];	//存在できるかフラグ
	int		vanishingCount_;						//消えるカウント
};