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
}

void FallEffect::reset()
{
	playingHandle_	= 0;
	position_		= VGet(0.0f, 0.0f, 0.0f);
}

void FallEffect::update(std::shared_ptr<CharaBase> chara)
{
	if(chara->GetisFalling_() && chara->Getposition_().y < -play_position_y && !WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		playingHandle_ = PlayEffekseer3DEffect(effectHandle_);

		SetScalePlayingEffekseer3DEffect(playingHandle_, scale, scale, scale);
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, play_speed);
		SetRotationPlayingEffekseer3DEffect(playingHandle_, DX_PI / 2, 0.0f, 0.0f);

		//DrawEffekseer3D_Begin();
	}

	//�G�t�F�N�g���Đ����͍��W���X�V����
	if (WrapIsEffekseer3DEffectPlaying(playingHandle_))
	{
		position_ = chara->Getposition_();

		SetPosPlayingEffekseer3DEffect(playingHandle_, position_.x, position_.y, position_.z);
	}
	else
	{
		//DrawEffekseer3D_End();
	}

	//�G�t�F�N�g���X�V
	UpdateEffekseer3D();
}

void FallEffect::draw()
{
	//Effekseer�ɂ��Đ����̃G�t�F�N�g�S�Ă�`�悷��B
	//DrawEffekseer3D();

	//�����ɓn�����n���h�������`�悷��
	DrawEffekseer3D_Draw(playingHandle_);
}