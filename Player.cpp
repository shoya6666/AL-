#define NOMINMAX
#include "Player.h"
#include "MyMath.h"
#include"MapChipField.h"
#include "cassert"
#include <algorithm>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	camera_ = camera;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {

	InputMove();
	AnimateTurn();

	// 衝突情報を初期化
	CoolisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;
	
	// マップ衝突チェック
	CheckMapCollision(collisionMapInfo);

	CheckMapMove(collisionMapInfo);
	// 着地フラグ
	bool landing = false;

	// 地面との当たり判定
	// 降下中?
	if (velocity_.y < 0) {
		// Y座標が地面以下になったら着地
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}
	if (landing) {
		// めり込み
		worldTransform_.translation_.y = 1.0f;
		// 摩擦で横方向速度が減衰する
		velocity_.x *= (1.0f - kAttenuation);
		// 下方向速度をリセット
		velocity_.y = 0.0f;
		// 着地状態に移行
		onGround_ = true;
	}



	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}
void Player::InputMove() {

	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移動
			onGround_ = false;
		}

		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			// 左右加速
			KamataEngine::Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右移動
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中に急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに開始を設定する
					turnTimer_ = kTimeTern;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中に急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに開始を設定する
					turnTimer_ = kTimeTern;
				}
			}

			// 加速/減速
			velocity_ += acceleration;
			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			velocity_.x *= (1.0f - kAttenuation);
		}

		if (Input::GetInstance()->PushKey(DIK_UP)) {
			velocity_ += Vector3(0, kJumpAcceleration, 0);
		}
	} else {
		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
}

void Player::AnimateTurn() {

	if (turnTimer_ > 0.0f) {

		turnTimer_ = 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度に取得
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTern);
	}
}

void Player::CheckMapCollision(CoolisionMapInfo& info) { 
	CheckMapCollisionUp(info);
	//CheckMapCollisionDown(info);
	// CheckMapCollisionRight(info);
	// CheckMapCollisionLeft(info);
}

void Player::CheckMapCollisionUp(CoolisionMapInfo& info) {
	
	//上昇あり？
	if (info.move.y <= 0) {
		return;
	}

	//移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	//真上のあたり判定を行う
	bool hit = false;
	//左上点の判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右上点の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {
		//
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + info.move + Vector3(0, +kHeight / 2.0f, 0));
		//めり込み先ブロックの範囲短形
		MapChipField::Rect rect = mapChipField_->GetRectVByIndex(indexSet.xIndex, indexSet.yIndex);
		info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));
		//天井にあった田ことを記録する
		info.ceiling = true;
	}

}

void Player::CheckMapMove(const CoolisionMapInfo& info) {

	worldTransform_.translation_ += info.move;

}

KamataEngine::Vector3 Player::CornerPosition(const KamataEngine::Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0},//RightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0},//LeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0},//RightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0},//LeftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }
