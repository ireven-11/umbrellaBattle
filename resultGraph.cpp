#include"DxLib.h"
#include"resultGraph.h"

ResultGraph::ResultGraph()
{
    movieHandle_    = LoadGraph("movie/confetti02.mp4");
    screenHandle_   = MakeScreen(1920, 1080, TRUE);
}

ResultGraph::~ResultGraph()
{
}

/// <summary>
/// ����w�i���ߕ`��֐�
/// </summary>
/// <param name="movieHandle">����n���h��</param>
/// <param name="screenHandle">�X�N���[���n���h����MakeScreen�Ńn���h��������Ă��̎��ɑ�O������TRUE�ɂ���K�v������</param>
/// <param name="isLoop">��������[�v���邩</param>
/// <param name="screenType">�ŏI�I�ɕ`�悷��Ƃ��̃X�N���[���n���h��</param>
void PlayTransparentMovie(int movieHandle, int screenHandle, bool isLoop = true, int screenType = DX_SCREEN_BACK)
{
    //�X�N���[���n���h���ɓ����`�悷��
    SetDrawScreen(screenHandle);
    PlayMovieToGraph(movieHandle);
    DrawGraph(0, 0, movieHandle, TRUE);

    //��������[�v������
    if (!GetMovieStateToGraph(movieHandle) && isLoop)
    {
        SeekMovieToGraph(movieHandle, 0);
    }

    //���̃X�N���[���n���h���ɖ߂�
    SetDrawScreen(screenType);

    //�X�N���[���n���h�����摜�Ƃ��ē��߂��Ă���`��
    GraphFilter(screenHandle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 128, TRUE, GetColor(0, 255, 0), 0);
    DrawGraph(0, 0, screenHandle, TRUE);
}

void ResultGraph::update()
{
    PlayTransparentMovie(movieHandle_, screenHandle_);
}