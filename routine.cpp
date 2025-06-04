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
    shared_ptr<Stage>stage = make_shared<Stage>();

    //�Q�[�����[�v�Ăяo��
    gameRoop(sceneManager,player,camera,stage);

    //�f���[�g
    sceneManager    = nullptr;
    camera          = nullptr;
    player          = nullptr;
}

/// <summary>
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera, shared_ptr<Stage> stage)
{
    while (gameRoopSetting)
    {
        //��ʂɕ`���ꂽ��������(�Q�[�����[�v�̍ŏ��ɌĂ�)
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

        // ����ʂ̓��e��\��ʂɔ��f(�Q�[�����[�v�̍Ō�ɌĂ�)
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