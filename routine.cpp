#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"camera.h"
#include"player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Routine::Routine()
{
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
    //�C���X�^���X��
    shared_ptr<SceneManager>sceneManager = make_shared<SceneManager>();
    shared_ptr<Camera>camera = make_shared<Camera>();
    shared_ptr<Player>player = make_shared<Player>();

    //�Q�[�����[�v�Ăяo��
    gameRoop(sceneManager,player,camera);

    //�f���[�g
    sceneManager    = nullptr;
    camera          = nullptr;
    player          = nullptr;
}

/// <summary>
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera)
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

            break;

        case PLAY:
            play(player);
            break;

        case RESULT:
            result();
            break;

        }

        // ����ʂ̓��e��\��ʂɔ��f(�Q�[�����[�v�̍Ō�ɌĂ�)
        ScreenFlip();
    }
}

void Routine::title()
{

}

void Routine::stanby()
{

}

void Routine::play(shared_ptr<Player>player)
{
    player->update();
}

void Routine::result()
{

}