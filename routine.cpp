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
/// �R���X�g���N�^
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
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
Routine::~Routine()
{
    DeleteSoundMem(bgm_);
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

        //�������Z�b�g
        if (CheckHitKey(KEY_INPUT_R) == true)
        {
            allReset();
        }

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
    sceneManager->proceedStandby();
}

/// <summary>
/// �X�^���o�C���[�`��
/// </summary>
void Routine::stanby()
{
    joinPlayer();

    if (sceneManager->proceedPlay())
    {
        //�v���C��ʂ֍s���Ƃ���cpu���Q��
        joinCPU();

        PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, TRUE);
    }

    standbyUI->update(isjoiningPlayer, max_player_number);
}

/// <summary>
/// �v���C���[�`��
/// </summary>
void Routine::play()
{
    //���ā[����������
    stage->update(players);

    //������Ƃ������Ă邩�̃J�E���g
    short collisionCount = 0;
    for (const auto& i:players)
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
        ++collisionCount;
        //DrawFormatString(100, 100 * collisionCount, GetColor(255, 0, 0), "player%d, x:%f, y:%f, z:%f", collisionCount, i->Getposition_().x, i->Getposition_().y, i->Getposition_().z);
        //DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d, moveVector(%f, %f, %f)", collisionCount, i->GetmoveVector_().x, i->GetmoveVector_().y, i->GetmoveVector_().z);
        DrawFormatString(100, 100 * collisionCount + 15 * collisionCount, GetColor(255, 0, 0), "player%d,HP:%d", collisionCount, i->Gethp_());

        //�v���C���[�`��
        i->draw();
    }

    //�G�t�F�N�g�}�l�[�W���[
    auto playerIt = players.begin();//�v���C���[�C�e���[�^�[
    for (const auto& e : effectManager)
    {
        e->update(*playerIt);
        ++playerIt;
    }

    DrawEffekseer3D();
    UpdateEffekseer3D();

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
    }
}

/// <summary>
/// ���U���g���[�`��
/// </summary>
void Routine::result()
{
    if (sceneManager->proceedTitle())
    {
        allReset();
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