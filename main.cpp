#include"DxLib.h"
#include"setting.h" 
#include"EffekseerForDXlib.h"
#include"routine.h"

int WINAPI WinMain(winmainSetting)
{
    //��ʐݒ�
    ScreenSetting();

    //dxlib��������
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    //�G�t�F�N�V�A�ݒ�
    setEffekseer();

    //���[�`�����C���X�^���X�����ăQ�[���J�n���ďI�������f���[�g
    std::shared_ptr<Routine>routine = std::make_shared<Routine>();
    routine->game();
    routine = nullptr;

    //Effekseer���I������B
    Effkseer_End();

    DxLib_End();
    return 0;
}