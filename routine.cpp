#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"
#include"stage.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Routine::Routine()
{
    player.emplace_back(make_shared<Player>());
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
    //�R���g���[���[���g����悤�ɂ���
    /*GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
    GetJoypadDirectInputState(DX_INPUT_PAD2, &input);
    GetJoypadDirectInputState(DX_INPUT_PAD3, &input);
    GetJoypadDirectInputState(DX_INPUT_PAD4, &input);
    if (input.Buttons[1] > 0)
    {
        player.emplace_back(make_shared<Player>());
    }*/
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