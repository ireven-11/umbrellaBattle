#include"DxLib.h"
#include"IEffect.h"
#include"charaBase.h"
#include"WindEffect.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

WindEffect::WindEffect()
{
	effectHandle_ = LoadEffekseerEffect("effect/00_Version16/Aura01.efkefc");

	reset();
}

WindEffect::~WindEffect()
{
	DeleteEffekseerEffect(effectHandle_);
}

void WindEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void WindEffect::update(std::shared_ptr<CharaBase> chara)
{
	if (!chara->GetcanSpawnWind_() && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
	}

	//�G�t�F�N�g���Đ����͍��W���X�V����
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->GetwindPosition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y, position_.z);
	}
	
	//Effect���~�߂�
	if (chara->GetcanSpawnWind_() || chara->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(chara->Getstate_()))
	{
		StopEffekseer3DEffect(playingHandle_);
	}
}

void WindEffect::draw()
{
	//Effekseer�ɂ��Đ����̃G�t�F�N�g�S�Ă�`�悷��B
	//DrawEffekseer3D();

	//�����ɓn�����n���h�������`�悷��
	//DrawEffekseer3D_Draw(playingHandle_);
}