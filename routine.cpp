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
    shared_ptr<SceneManager>sceneManager = make_shared<SceneManager>();
    shared_ptr<Camera>camera = make_shared<Camera>();
    shared_ptr<Player>player = make_shared<Player>();
    shared_ptr<Stage>stage = make_shared<Stage>();

    //ゲームループ呼び出し
    gameRoop(sceneManager,player,camera,stage);

    //デリート
    sceneManager    = nullptr;
    camera          = nullptr;
    player          = nullptr;
}

/// <summary>
/// ゲームループ
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera, shared_ptr<Stage> stage)
{
    while (gameRoopSetting)
    {
        //画面に描かれた物を消す(ゲームループの最初に呼ぶ)
        ClearDrawScreen();

        switch (sceneManager->GetsceneType_())
        {
        case TITLE:
            title(sceneManager);
            break;

        case STANDBY:
            stanby(sceneManager);
            break;

        case PLAY:
            play(player, sceneManager);
            stage->update();
            break;

        case RESULT:
            result(sceneManager);
            break;

        }

        SetFPS();

        // 裏画面の内容を表画面に反映(ゲームループの最後に呼ぶ)
        ScreenFlip();
    }
}

void Routine::title(shared_ptr<SceneManager> sceneManager)
{

}

void Routine::stanby(shared_ptr<SceneManager> sceneManager)
{

}

void Routine::play(shared_ptr<Player>player, shared_ptr<SceneManager> sceneManager)
{
    player->update();
}

void Routine::result(shared_ptr<SceneManager> sceneManager)
{

}