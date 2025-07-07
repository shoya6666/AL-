#include "KamataEngine.h"
#pragma once
class Player {

public:

	

	KamataEngine::Vector3 velocity_ = {};

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	

private:

	enum class LRDirection {
		kRight,
		kLeft,
	};

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	//接地状態フラグ
	bool onGround_ = true;

	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.8f;
	static inline const float kLimitRunSpeed = 0.3f;
	//旋回時間<秒>
	static inline const float kTimeTern  = 0.3f;
	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.3f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.3f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.3f;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	LRDirection lrDirection_ = LRDirection::kRight;
};
