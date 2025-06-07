#pragma once

constexpr int	tile_number			= 5;
constexpr int	all_tile_number		= tile_number * tile_number;
constexpr float init_posX			= -20.0f;
constexpr float init_posZ			= 0.0f;
constexpr float shifting_number		= 10.0f;
constexpr float scale				= 0.05;
constexpr int	vanishing_timing	= 200;

class Stage
{
public:
	Stage();
	~Stage();

	void update();
	void draw();
	void reset();

private:
	void vanishTile();

	int		modelHandle_[tile_number][tile_number];	//���f���n���h��
	VECTOR	position_[tile_number][tile_number];	//���W
	bool	canExsist_[tile_number][tile_number];	//���݂ł��邩�t���O
	int		vanishingCount_;						//������J�E���g
};