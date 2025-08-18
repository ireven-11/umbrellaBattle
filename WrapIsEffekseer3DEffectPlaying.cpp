#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"WrapIsEffekseer3DEffectPlaying.h"

bool WrapIsEffekseer3DEffectPlaying(int playingEffectHandle)
{
	if (IsEffekseer3DEffectPlaying(playingEffectHandle) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
