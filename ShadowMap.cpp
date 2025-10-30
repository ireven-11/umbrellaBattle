#include"DxLib.h"
#include"charaBase.h"
#include"stage.h"
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
	stageShadows = nullptr;
}

void ShadowMap::addPlayerShadows(std::shared_ptr<CharaBase> chara)
{
	playersShadows.emplace_back(chara);
}

void ShadowMap::addSandBagShadows(std::shared_ptr<CharaBase> chara)
{
	sandBagShadows.emplace_back(chara);
}

void ShadowMap::addStageShadows(std::shared_ptr<Stage> stage)
{
	stageShadows = stage;
}

void ShadowMap::drawStageToShadowMap()
{
	//描画されてないときは影を描画しない
	if (!stageShadows->isDrawing())return;

	stageShadows->draw();
}

void ShadowMap::drawPlayerToShadowMap()
{
	for (const auto& shadows : playersShadows)
	{
		//描画されてないときは影を描画しない
		if (!shadows->isDrawing())continue;

		shadows->draw();
	}
}

void ShadowMap::drawSandBagToShadowMap()
{
	for (const auto& shadows : sandBagShadows)
	{
		//描画されてないときは影を描画しない
		if (!shadows->isDrawing())continue;

		shadows->draw();
	}
}

void ShadowMap::drawToShadowMap()
{
	//シャドウマップへの描画の準備
	ShadowMap_DrawSetup(shadowMapHandle_);

	drawStageToShadowMap();
	drawPlayerToShadowMap();
	drawSandBagToShadowMap();

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();
}

void ShadowMap::setUse()
{
	SetUseShadowMap(0, shadowMapHandle_);

	//TestDrawShadowMap(shadowMapHandle_, 0, 0, 1920, 1080);
}

void ShadowMap::release()
{
	SetUseShadowMap(0, -1);
}