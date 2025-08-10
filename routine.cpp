#include"DxLib.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"
#include"stage.h"
#include"standbyUI.h"
#include"cpu.h"
#include"routine.h"
#include"EffekseerForDXLib.h"
#include"effectManager.h"
#include"titleUI.h"
#include"titleGraph.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    bgm_ = LoadSoundMem("sound/bgm.mp3");
    ChangeVolumeSoundMem(bgm_volume, bgm_);

    for (auto i = 0; i < max_player_number; i++)
    {
        effectManager.emplace_back(std::make_shared<EffectManager>());
    }

    reset();
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
Routine::~Routine()
{
    DeleteSoundMem(bgm_);
}

/// <summary>
/// ゲーム
/// </summary>
void Routine::game()
{
    //ゲームループ呼び出し
    gameRoop();

    //ゲームループが終わったらデリート
    sceneManager    = nullptr;
    camera          = nullptr;
    stage           = nullptr;
    standbyUI       = nullptr;
    titleUI         = nullptr;
    players.clear();
    effectManager.clear();
    titleUI         = nullptr;
    titleGraph      = nullptr;
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
        
        camera->update();

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

        //強制リセット
        if (CheckHitKey(KEY_INPUT_R) == true)
        {
            allReset();
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
    //画像
    titleGraph->update();

    //ui
    titleUI->update();

    //シーン遷移
    sceneManager->proceedStandby();
}

/// <summary>
/// スタンバイルーチン
/// </summary>
void Routine::stanby()
{
    joinPlayer();

    if (sceneManager->proceedPlay())
    {
        //プレイ画面へ行くときにcpuを参加
        joinCPU();

        PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, TRUE);
    }

    standbyUI->update(isjoiningPlayer, max_player_number);
}

/// <summary>
/// プレイルーチン
/// </summary>
void Routine::play()
{
    //すてーじこうしん
    stage->update(players);

    //だれっとあたってるかのカウント
    short collisionCount = 0;
    for (const auto& i:players)
    {
        i->update(this, stage);

        //二重範囲forにして当たり判定をチェック
        for (const auto& j : players)
        {
            //この条件分がなかったらバグるので注意
            if (i != j)
            {
                //ノックバック量（反発量）を決める
                i->decideKnockBackWithChara(j);

                //風の当たり判定
                i->collisionWindWithChara(j, stage);
            }
        }

        //判定が終わった後にノックバック（反発）をする
        i->knockBackNow();

        //デバッグ用
        //DrawSphere3D(i->GetcollisionCenterPosition_(), collision_radius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
        //DrawSphere3D(i->Getposition_(), collision_radius_stage, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
        //DrawSphere3D(i->GetwindPosition_(), collision_radius_wind, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
        //DrawSphere3D(stage_center, collision_radius_wind, 32, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
        ++collisionCount;
        //DrawFormatString(100, 100 * collisionCount, GetColor(255, 0, 0), "player%d, x:%f, y:%f, z:%f", collisionCount, i->Getposition_().x, i->Getposition_().y, i->Getposition_().z);
        //DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d, moveVector(%f, %f, %f)", collisionCount, i->GetmoveVector_().x, i->GetmoveVector_().y, i->GetmoveVector_().z);
        DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d,HP:%d", collisionCount, i->Gethp_());

        //プレイヤー描画
        i->draw();
    }

    //エフェクトマネージャー
    auto playerIt = players.begin();//プレイヤーイテレーター
    for (const auto& e : effectManager)
    {
        e->update(*playerIt);
        ++playerIt;
    }

    DrawEffekseer3D();
    UpdateEffekseer3D();

    //勝利判定
    auto winPlayer1 = players.at(0)->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(players.at(0)->Getstate_())
        && players.at(1)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(1)->Getstate_())
        && players.at(2)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(2)->Getstate_())
        && players.at(3)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(3)->Getstate_());
    auto winPlayer2 = players.at(0)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(0)->Getstate_())
        && players.at(1)->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(players.at(1)->Getstate_())
        && players.at(2)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(2)->Getstate_())
        && players.at(3)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(3)->Getstate_());
    auto winPlayer3 = players.at(0)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(0)->Getstate_())
        && players.at(1)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(1)->Getstate_())
        && players.at(2)->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(players.at(2)->Getstate_())
        && players.at(3)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(3)->Getstate_());
    auto winPlayer4 = players.at(0)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(0)->Getstate_())
        && players.at(1)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(1)->Getstate_())
        && players.at(2)->Getstate_() == std::dynamic_pointer_cast<CharaState::FanState>(players.at(2)->Getstate_())
        && players.at(3)->Getstate_() != std::dynamic_pointer_cast<CharaState::FanState>(players.at(3)->Getstate_());
    if (winPlayer1 || winPlayer2 || winPlayer3 || winPlayer4)
    {
        sceneManager->proceedResult();
    }
}

/// <summary>
/// リザルトルーチン
/// </summary>
void Routine::result()
{
    if (sceneManager->proceedTitle())
    {
        allReset();
    }
    
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

/// <summary>
/// プレイヤー参加
/// </summary>
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
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD1));
        isjoiningPlayer[0] = true;
    }
    if (input2.Buttons[1] > 0 && !isjoiningPlayer[1])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD2));
        isjoiningPlayer[1] = true;
    }
    if (input3.Buttons[1] > 0 && !isjoiningPlayer[2])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD3));
        isjoiningPlayer[2] = true;
    }
    if (input4.Buttons[1] > 0 && !isjoiningPlayer[3])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD4));
        isjoiningPlayer[3] = true;
    }
}

/// <summary>
/// cpu参加
/// </summary>
void Routine::joinCPU()
{
    for (auto i = 0; i < max_player_number; i++)
    {
        //プレイヤーが参加してなければ
        if (!isjoiningPlayer[i])
        {
            players.emplace_back(std::make_shared<CPU>(i + 1));
        }
    }
}

void Routine::allReset()
{
    sceneManager = nullptr;
    camera = nullptr;
    players.clear();
    stage = nullptr;
    standbyUI = nullptr;
    effectManager.clear();
    titleUI = nullptr;
    titleGraph = nullptr;

    sceneManager = std::make_shared<SceneManager>();
    camera = std::make_shared<Camera>();
    stage = std::make_shared<Stage>();
    standbyUI = std::make_shared<StandbyUI>();
    for (auto i = 0; i < max_player_number; i++)
    {
        effectManager.emplace_back(std::make_shared<EffectManager>());
    }
    titleUI     = std::make_shared<TitleUI>();
    titleGraph  = std::make_shared<TitleGraph>();
    reset();
}