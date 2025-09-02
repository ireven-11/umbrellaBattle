#include"EffekseerForDXLib.h"
#include"DxLib.h"
#include"setting.h"

/// <summary>
/// dxlib�ݒ�
/// </summary>
void DxlibSetting()
{
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//�E�B���h�E�̃T�C�Y�ƃJ���[���[�h�����߂�
    ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɂ���
    SetWindowStyleMode(7);						//�ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX

	if (DxLib_Init() == -1)return;

    // �T�C�Y�ύX���\�ɂ���
    SetWindowSizeChangeEnableFlag(TRUE, FALSE);

    // �E�C���h�E�T�C�Y�̓Q�[����ʂƈ�v������
    SetWindowSize(screenWIDTH, screenHEIGHT);

    SetMainWindowText("gamename");              //�E�B���h�E�i�����Ƃ���j�ɃQ�[����������
    SetDrawScreen(DX_SCREEN_BACK);		        //�w�i���Z�b�g����
}

/// <summary>
/// fps�ݒ�
/// </summary>
void SetFPS()
{
    //wait�̕����̐��l�𑝂₷�قǂ��������������Ă���
    const int wait = 30;
    int term;
    static int t = 0;
    term = GetNowCount() - t;
    if (wait - term > 0)
        Sleep(wait - term);
    t = GetNowCount();
}

//�G�t�F�N�V�A�ݒ�
int setEffekseer()
{
	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(max_effekseer_particles) == -1)
	{
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	
	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	return 0;
}