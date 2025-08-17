#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"changeFanEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

ChangeFanEffect::ChangeFanEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/00_Basic/changeFan.efkefc");

	reset();
}

ChangeFanEffect::~ChangeFanEffect()
{
	StopEffekseer3DEffect(playingHandle_);
	DeleteEffekseerEffect(effectHandle_);
}

void ChangeFanEffect::reset()
{
	position_ = VGet(0.0f, 0.0f, 0.0f);
	playingHandle_ = 0;
}

void ChangeFanEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetcanChangeFan_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_) || chara->GetonConstructFrame_())
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);

		position_ = chara->Getposition_();
		chara->cannotChangeFan();
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y, position_.z);
	}
}

void ChangeFanEffect::draw()
{

}

void ChangeFanEffect::stop()
{
	StopEffekseer3DEffect(playingHandle_);
}