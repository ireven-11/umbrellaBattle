#include"DxLib.h"
#include <math.h>
#include"FPS.h"

FPS::FPS()
{
    startTime_ = GetNowCount();
    count_ = 0;
    currentFPS_ = 0;
}

FPS::~FPS()
{
}

void FPS::init()
{
    startTime_ = GetNowCount();
    count_ = 0;
    currentFPS_ = 0;
}

bool FPS::update()
{
    if (count_ == 0)
    { //1フレーム目なら時刻を記憶
        startTime_ = GetNowCount();
    }
    if (count_ == n)
    { //60フレーム目なら平均を計算する
        int t = GetNowCount();
        currentFPS_ = 1000.f / ((t - startTime_) / (float)n);
        count_ = 0;
        startTime_ = t;
    }
    count_++;
    return true;
}

void FPS::draw()
{
    DrawFormatString(drawingPosition.x, drawingPosition.y, GetColor(255, 255, 255), "FPS:%.1f", GetFPS());
}

void FPS::wait()
{
    int tookTime = GetNowCount() - startTime_;      //かかった時間
    int waitTime = count_ * 1000 / fps - tookTime;  //待つべき時間
    if (waitTime > 0)
    {
        Sleep(waitTime);  //待機
    }
}