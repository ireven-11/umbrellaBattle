#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"
#include"stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    player.emplace_back(make_shared<Player>());
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