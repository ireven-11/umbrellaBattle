#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"fallEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

FallEffect::FallEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/00_Basic/fall.efkefc");

	reset();
}

FallEffect::~FallEffect()
{
	DeleteEffekseerEffect(effectHandle_);
}

void FallEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void FallEffect::update(std::shared_ptr<CharaBase> chara)
{
	if(chara->GetisFalling_() && chara->Getposition_().y < -play_position_y)
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
		SetRotationPlayingEffekseer3DEffect(playingHandle_, DX_PI / 2, 0.0f, 0.0f);

		position_ = chara->Getposition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y, position_.z);
	}

	if (!chara->GetisFalling_())
	{
		StopEffekseer3DEffect(playingHandle_);
	}
}

void FallEffect::draw()
{
	//Effekseerにより再生中のエフェクト全てを描画する。
	//DrawEffekseer3D();

	//引数に渡したハンドルだけ描画する
	//DrawEffekseer3D_Draw(playingHandle_);
}