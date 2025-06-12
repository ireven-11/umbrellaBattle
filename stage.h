#pragma once
#include<memory>
#include<vector>
using namespace std;

constexpr int	tile_number			= 7;
constexpr int	all_tile_number		= tile_number * tile_number;
constexpr float init_posX			= -25.0f;
constexpr float init_posZ			= -10.0f;
constexpr float scale				= 0.05;
constexpr float shifting_numberX	= 190.0f * scale;
constexpr float shifting_numberZ	= shifting_numberX * 0.85f;
constexpr float triangle_pointZ		= shifting_numberX * 0.45f;
constexpr int	vanishing_timing	= 200;

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
	bool hitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos);

	int		modelHandle_[tile_number][tile_number];	//���f���n���h��
	VECTOR	position_[tile_number][tile_number];	//���W
	bool	canExist_[tile_number][tile_number];	//���݂ł��邩�t���O
	int		vanishingCount_;						//������J�E���g
	int		skydomeHandle_;							//�X�J�C�h�[���n���h��
};