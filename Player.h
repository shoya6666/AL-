#include "KamataEngine.h"
#pragma once
class MapChipField;
class Player {

public:
	enum class LRDirection {
		kRight,
		kLeft,
	};

	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	struct CoolisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	KamataEngine::Vector3 velocity_ = {};

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	void AnimateTurn();

	void CheckMapCollision(CoolisionMapInfo& info);

	void CheckMapCollisionUp(CoolisionMapInfo& info);

	void CheckMapMove(const CoolisionMapInfo& info);

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

private:
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 接地状態フラグ
	bool onGround_ = true;

	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.8f;
	static inline const float kLimitRunSpeed = 0.3f;
	// 旋回時間<秒>
	static inline const float kTimeTern = 0.3f;
	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.3f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.3f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.5f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// 隙間
	static inline const float kBlank = 0.1f;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	MapChipField* mapChipField_ = nullptr;

	LRDirection lrDirection_ = LRDirection::kRight;
};
