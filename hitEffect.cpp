#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"hitEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

HitEffect::HitEffect()
{
	effectHandle_	= LoadEffekseerEffect("effect/00_Basic/hit.efkefc");
	effectHandle2_	= LoadEffekseerEffect("effect/01_AndrewFM01/bigHit.efkefc");

	reset();
}

HitEffect::~HitEffect()
{
	StopEffekseer3DEffect(playingHandle_);
	DeleteEffekseerEffect(effectHandle_);
}

void HitEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void HitEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetisHit_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_) && chara->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(chara->Getstate_()))
	{
		if (chara->GetOnHitStop())
		{
			playingHandle_ = PlayEffekseer3DEffect(effectHandle2_);
			SetScalePlayingEffekseer3DEffect(playingHandle_, scale * 5.0f, scale * 5.0f, scale * 5.0f);
			SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed * 1.4f);
		}
		else
		{
			playingHandle_ = PlayEffekseer3DEffect(effectHandle_);
			SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
			SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
		}
		
		position_ = chara->GetcollisionCenterPosition_();
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y + 2.0f, position_.z);
	}
}

void HitEffect::draw()
{
	//Effekseerにより再生中のエフェクト全てを描画する。
	//DrawEffekseer3D();

	//引数に渡したハンドルだけ描画する
	//DrawEffekseer3D_Draw(playingHandle_);
}


void HitEffect::stop()
{
	StopEffekseer3DEffect(playingHandle_);
}