#include"PlayTransparentMovie.h"

/// <summary>
/// �w�i���ߓ���Đ��֐�
/// </summary>
/// <param name="movieHandle">����n���h��</param>
/// <param name="screenHandle">�X�N���[���n���h����MakeScreen�Ńn���h��������Ă��̎��ɑ�O������TRUE�ɂ���K�v������</param>
/// <param name="movieWidht">���敝</param>
/// <param name="movieHeght">���捂��</param>
/// <param name="isLoop">��������[�v���邩</param>
/// <param name="screenType">�ŏI�I�ɕ`�悷��Ƃ��̃X�N���[���n���h��</param>
void PlayTransparentMovie(int movieHandle, int screenHandle, int movieWidht, int movieHeight, VECTOR position, bool isLoop, int screenType)
{
    //�X�N���[���n���h���ɓ����`�悷��
    SetDrawScreen(screenHandle);
    PlayMovieToGraph(movieHandle);
    DrawExtendGraph(position.x, position.y, position.x + movieWidht, position.y + movieHeight, movieHandle, TRUE);

    //��������[�v������
    if (!GetMovieStateToGraph(movieHandle) && isLoop)
    {
        SeekMovieToGraph(movieHandle, 0);
    }

    //���̃X�N���[���n���h���ɖ߂�
    SetDrawScreen(screenType);

    //�X�N���[���n���h�����摜�Ƃ��ē��߂��Ă���`��
    GraphFilter(screenHandle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 128, TRUE, GetColor(0, 255, 0), 0);
    DrawExtendGraph(position.x, position.y, position.x + movieWidht, position.y + movieHeight, screenHandle, TRUE);
}