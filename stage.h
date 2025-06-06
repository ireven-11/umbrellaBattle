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
	int		modelHandle_[tile_number][tile_number];	//���f���n���h��
	VECTOR	position_[tile_number][tile_number];	//���W
	bool	canExsist_[tile_number][tile_number];	//���݂ł��邩�t���O
	int		vanishingCount_;						//������J�E���g
};