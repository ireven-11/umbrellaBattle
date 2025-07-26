#include"DxLib.h"
#include"setting.h" 
#include"EffekseerForDXlib.h"
#include"routine.h"

int WINAPI WinMain(winmainSetting)
{
    //画面設定
    ScreenSetting();

    //dxlibを初期化
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    //エフェクシア設定
    setEffekseer();

    //ルーチンをインスタンス化してゲーム開始して終わったらデリート
    std::shared_ptr<Routine>routine = std::make_shared<Routine>();
    routine->game();
    routine = nullptr;

    //Effekseerを終了する。
    Effkseer_End();

    DxLib_End();
    return 0;
}