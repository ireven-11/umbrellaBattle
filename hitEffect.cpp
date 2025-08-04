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

	//�G�t�F�N�g���Đ����͍��W���X�V����
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->GetcollisionCenterPosition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y + 2.0f, position_.z);
	}
	else
	{
		//DrawEffekseer3D_End();
	}

	//�G�t�F�N�g���X�V
	UpdateEffekseer3D();
}

void HitEffect::draw()
{
	//Effekseer�ɂ��Đ����̃G�t�F�N�g�S�Ă�`�悷��B
	//DrawEffekseer3D();

	//�����ɓn�����n���h�������`�悷��
	DrawEffekseer3D_Draw(playingHandle_);
}