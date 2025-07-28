#pragma once
#include "KamataEngine.h"
#include <numbers>

class Enemy {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

	//
	float walkTime_ = 0.0f;

	static inline const float kWalkSpeed = 0.1f;
	//最初の角度
	static inline const float kWalkMotionAngleStart = static_cast<float>(30.0f * std::numbers::pi / 180.0f);
	//最後の角度
	static inline const float kWalkMotionAngleEnd = static_cast<float>(-30.0f * std::numbers::pi / 180.0f);
	
	//アニメーション周期となる時間
	static inline const float kWalkMotionTime = 1.0f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	KamataEngine::Vector3 velocity_ = {};
	
	Vector3 GetWorldPosition();

	AABB GetAABB();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;
};

