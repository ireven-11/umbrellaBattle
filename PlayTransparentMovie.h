#pragma once
#include"DxLib.h"

void PlayTransparentMovie(int movieHandle, int screenHandle, int movieWidht = 1920, int movieHeight = 1080, VECTOR position = VGet(0.0f,0.0f,0.0f), bool isLoop = true, int screenType = DX_SCREEN_BACK);