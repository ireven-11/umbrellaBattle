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
/// 動画背景透過描画関数
/// </summary>
/// <param name="movieHandle">動画ハンドル</param>
/// <param name="screenHandle">スクリーンハンドル※MakeScreenでハンドルを作ってその時に第三引数をTRUEにする必要がある</param>
/// <param name="isLoop">動画をループするか</param>
/// <param name="screenType">最終的に描画するとこのスクリーンハンドル</param>
void PlayTransparentMovie(int movieHandle, int screenHandle, bool isLoop = true, int screenType = DX_SCREEN_BACK)
{
    //スクリーンハンドルに動画を描画する
    SetDrawScreen(screenHandle);
    PlayMovieToGraph(movieHandle);
    DrawGraph(0, 0, movieHandle, TRUE);

    //動画をループさせる
    if (!GetMovieStateToGraph(movieHandle) && isLoop)
    {
        SeekMovieToGraph(movieHandle, 0);
    }

    //元のスクリーンハンドルに戻す
    SetDrawScreen(screenType);

    //スクリーンハンドルを画像として透過してから描画
    GraphFilter(screenHandle, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 128, TRUE, GetColor(0, 255, 0), 0);
    DrawGraph(0, 0, screenHandle, TRUE);
}

void ResultGraph::update()
{
    PlayTransparentMovie(movieHandle_, screenHandle_);
}