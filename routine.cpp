#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
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
    //インスタンス化
    std::shared_ptr<SceneManager>sceneManager = std::make_shared<SceneManager>();

    //ゲームループ呼び出し
    gameRoop(sceneManager);

    //デリート
    sceneManager = nullptr;
}

/// <summary>
/// ゲームループ
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager)
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

        case PLAY:
            play();
            break;

        case RESULT:
            result();
            break;

        }

        // 裏画面の内容を表画面に反映(ゲームループの最後に呼ぶ)
        ScreenFlip();
    }
}

void Routine::title()
{

}

void Routine::play()
{

}

void Routine::result()
{

}