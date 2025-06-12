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
    gameRoop(/*sceneManager,player,camera,stage*/);

    //�f���[�g
    sceneManager    = nullptr;
    camera          = nullptr;
    player.clear();
}

/// <summary>
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop(/*shared_ptr<SceneManager> sceneManager, shared_ptr<Player>player, shared_ptr<Camera>camera, shared_ptr<Stage> stage*/)
{
    while (gameRoopSetting)
    {
        //��ʂɕ`���ꂽ��������(�Q�[�����[�v�̍ŏ��ɌĂ�)
        ClearDrawScreen();

        switch (sceneManager->GetsceneType_())
        {
        case TITLE:
            title(/*sceneManager*/);
            break;

        case STANDBY:
            stanby(/*sceneManager*/);
            break;

        case PLAY:
            play(/*player, sceneManager*/);
            break;

        case RESULT:
            result(/*sceneManager*/);
            break;

        }

        SetFPS();

        // ����ʂ̓��e��\��ʂɔ��f(�Q�[�����[�v�̍Ō�ɌĂ�)
        ScreenFlip();
    }
}

void Routine::title(/*shared_ptr<SceneManager> sceneManager*/)
{

}

void Routine::stanby(/*shared_ptr<SceneManager> sceneManager*/)
{
    
}

void Routine::play(/*shared_ptr<Player>player, shared_ptr<SceneManager> sceneManager*/)
{
    stage->update(player);

    for (const auto& i:player)
    {
        i->update();
    }
}

void Routine::result(/*shared_ptr<SceneManager> sceneManager*/)
{

}