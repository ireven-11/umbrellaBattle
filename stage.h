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
	int		modelHandle_[tile_number];	//���f���n���h��
	VECTOR	position_[tile_number];		//���W
	bool	canExsist_[tile_number];	//���݂ł��邩�t���O
	int		vanishingCount_;			//������J�E���g
};