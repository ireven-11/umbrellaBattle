#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"
#include"stage.h"
#include"standbyUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Routine::Routine()
{
    reset();
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
Routine::~Routine()
{
}

/// <summary>
/// �Q�[��
/// </summary>
void Routine::game()
{
    //�Q�[�����[�v�Ăяo��
    gameRoop();

    //�f���[�g
    sceneManager    = nullptr;
    camera          = nullptr;
    player.clear();
    stage           = nullptr;
    standbyUI       = nullptr;
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

}

/// <summary>
/// �X�^���o�C���[�`��
/// </summary>
void Routine::stanby()
{
    joinPlayer();

    sceneManager->proceedPlay();

    standbyUI->update(isjoiningPlayer, max_player_number);
}

/// <summary>
/// �v���C���[�`��
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
/// ���U���g���[�`��
/// </summary>
void Routine::result()
{

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