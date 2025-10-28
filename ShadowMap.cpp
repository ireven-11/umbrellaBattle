#include"DxLib.h"
#include"ShadowMap.h"

ShadowMap::ShadowMap()
{
	//シャドウマップハンドルの作成
	shadowMapHandle_ = MakeShadowMap(shadow_map_size, shadow_map_size);

	//ライトの方向を設定
	SetLightDirection(shadow_map_light_vector);

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

void ShadowMap::drawToShadowMap()
{
	//シャドウマップへの描画の準備
	ShadowMap_DrawSetup(shadowMapHandle_);

	for (const auto& shadows : playersShadows)
	{
		shadows->draw();
	}
	for (const auto& shadows : sandBagShadows)
	{
		shadows->draw();
	}

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();
}

void ShadowMap::setUse()
{
	SetUseShadowMap(0, shadowMapHandle_);
}

void ShadowMap::release()
{
	SetUseShadowMap(0, -1);
}