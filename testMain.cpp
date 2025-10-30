#include"DxLib.h"
#include"charaBase.h"
#include"routine.h"
#include"setting.h" 
#include"camera.h"
#include"player.h"
#include"stage.h""
#include"cpu.h"
#include"sandBag.h"
#include"ShadowMap.h"


int WINAPI WinMain(winmainSetting)
{
    //画面設定
    DxlibSetting();

    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetUseLighting(TRUE);
    SetUsePixelLighting(TRUE);

    std::shared_ptr<Routine>routine = std::make_shared<Routine>();
	std::shared_ptr<Camera>camera = std::make_shared<Camera>();
	std::shared_ptr<Stage>stage = std::make_shared<Stage>();
    std::shared_ptr<ShadowMap>shadowMap = std::make_shared<ShadowMap>();
    std::vector<std::shared_ptr<CharaBase>>players;

    shadowMap->addPlayerShadows(players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD1)));
    shadowMap->addStageShadows(stage);

    while (gameRoopSetting)
    {
        //カメラ更新
        camera->update();

        //すてーじこうしん
        stage->update();

        //プレイヤー更新
        for (const auto& i : players)
        {
            i->update(routine.get(), stage);
        }

        //シャドウマップに影を描画
        shadowMap->drawToShadowMap();

        //シャドウマップを設定
        shadowMap->setUse();

        //描画
        stage->draw();
        for (const auto& i : players)
        {
            //プレイヤー描画
            i->draw();
        }

        //シャドウマップを解除
        shadowMap->release();
    }

    DxLib_End();
    return 0;

	//DxlibSetting();

	//std::shared_ptr<Routine>routine = std::make_shared<Routine>();
	//std::shared_ptr<Camera>camera = std::make_shared<Camera>();
	//std::shared_ptr<Stage>stage = std::make_shared<Stage>();
	//std::shared_ptr<ShadowMap>shadowMap = std::make_shared<ShadowMap>();
	//std::vector<std::shared_ptr<CharaBase>>players;

	//shadowMap->addPlayerShadows(players.emplace_back(std::make_shared<Player>(DX_INPUT_PAD1)));
	//shadowMap->addStageShadows(stage);

	//int ShadowMapHandle;

	//// シャドウマップハンドルの作成
	//ShadowMapHandle = MakeShadowMap(1024, 1024);

	//// ライトの方向を設定
	//SetLightDirection(VGet(0.5f, -0.5f, 0.5f));

	//// シャドウマップが想定するライトの方向もセット
	//SetShadowMapLightDirection(ShadowMapHandle, VGet(0.5f, -0.5f, 0.5f));

	//// シャドウマップに描画する範囲を設定
	//SetShadowMapDrawArea(ShadowMapHandle, VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

	//// メインループ
	//while (gameRoopSetting)
	//{
 //       //カメラ更新
 //       camera->update();

 //       //すてーじこうしん
 //       stage->update();

 //       //プレイヤー更新
 //       for (const auto& i : players)
 //       {
 //           i->update(routine.get(), stage);
 //       }

	//	// シャドウマップへの描画の準備
	//	ShadowMap_DrawSetup(ShadowMapHandle);
 //       //描画
 //       stage->draw();
 //       for (const auto& i : players)
 //       {
 //           //プレイヤー描画
 //           i->draw();
 //       }
	//	// シャドウマップへの描画を終了
	//	ShadowMap_DrawEnd();

	//	// 描画に使用するシャドウマップを設定
	//	SetUseShadowMap(0, ShadowMapHandle);
 //       //描画
 //       stage->draw();
 //       for (const auto& i : players)
 //       {
 //           //プレイヤー描画
 //           i->draw();
 //       }
	//	// 描画に使用するシャドウマップの設定を解除
	//	SetUseShadowMap(0, -1);
	//}

	//// シャドウマップの削除
	//DeleteShadowMap(ShadowMapHandle);

	//// ＤＸライブラリの後始末
	//DxLib_End();

	//// ソフトの終了
	//return 0;
}