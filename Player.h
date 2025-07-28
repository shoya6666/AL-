#pragma once
#include "KamataEngine.h"

class MapChipField;

class Player {
public:
	enum class LRDirection {
		kRigth,
		kLeft,
	};

	// マップチップの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	KamataEngine::Vector3 velocity_ = {};

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	static inline const float kAccleration = 0.1f;

	static inline const float kAttenuation = 0.8f;

	static inline const float kLimitRunSpeed = 0.3f;

	float turnFirstRotationY_ = 0.0f;

	float turnTimer_ = 0.3f;

	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.1f;

	static inline const float kLimitFallSpeed = 0.3f;

	static inline const float kJumpAcceLeration = 1.0f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	// 1移動入力
	void InputMove();

	// 2マップ衝突判定
	void CheckMapCollision(CollisionMapInfo& info);

	// マップ衝突判定(上)
	void CheckMapCollisionUp(CollisionMapInfo& info);

	// マップ衝突判定(下)
	void CheckMapCollisionDown(CollisionMapInfo& info);

	// マップ衝突判定(右)
	void CheckMapCollisionRight(CollisionMapInfo& info);

	// マップ衝突判定(左)
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	// 3判定結果を反映して移動させる
	void CheckMapMove(const CollisionMapInfo& info);

	// 4天井に接触している場合の処理
	void CheckMapCeiling(const CollisionMapInfo& info);

	// 5壁に接触している場合の処理
	void CheckMapWall(const CollisionMapInfo& info);

	// 6設置状態の切り替え
	void CheckMapLanding(const CollisionMapInfo& info);

	// 7旋回制御
	void AnimateTurn();

	// 指定された角の座標計算
	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	LRDirection lrDrirection_ = LRDirection::kRigth;

	static inline const float kBlank = 0.1f;

	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.5f;

	// 微小な数値
	static inline const float kGroundSearchHeight = 0.1f;

	// 壁の速度減速率
	static inline const float kAttenuationWall = 0.5f;

	Vector3 GetWorldPosition();

	AABB GetAABB();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;
};