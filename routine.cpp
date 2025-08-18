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
/// �R���X�g���N�^
/// </summary>
Routine::Routine()
{
    //���ʉ���ǂݍ���
    crap_           = LoadSoundMem("sound/crap.mp3");
    fanfare_        = LoadSoundMem("sound/win.mp3");
    decideSound_    = LoadSoundMem("sound/decide.mp3");
    ChangeVolumeSoundMem(crap_volume, crap_);
    ChangeVolumeSoundMem(fanfare_volume, fanfare_);
    ChangeVolumeSoundMem(decide_volume, decideSound_);

    //bgm��ǂݍ���
    bgm_ = LoadSoundMem("sound/bgm.mp3");
    ChangeVolumeSoundMem(bgm_volume, bgm_);
    bgmPractice_ = LoadSoundMem("sound/bgm2.mp3");
    ChangeVolumeSoundMem(bgm_volume * 2, bgmPractice_);

    //�T���h�o�b�O�C���X�^���X��
    sandBag.emplace_back(std::make_shared<SandBag>(0));

    //�t�H���g���g����悤�ɂ���
    AddFontResourceEx("font/AprilGothicOne-R.ttf", FR_PRIVATE, NULL);

    reset();
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
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
/// �Q�[��
/// </summary>
void Routine::game()
{
    //�Q�[�����[�v�Ăяo��
    gameRoop();

    //�Q�[�����[�v���I�������f���[�g
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
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop()
{
    while (gameRoopSetting)
    {
        //��ʂɕ`���ꂽ��������(�Q�[�����[�v�̍ŏ��ɌĂ�)
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

        //�������Z�b�g
        if (CheckHitKey(KEY_INPUT_R) == true)
        {
            allReset();
        }

        //fps��ݒ�
        SetFPS();

        // ����ʂ̓��e��\��ʂɔ��f(�Q�[�����[�v�̍Ō�ɌĂ�)
        ScreenFlip();
    }
}

/// <summary>
/// �^�C�g�����[�`��
/// </summary>
void Routine::title()
{
    //�摜
    titleGraph->update();

    //ui
    titleUI->update();

    //�V�[���J��
    if (sceneManager->proceedStandby())
    {
        PlaySoundMem(decideSound_, DX_PLAYTYPE_BACK, TRUE);
        PlayMovie("movie/umbrella.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
        PlaySoundMem(bgmPractice_, DX_PLAYTYPE_LOOP, TRUE);
    }
}

/// <summary>
/// �X�^���o�C���[�`��
/// </summary>
void Routine::stanby()
{
    //�J�����X�V
    camera->update();

    //�X�e�[�W�X�V
    stage->update();
    stage->draw();

    //�v���C���[�Q��
    joinPlayer();

    //�v���C���[���Q�����Ă��鎞����
    if (isjoiningPlayer[0] || isjoiningPlayer[1] || isjoiningPlayer[2] || isjoiningPlayer[3])
    {
        for (const auto& i : players)
        {
            i->update(this, stage);

            //��d�͈�for�ɂ��ē����蔻����`�F�b�N
            for (const auto& j : players)
            {
                //���̏��������Ȃ�������o�O��̂Œ���
                if (i != j)
                {
                    //�m�b�N�o�b�N�ʁi�����ʁj�����߂�
                    i->decideKnockBackWithChara(j);

                    //���̓����蔻��
                    i->collisionWindWithChara(j, stage);
                }
            }

            //�T���h�o�b�O�X�V
            for (const auto& s : sandBag)
            {
                s->update(this, stage);

                //�T���h�o�b�O�Ƃ̓����蔻��
                i->decideKnockBackWithChara(s);
                i->collisionWindWithChara(s, stage);
            }

            //���肪�I�������Ƀm�b�N�o�b�N�i�����j������
            i->knockBackNow();
            for (const auto& s : sandBag)
            {
                s->knockBackNow();
            }

            //�v���C���[�`��
            i->draw();

            //ui
            playUI->update(i, i->GetcontrolerNumber_());
        }

        //�G�t�F�N�g�}�l�[�W���[
        auto playerIt = players.begin();
        for (const auto& e : effectManager)
        {
            e->update(*playerIt);
            ++playerIt;
        }

        UpdateEffekseer3D();
        DrawEffekseer3D();

        //�X�e�[�W�Ƃ̓����蔻��
        stage->collisionWithPlayer(players);
        stage->collisionWithPlayer(sandBag);

        //�T���h�o�b�O�`��
        for (const auto& s : sandBag)
        {
            s->draw();
        }
    }
    
    if (sceneManager->proceedPlay())
    {
        PlaySoundMem(decideSound_, DX_PLAYTYPE_BACK, TRUE);

        //�v���C��ʂ֍s���Ƃ���cpu���Q��
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

    //�R���X�g���N�^�������t���[���̍Ō�ɂ��̃t���[�����I��邱�Ƃ�ʒm����
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
/// �v���C���[�`��
/// </summary>
void Routine::play()
{
    //�J�����X�V
    camera->update();

    //�J�E���g�_�E�����I����Ă���
    if (!playGraph->GetonCountDown_())
    {
        //���ā[����������
        stage->updateGimmick(players);
        stage->update();

        //�v���C���[�X�V
        for (const auto& i : players)
        {
            i->update(this, stage);

            //��d�͈�for�ɂ��ē����蔻����`�F�b�N
            for (const auto& j : players)
            {
                //���̏��������Ȃ�������o�O��̂Œ���
                if (i != j)
                {
                    //�m�b�N�o�b�N�ʁi�����ʁj�����߂�
                    i->decideKnockBackWithChara(j);

                    //���̓����蔻��
                    i->collisionWindWithChara(j, stage);
                }
            }

            //���肪�I�������Ƀm�b�N�o�b�N�i�����j������
            i->knockBackNow();

            //�f�o�b�O�p
            //DrawSphere3D(i->GetcollisionCenterPosition_(), collision_radius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
            //DrawSphere3D(i->Getposition_(), collision_radius_stage, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
            //DrawSphere3D(i->GetwindPosition_(), collision_radius_wind, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
            //DrawSphere3D(stage_center, collision_radius_wind, 32, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);
            //DrawFormatString(100, 100 * collisionCount, GetColor(255, 0, 0), "player%d, x:%f, y:%f, z:%f", collisionCount, i->Getposition_().x, i->Getposition_().y, i->Getposition_().z);
            //DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d, moveVector(%f, %f, %f)", collisionCount, i->GetmoveVector_().x, i->GetmoveVector_().y, i->GetmoveVector_().z);
        }
    }

    //�v���C���[�̍��W�Z�b�g
    for (const auto& i : players)
    {
        i->setPosition();
    }

    //�G�t�F�N�g�}�l�[�W���[
    auto playerIt = players.begin();
    for (const auto& e : effectManager)
    {
        e->update(*playerIt);
        ++playerIt;
    }
    UpdateEffekseer3D();

    //�`��
    stage->draw();
    for (const auto& i : players)
    {
        //�v���C���[�`��
        i->draw();

        //ui
        playUI->update(i, i->GetcontrolerNumber_());
    }
    DrawEffekseer3D();

    //�v���C�摜�`��
    playGraph->update();

    //���Ҕ���
    judgeWinner();
}

/// <summary>
/// ���U���g���[�`��
/// </summary>
void Routine::result()
{
    //�o�[�`�����J�����X�V
    camera->virtualUpdate(cameraUpPosition_);

    stage->draw();
    for (const auto& p : players)
    {
        p->draw();
    }

    //�Y�[���A�b�v���I���
    if (camera->GetwasZoomUP_())
    {
        //�����ʉ��𗬂�
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
/// �ϐ������Z�b�g
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
/// �v���C���[�Q��
/// </summary>
void Routine::joinPlayer()
{
    //�R���g���[���[(D)�p�\���̕ϐ�
    DINPUT_JOYSTATE input1;
    DINPUT_JOYSTATE input2;
    DINPUT_JOYSTATE input3;
    DINPUT_JOYSTATE input4;

    //�R���g���[���[���g����悤�ɂ���
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input1);
    GetJoypadDirectInputState(DX_INPUT_PAD2, &input2);
    GetJoypadDirectInputState(DX_INPUT_PAD3, &input3);
    GetJoypadDirectInputState(DX_INPUT_PAD4, &input4);
    //�v���C���[�̓R���g���[����A�{�^������������Q���ł���
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
/// cpu�Q��
/// </summary>
void Routine::joinCPU()
{
    for (auto i = 0; i < max_player_number; i++)
    {
        //�v���C���[���Q�����ĂȂ����
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
    //��������
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