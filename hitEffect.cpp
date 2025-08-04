#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"hitEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

HitEffect::HitEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/00_Basic/hit.efkefc");

	reset();
}

HitEffect::~HitEffect()
{
}

void HitEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void HitEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetisHit_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);

		//DrawEffekseer3D_Begin();
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->GetcollisionCenterPosition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y + 2.0f, position_.z);
	}
	else
	{
		//DrawEffekseer3D_End();
	}

	//エフェクトを更新
	UpdateEffekseer3D();
}

void HitEffect::draw()
{
	//Effekseerにより再生中のエフェクト全てを描画する。
	//DrawEffekseer3D();

	//引数に渡したハンドルだけ描画する
	DrawEffekseer3D_Draw(playingHandle_);
}