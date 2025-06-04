#pragma once

constexpr int tile_number = 16;

class Stage
{
public:
	Stage();
	~Stage();

	void update();
	void draw();

private:
	int		modelHandle_[tile_number];	//モデルハンドル
	VECTOR	position_[tile_number];		//座標
	bool	canExsist_[tile_number];	//存在できるかフラグ
	int		vanishingCount_;			//消えるカウント
};