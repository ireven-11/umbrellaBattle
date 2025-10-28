#include"DxLib.h"
#include"ShadowMap.h"

ShadowMap::ShadowMap()
{
	//シャドウマップハンドルの作成
	shadowMapHandle_ = MakeShadowMap(shadow_map_size, shadow_map_size);

	//シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(shadowMapHandle_, shadow_map_light_vector);

	//シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(shadowMapHandle_, min_shadow_area, max_shadow_area);
}

ShadowMap::~ShadowMap()
{
	DeleteShadowMap(shadowMapHandle_);
	playersShadows.clear();
	sandBagShadows.clear();
}

void ShadowMap::addPlayerShadows(std::shared_ptr<CharaBase> chara)
{
	playersShadows.emplace_back(chara);
}

void ShadowMap::addSandBagShadows(std::shared_ptr<CharaBase> chara)
{
	sandBagShadows.emplace_back(chara);
}