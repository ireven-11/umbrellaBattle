#pragma once
#include<vector>
#include"charaBase.h"

class CharaBase;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void addPlayerShadows(std::shared_ptr<CharaBase> chara);
	void addSandBagShadows(std::shared_ptr<CharaBase> chara);

private:
	int shadowMapHandle_;
	std::vector<std::shared_ptr<CharaBase>>playersShadows;
	std::vector<std::shared_ptr<CharaBase>>sandBagShadows;

	const int		shadow_map_size			= 1024;
	const VECTOR	min_shadow_area			= VGet(-100.0f, -1.0f, -100.0f);
	const VECTOR	max_shadow_area			= VGet(100.0f, 10.0f, 100.0f);
	const VECTOR	shadow_map_light_vector = VGet(0.5f, -0.5f, 0.5f);
};