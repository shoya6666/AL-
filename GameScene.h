#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"
#include <vector>

class GameScene {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	~GameScene();

	void GenerateBlocks();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// カメラ
	KamataEngine::Camera camera_;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
	// ImGuiで値を入力する変数
	float inputFloat3[3] = {0, 0, 0};
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
	// 敵キャラ
	Enemy* enemy_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
	// 3Dモデルデータ
	KamataEngine::Model* modelBlock_ = nullptr;
	// デバッグカメラ友好
	bool isDebugCameraActive_ = false;
	// キー入力
	KamataEngine::Input* input_ = nullptr;
	Skydome* skydome_ = nullptr;
	// 3Dモデル
	KamataEngine::Model* modelSkydome_ = nullptr;
	//マップチップフィールド
	MapChipField* mapChipField_;
	//カメラコントローラー
	CameraController* cameraController_ = nullptr;
};