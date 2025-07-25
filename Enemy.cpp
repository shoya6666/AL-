#include "Enemy.h"
#include "MyMath.h"


void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position)
{
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
}

void Enemy::Update() {
	// アフィン変換
	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }
