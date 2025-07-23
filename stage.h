#pragma once
#include<memory>
#include<vector>

constexpr	int		tile_number			= 7;
constexpr	int		all_tile_number		= tile_number * tile_number;
constexpr	float	init_posX			= -25.0f;
constexpr	float	init_posZ			= -10.0f;
constexpr	float	scale				= 0.05;
constexpr	float	shifting_numberX	= 185.0f * scale;
constexpr	float	shifting_numberZ	= shifting_numberX * 0.85f;
constexpr	float	triangle_pointZ		= shifting_numberX * 0.45f;
constexpr	int		vanishing_timing	= 200;
constexpr	int		change_color_timing = 150;
constexpr	float	stage_radius		= 37.5f;
const		VECTOR	stage_center		= VGet(-2.0f, 0.0f, 15.0f);
const		float	sphereRad			= 185.0f * scale / 1.6f;

class CharaBase;

class Stage
{
public:
	Stage();
	~Stage();

	void update(std::vector<std::shared_ptr<CharaBase>>player);
	void draw();
	void reset();
	void collisionWithPlayer(std::vector<std::shared_ptr<CharaBase>>player);
	const VECTOR (&Getposition_()const) [tile_number][tile_number]{ return position_; }

private:
	void vanishTile();
	void addvanishingCount();
	void change3dModelColor();
	
	int		modelHandle_[tile_number][tile_number];	//���f���n���h��
	VECTOR	position_[tile_number][tile_number];	//���W
	bool	canExist_[tile_number][tile_number];	//���݂ł��邩�t���O
	int		vanishingCount_;						//������J�E���g
	int		skydomeHandle_;							//�X�J�C�h�[���n���h��
	int		dicideRandomTileJ_;						//�^�C���p�����_���ϐ�j
	int		dicideRandomTileI_;						//�^�C���p�����_���ϐ�i
	int		tileCount_;								//�^�C���������������̃J�E���g
};

bool HitTriangleAndPixel(VECTOR trianglePos0, VECTOR trianglePos1, VECTOR trianglePos2, VECTOR pixelPos);
void DrawHexagon3D(VECTOR standardPosition, float sideX, float sideZ, float sideZ2, int color, bool fill);