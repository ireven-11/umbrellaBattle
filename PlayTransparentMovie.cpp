#include"PlayTransparentMovie.h"

/// <summary>
/// 背景透過動画再生関数
/// </summary>
/// <param name="movieHandle">動画ハンドル</param>
/// <param name="screenHandle">スクリーンハンドル※MakeScreenでハンドルを作ってその時に第三引数をTRUEにする必要がある</param>
/// <param name="movieWidht">動画幅</param>
/// <param name="movieHeght">動画高さ</param>
/// <param name="isLoop">動画をループするか</param>
/// <param name="screenType">最終的に描画するとこのスクリーンハンドル</param>
void PlayTransparentMovie(int movieHandle, int screenHandle, int movieWidht, int movieHeight, VECTOR position, bool isLoop, int screenType)
{
    //スクリーンハンドルに動画を描画する
    SetDrawScreen(screenHandle);
    PlayMovieToGraph(movieHandle);
    DrawExtendGraph(position.x, position.y, position.x + movieWidht, position.y + movieHeight, movieHandle, TRUE);

    //動画をループさせる
    if (!GetMovieStateToGraph(movieHandle) && isLoop)
    {
        SeekMovieToGraph(movieHandle, 0);
    }

    //元のスクリーンハンドルに戻す
    SetDrawScreen(screenType);

    //スクリーンハンドルを画像として透過してから描画
    GraphFilter(screenHandle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 128, TRUE, GetColor(0, 255, 0), 0);
    DrawExtendGraph(position.x, position.y, position.x + movieWidht, position.y + movieHeight, screenHandle, TRUE);
}