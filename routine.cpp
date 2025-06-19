#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"
#include"stage.h"
#include"standbyUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    reset();
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
Routine::~Routine()
{
}

/// <summary>
/// ゲーム
/// </summary>
void Routine::game()
{
    //ゲームループ呼び出し
    gameRoop();

    //デリート
    sceneManager    = nullptr;
    camera          = nullptr;
    player.clear();
    stage           = nullptr;
    standbyUI       = nullptr;
}

/// <summary>
/// ゲームループ
/// </summary>
void Routine::gameRoop()
{
    while (gameRoopSetting)
    {
        //画面に描かれた物を消す(ゲームループの最初に呼ぶ)
        ClearDrawScreen();

        switch (sceneManager->GetsceneType_())
        {
        case TITLE:
            title();
            break;

        case STANDBY:
            stanby();
            break;

        case PLAY:
            play();
            break;

        case RESULT:
            result();
            break;

        }

        SetFPS();

        // 裏画面の内容を表画面に反映(ゲームループの最後に呼ぶ)
        ScreenFlip();
    }
}

/// <summary>
/// タイトルルーチン
/// </summary>
void Routine::title()
{

}

/// <summary>
/// スタンバイルーチン
/// </summary>
void Routine::stanby()
{
    joinPlayer();

    sceneManager->proceedPlay();

    standbyUI->update(isjoiningPlayer, max_player_number);
}

/// <summary>
/// プレイルーチン
/// </summary>
void Routine::play()
{
    stage->update(player);

    for (const auto& i:player)
    {
        i->update();
    }
}

/// <summary>
/// リザルトルーチン
/// </summary>
void Routine::result()
{

}

/// <summary>
/// 変数をリセット
/// </summary>
void Routine::reset()
{
    for (int i = 0; i < max_player_number; i++)
    {
        isjoiningPlayer[i] = false;
    }
}

void Routine::joinPlayer()
{
    //コントローラー(D)用構造体変数
    DINPUT_JOYSTATE input1;
    DINPUT_JOYSTATE input2;
    DINPUT_JOYSTATE input3;
    DINPUT_JOYSTATE input4;

    //コントローラーを使えるようにする
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input1);
    GetJoypadDirectInputState(DX_INPUT_PAD2, &input2);
    GetJoypadDirectInputState(DX_INPUT_PAD3, &input3);
    GetJoypadDirectInputState(DX_INPUT_PAD4, &input4);
    //プレイヤーはコントローラのAボタンを押したら参加できる
    if (input1.Buttons[1] > 0 && !isjoiningPlayer[0])
    {
        player.emplace_back(make_shared<Player>(DX_INPUT_PAD1));
        isjoiningPlayer[0] = true;
    }
    if (input2.Buttons[1] > 0 && !isjoiningPlayer[1])
    {
        player.emplace_back(make_shared<Player>(DX_INPUT_PAD2));
        isjoiningPlayer[1] = true;
    }
    if (input3.Buttons[1] > 0 && !isjoiningPlayer[2])
    {
        player.emplace_back(make_shared<Player>(DX_INPUT_PAD3));
        isjoiningPlayer[2] = true;
    }
    if (input4.Buttons[1] > 0 && !isjoiningPlayer[3])
    {
        player.emplace_back(make_shared<Player>(DX_INPUT_PAD4));
        isjoiningPlayer[3] = true;
    }
}