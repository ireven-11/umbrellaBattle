#pragma once

const int screenWIDTH	= 1920;//画面幅(学校のｐｃにあわせてる)
const int screenHEIGHT	= 1080;//画面高さ(学校のｐｃにあわせてる)

//#defineで長い名前を短くすむようにする
#define winmainSetting HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow                                //winmainの引数
#define gameRoopSetting ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0//ゲームループの引数

//関数のプロトタイプ宣言
void ScreenSetting();
void SetFPS();