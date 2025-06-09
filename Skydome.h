#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
class Skydome {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);
	// デストラクタ
	~Skydome();
	// 更新
	void Update();
	// 描画
	void Draw();

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	

	KamataEngine::Camera* camera_ = nullptr;

};