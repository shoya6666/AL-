#include <algorithm>
#include "CameraController.h"
#include "Math.h"
#include "Player.h"
using namespace KamataEngine;
using namespace MathUtility;

void CameraController::Initialize() {

	camera_.Initialize(); 
}

void CameraController::Update() {
	// 追跡対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追跡対象とオフセットからカメラの座標を計算
	const Vector3& targetVelocity = target_->GetVelocity();
	targetPosition_ = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;
	
	//座標補間によるゆったり追跡
	camera_.translation_.x = Lerp(camera_.translation_.x, targetPosition_.x, kInterpolationRate);

	// 追跡対象が画面外に出ないように補正
	camera_.translation_.x = max(camera_.translation_.x, camera_.translation_.x + targetMargin.left);
	camera_.translation_.x = min(camera_.translation_.x, camera_.translation_.x + targetMargin.right);
	camera_.translation_.y = max(camera_.translation_.y, camera_.translation_.y + targetMargin.bottom);
	camera_.translation_.y = min(camera_.translation_.y, camera_.translation_.y + targetMargin.top);

	//移動範囲制限
	camera_.translation_.x = max(camera_.translation_.x, movableArea_.left);
	camera_.translation_.x = min(camera_.translation_.x, movableArea_.right);
	camera_.translation_.y = max(camera_.translation_.y, movableArea_.bottom);
	camera_.translation_.y = min(camera_.translation_.y, movableArea_.top);

	// 行列を更新
	camera_.UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットからカメラの座標を計算
	camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}