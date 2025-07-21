#include "GameScene.h"
#include "KamataEngine.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"GC2C06タナカ_ショウヤ_AL3");

	// DirectXの機能取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーンの取得・初期化
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	//oiuytr
	/// aaaaaaaaaaaaaaaaaaaaaaaa
	// gggggg

	// sssssss
	

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// ゲームシーンの更新
		gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	gameScene = nullptr;

	KamataEngine::Finalize();

	return 0;
}