#include"DxLib.h"
#include"setting.h"

/// <summary>
/// �X�N���[���ݒ�
/// </summary>
void ScreenSetting()
{
    ChangeWindowMode(TRUE);				   //�E�B���h�E���[�h�ɂ���
    SetWindowStyleMode(7);				   //�ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX

    // �T�C�Y�ύX���\�ɂ���
    SetWindowSizeChangeEnableFlag(TRUE, FALSE);

    // �E�C���h�E�T�C�Y�̓Q�[����ʂƈ�v������
    SetWindowSize(screenWIDTH, screenHEIGHT);

    SetMainWindowText("gamename");              //�E�B���h�E�i�����Ƃ���j�ɃQ�[����������
    SetDrawScreen(DX_SCREEN_BACK);		        //�w�i���Z�b�g����
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//�E�B���h�E�̃T�C�Y�ƃJ���[���[�h�����߂�
}

/// <summary>
/// fps�ݒ�
/// </summary>
void SetFPS()
{
    const int wait = 20;
    int term;
    static int t = 0;
    term = GetNowCount() - t;
    //�P�U�̕����̐��l�𑝂₷�قǂ��������������Ă���
    if (wait - term > 0)
        Sleep(wait - term);
    t = GetNowCount();
}