#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"effect.h"
#include"charaBase.h"

Effect::Effect()
{
	hit_	= LoadEffekseerEffect("effect/hit.efkefc");
	fall_	= LoadEffekseerEffect("effect/fall.efkefc");
	charge_ = LoadEffekseerEffect("effect/charge.efkefc");

	playingHit_ = 0;
	playingFall_ = 0;
	playingCharge_ = 0;

	hitPosition_	= VGet(0.0f, 0.0f, 0.0f);
	fallPosition_	= VGet(0.0f, 0.0f, 0.0f);
	chargePosition_ = VGet(0.0f, 0.0f, 0.0f);
}

Effect::~Effect()
{
	DeleteEffekseerEffect(hit_);
	DeleteEffekseerEffect(fall_);
	DeleteEffekseerEffect(charge_);
}

void Effect::updateHit(std::shared_ptr<CharaBase> chara)
{
	playingHit_ = PlayEffekseer3DEffect(hit_);

	hitPosition_ = chara->Getposition_();

	SetPosPlayingEffekseer3DEffect(playingHit_, hitPosition_.x, hitPosition_.y, hitPosition_.z);
}

void Effect::updateFall(std::shared_ptr<CharaBase> chara)
{
	playingFall_ = PlayEffekseer3DEffect(fall_);

	fallPosition_ = chara->Getposition_();

	SetPosPlayingEffekseer3DEffect(playingFall_, hitPosition_.x, hitPosition_.y, hitPosition_.z);
}

void Effect::updateCharge(std::shared_ptr<CharaBase> chara)
{
	if (chara->GetisChargeTackle_())
	{
		playingCharge_ = PlayEffekseer3DEffect(charge_);

		SetScalePlayingEffekseer3DEffect(playingCharge_, charge_scale, charge_scale, charge_scale);
		SetSpeedPlayingEffekseer3DEffect(playingCharge_, charge_speed);

		chargePosition_ = chara->Getposition_();

		SetPosPlayingEffekseer3DEffect(playingCharge_, chargePosition_.x, chargePosition_.y, chargePosition_.z);
	}
}

void Effect::draw()
{
	//エフェクトを更新
	UpdateEffekseer3D();

	// Effekseerにより再生中のエフェクト全てを描画する。
	DrawEffekseer3D();
}