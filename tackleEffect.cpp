#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"tackleEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

TackleEffect::TackleEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/01_AndrewFM01/tackle.efkefc");

	reset();
}

TackleEffect::~TackleEffect()
{
	StopEffekseer3DEffect(playingHandle_);
	DeleteEffekseerEffect(effectHandle_);
}

void TackleEffect::reset()
{
	position_		= VGet(0.0f, 0.0f, 0.0f);
	playingHandle_	= 0;
}

void TackleEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetisMovingTackle_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale / 3);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
		SetRotationPlayingEffekseer3DEffect(playingHandle_, 0.0f, chara->GetrotationAngleY_() + DX_PI / 2, 0.0f);
	}
	else if(!chara->GetisMovingTackle_())
	{
		stop();
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->GettackleEffectPos_();
		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y + 1.5f, position_.z);
	}
}

void TackleEffect::draw()
{

}

void TackleEffect::stop()
{
	StopEffekseer3DEffect(playingHandle_);
}