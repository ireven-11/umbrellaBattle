#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"ChargeEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

ChargeEffect::ChargeEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/01_AndrewFM01/charge.efkefc");

	reset();
}

ChargeEffect::~ChargeEffect()
{
	StopEffekseer3DEffect(playingHandle_);
	DeleteEffekseerEffect(effectHandle_);
}

void ChargeEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void ChargeEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetisChargeTackle_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
	}

	//エフェクトが再生中は座標を更新する
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->Getposition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y + 2.0f, position_.z);
	}
}

void ChargeEffect::draw()
{
	//Effekseerにより再生中のエフェクト全てを描画する。
	//DrawEffekseer3D();

	//引数に渡したハンドルだけ描画する
	//DrawEffekseer3D_Draw(playingHandle_);
}

void ChargeEffect::stop()
{
	StopEffekseer3DEffect(playingHandle_);
}