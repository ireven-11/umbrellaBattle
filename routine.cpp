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
#include"playUI.h"
#include"resultUI.h"
#include"resultGraph.h"
#include"sandBag.h"
#include"playGraph.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    //効果音を読み込み
    crap_           = LoadSoundMem("sound/crap.mp3");
    fanfare_        = LoadSoundMem("sound/win.mp3");
    decideSound_    = LoadSoundMem("sound/decide.mp3");
    ChangeVolumeSoundMem(crap_volume, crap_);
    ChangeVolumeSoundMem(fanfare_volume, fanfare_);
    ChangeVolumeSoundMem(decide_volume, decideSound_);

    //bgmを読み込み
    bgm_ = LoadSoundMem("sound/bgm.mp3");
    ChangeVolumeSoundMem(bgm_volume, bgm_);
    bgmPractice_ = LoadSoundMem("sound/bgm2.mp3");
    ChangeVolumeSoundMem(bgm_volume * 2, bgmPractice_);

    //サンドバッグインスタンス化
    sandBag.emplace_back(std::make_shared<SandBag>(0));

    //フォントを使えるようにする
    AddFontResourceEx("font/AprilGothicOne-R.ttf", FR_PRIVATE, NULL);

    reset();
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
Routine::~Routine()
{
    DeleteSoundMem(bgm_);
    DeleteSoundMem(bgmPractice_);
    DeleteSoundMem(crap_);
    DeleteSoundMem(fanfare_);
    DeleteSoundMem(decideSound_);
    RemoveFontResourceEx("font/AprilGothicOne-R.ttf", FR_PRIVATE, NULL);
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
    playUI          = nullptr;
    resultUI        = nullptr;
    resultGraph     = nullptr;
    sandBag.clear();
    playGraph       = nullptr;
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

        //強制リセット
        if (CheckHitKey(KEY_INPUT_R) == true)
        {
            allReset();
        }

        //fpsを設定
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
    if (sceneManager->proceedStandby())
    {
        PlaySoundMem(decideSound_, DX_PLAYTYPE_BACK, TRUE);
        PlayMovie("movie/umbrella.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
        PlaySoundMem(bgmPractice_, DX_PLAYTYPE_LOOP, TRUE);
    }
}

/// <summary>
/// スタンバイルーチン
/// </summary>
void Routine::stanby()
{
    //カメラ更新
    camera->update();

    //ステージ更新
    stage->update();
    stage->draw();

    //プレイヤー参加
    joinPlayer();

    //プレイヤーが参加している時だけ
    if (isjoiningPlayer[0] || isjoiningPlayer[1] || isjoiningPlayer[2] || isjoiningPlayer[3])
    {
        for (const auto& i : players)
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

            //サンドバッグ更新
            for (const auto& s : sandBag)
            {
                s->update(this, stage);

                //サンドバッグとの当たり判定
                i->decideKnockBackWithChara(s);
                i->collisionWindWithChara(s, stage);
            }

            //判定が終わった後にノックバック（反発）をする
            i->knockBackNow();
            for (const auto& s : sandBag)
            {
                s->knockBackNow();
            }

            //プレイヤー描画
            i->draw();

            //ui
            playUI->update(i, i->GetcontrolerNumber_());
        }

        //エフェクトマネージャー
        auto playerIt = players.begin();
        for (const auto& e : effectManager)
        {
            e->update(*playerIt);
            ++playerIt;
        }

        UpdateEffekseer3D();
        DrawEffekseer3D();

        //ステージとの当たり判定
        stage->collisionWithPlayer(players);
        stage->collisionWithPlayer(sandBag);

        //サンドバッグ描画
        for (const auto& s : sandBag)
        {
            s->draw();
        }
    }
    
    if (sceneManager->proceedPlay())
    {
        PlaySoundMem(decideSound_, DX_PLAYTYPE_BACK, TRUE);

        //プレイ画面へ行くときにcpuを参加
        joinCPU();

        StopSoundMem(bgmPractice_, 0);
        PlayMovie("movie/umbrella.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
        PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, TRUE);

        for (const auto& p : players)
        {
            p->reset();
        }
    }

    standbyUI->update(isjoiningPlayer, max_player_number);

    //コンストラクタをしたフレームの最後にそのフレームが終わることを通知する
    if (isjoiningPlayer[0] || isjoiningPlayer[1] || isjoiningPlayer[2] || isjoiningPlayer[3])
    {
        for (const auto& p : players)
        {
            if (p->GetonConstructFrame_())
            {
                p->constructFrameEnd();
            }
        }
    }
}

/// <summary>
/// プレイルーチン
/// </summary>
void Routine::play()
{
    //カメラ更新
    camera->update();

    //カウントダウンが終わってから
    if (!playGraph->GetonCountDown_())
    {
        //すてーじこうしん
        stage->updateGimmick(players);
        stage->update();

        //プレイヤー更新
        for (const auto& i : players)
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
            //DrawFormatString(100, 100 * collisionCount, GetColor(255, 0, 0), "player%d, x:%f, y:%f, z:%f", collisionCount, i->Getposition_().x, i->Getposition_().y, i->Getposition_().z);
            //DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d, moveVector(%f, %f, %f)", collisionCount, i->GetmoveVector_().x, i->GetmoveVector_().y, i->GetmoveVector_().z);
        }
    }

    //プレイヤーの座標セット
    for (const auto& i : players)
    {
        i->setPosition();
    }

    //エフェクトマネージャー
    auto playerIt = players.begin();
    for (const auto& e : effectManager)
    {
        e->update(*playerIt);
        ++playerIt;
    }
    UpdateEffekseer3D();

    //描画
    stage->draw();
    for (const auto& i : players)
    {
        //プレイヤー描画
        i->draw();

        //ui
        playUI->update(i, i->GetcontrolerNumber_());
    }
    DrawEffekseer3D();

    //プレイ画像描画
    playGraph->update();

    //勝者判定
    judgeWinner();
}

/// <summary>
/// リザルトルーチン
/// </summary>
void Routine::result()
{
    //バーチャルカメラ更新
    camera->virtualUpdate(cameraUpPosition_);

    stage->draw();
    for (const auto& p : players)
    {
        p->draw();
    }

    //ズームアップが終わり
    if (camera->GetwasZoomUP_())
    {
        //一回効果音を流す
        if (!wasPlayingSE_)
        {
            wasPlayingSE_ = true;
            PlaySoundMem(fanfare_, DX_PLAYTYPE_BACK, TRUE);
            PlaySoundMem(crap_, DX_PLAYTYPE_LOOP, TRUE);
        }

        resultUI->update(winPlayer_);
        resultGraph->update();
        if (sceneManager->proceedTitle())
        {
            PlaySoundMem(decideSound_, DX_PLAYTYPE_BACK, TRUE);
            allReset();
            StopSoundMem(crap_);
            StopSoundMem(fanfare_);
            PlayMovie("movie/umbrella.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
        }
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
    winPlayer_          = 0;
    cameraUpPosition_   = VGet(0.0f, 0.0f, 0.0f);
    wasPlayingSE_       = false;
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
        effectManager.emplace_back(std::make_shared<EffectManager>());
    }
    if (input2.Buttons[1] > 0 && !isjoiningPlayer[1])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD2));
        isjoiningPlayer[1] = true;
        effectManager.emplace_back(std::make_shared<EffectManager>());
    }
    if (input3.Buttons[1] > 0 && !isjoiningPlayer[2])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD3));
        isjoiningPlayer[2] = true;
        effectManager.emplace_back(std::make_shared<EffectManager>());
    }
    if (input4.Buttons[1] > 0 && !isjoiningPlayer[3])
    {
        players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD4));
        isjoiningPlayer[3] = true;
        effectManager.emplace_back(std::make_shared<EffectManager>());
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
            effectManager.emplace_back(std::make_shared<EffectManager>());
        }
    }
}

void Routine::allReset()
{
    sceneManager    = nullptr;
    camera          = nullptr;
    players.clear();
    stage           = nullptr;
    standbyUI       = nullptr;
    effectManager.clear();
    titleUI         = nullptr;
    titleGraph      = nullptr;
    playUI          = nullptr;
    resultUI        = nullptr;
    resultGraph     = nullptr;
    playGraph       = nullptr;
    
    sceneManager    = std::make_shared<SceneManager>();
    camera          = std::make_shared<Camera>();
    stage           = std::make_shared<Stage>();
    standbyUI       = std::make_shared<StandbyUI>("April Gothic one Regular");
    titleUI         = std::make_shared<TitleUI>("April Gothic one Regular");
    titleGraph      = std::make_shared<TitleGraph>();
    playUI          = std::make_shared<PlayUI>("April Gothic one Regular");
    resultUI        = std::make_shared<ResultUI>("April Gothic one Regular");
    resultGraph     = std::make_shared<ResultGraph>();
    playGraph       = std::make_shared<PlayGraph>();
    
    reset();
}

void Routine::judgeWinner()
{
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
        StopSoundMem(bgm_);

        if (winPlayer1)
        {
            winPlayer_          = players.at(0)->GetcontrolerNumber_();
            cameraUpPosition_   = players.at(0)->Getposition_();
        }
        else if (winPlayer2)
        {
            winPlayer_          = players.at(1)->GetcontrolerNumber_();
            cameraUpPosition_   = players.at(1)->Getposition_();
        }
        else if (winPlayer3)
        {
            winPlayer_          = players.at(2)->GetcontrolerNumber_();
            cameraUpPosition_   = players.at(2)->Getposition_();
        }
        else
        {
            winPlayer_          = players.at(3)->GetcontrolerNumber_();
            cameraUpPosition_   = players.at(3)->Getposition_();
        }
    }
}