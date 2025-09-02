#include"EffekseerForDXLib.h"
#include"DxLib.h"
#include"setting.h"

/// <summary>
/// dxlib設定
/// </summary>
void DxlibSetting()
{
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//ウィンドウのサイズとカラーモードを決める
    ChangeWindowMode(TRUE);						//ウィンドウモードにする
    SetWindowStyleMode(7);						//最大化ボタンが存在するウインドウモードに変更

	if (DxLib_Init() == -1)return;

    // サイズ変更を可能にする
    SetWindowSizeChangeEnableFlag(TRUE, FALSE);

    // ウインドウサイズはゲーム画面と一致させる
    SetWindowSize(screenWIDTH, screenHEIGHT);

    SetMainWindowText("gamename");              //ウィンドウ（白いところ）にゲーム名を書く
    SetDrawScreen(DX_SCREEN_BACK);		        //背景をセットする
}

/// <summary>
/// fps設定
/// </summary>
void SetFPS()
{
    //waitの部分の数値を増やすほどｆｐｓがさがっていく
    const int wait = 30;
    int term;
    static int t = 0;
    term = GetNowCount() - t;
    if (wait - term > 0)
        Sleep(wait - term);
    t = GetNowCount();
}

//エフェクシア設定
int setEffekseer()
{
	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(max_effekseer_particles) == -1)
	{
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	
	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	return 0;
}