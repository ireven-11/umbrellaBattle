#include"DxLib.h"
#include"IEffect.h"
#include"fallEffect.h"
#include"windEffect.h"
#include"chargeEffect.h"
#include"hitEffect.h"
#include"respawnEffect.h"
#include"changeFanEffect.h"
#include"tackleEffect.h"
#include"charaBase.h"
#include"effectManager.h"

EffectManager::EffectManager()
{
	effects.emplace_back(std::make_shared<ChargeEffect>());
	effects.emplace_back(std::make_shared<FallEffect>());
	effects.emplace_back(std::make_shared<HitEffect>());
	effects.emplace_back(std::make_shared<WindEffect>());
	effects.emplace_back(std::make_shared<RespawnEffect>());
	effects.emplace_back(std::make_shared<ChangeFanEffect>());
	effects.emplace_back(std::make_shared<TackleEffect>());
}

EffectManager::~EffectManager()
{
	effects.clear();
}

void EffectManager::update(std::shared_ptr<CharaBase> charaBase)
{
	for (const auto& effect : effects)
	{
		effect->update(charaBase);
	}
}

void EffectManager::draw()
{
	for (const auto& effect : effects)
	{
		effect->draw();
	}
}

void EffectManager::stop()
{
	for (const auto& effect : effects)
	{
		effect->stop();
	}
}