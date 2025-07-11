#include "KamataEngine.h"
#pragma once
class Player;
class CameraController {
public:
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0;
	};

	// 初期化
	void Initialize();

	// 更新
	void Update();

	void setTarget(Player* target) { target_ = target; }

	void Reset();

	const KamataEngine::Camera& GetViewProjection() const { return camera_; }

	Rect movableArea_ = {0, 100, 0, 100};

	void SetMovableArea(Rect area) {
		movableArea_ = area;
	}

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera camera_;

	Player* target_ = nullptr;

	KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f};

	KamataEngine::Vector3 targetPosition_;

	static inline const float kInterpolationRate = 1.0f;
	static inline const float kVelocityBias = 5.0f;
	static inline const Rect targetMargin = {-9.0f, 9.0f, -5.0f, 5.0f};
};
