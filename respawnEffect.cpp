#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"respawnEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

RespawnEffect::RespawnEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/02_Tktk03/respawn.efkefc");

	reset();
}

RespawnEffect::~RespawnEffect()
{
	DeleteEffekseerEffect(effectHandle_);
}

void RespawnEffect::reset()
{
	position_		= VGet(0.0f, 0.0f, 0.0f);
	playingHandle_	= 0;
}

void RespawnEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetcanRespawn_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);

		position_ = chara->GetrespawnPosition_();
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y, position_.z);
	}
}

void RespawnEffect::draw()
{

}