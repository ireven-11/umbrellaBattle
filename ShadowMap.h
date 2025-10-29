#pragma once
#include<vector>

class CharaBase;
class Stage;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void addPlayerShadows(std::shared_ptr<CharaBase> chara);
	void addSandBagShadows(std::shared_ptr<CharaBase> chara);
	void addStageShadows(std::shared_ptr<Stage> stage);
	void drawToShadowMap();
	void setUse();
	void release();

private:
	int shadowMapHandle_;
	std::vector<std::shared_ptr<CharaBase>>playersShadows;
	std::vector<std::shared_ptr<CharaBase>>sandBagShadows;
	std::shared_ptr<Stage>stageShadows;

	const int		shadow_map_size			= 1024;
	const VECTOR	min_shadow_area			= VGet(-500.0f, -100.0f, -500.0f);
	const VECTOR	max_shadow_area			= VGet(500.0f, 100.0f, 500.0f);
	const VECTOR	shadow_map_light_vector = VGet(0.5f, -0.5f, 0.f);
};