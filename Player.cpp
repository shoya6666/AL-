#include "Player.h"
#include "cassert"
#include<numbers>
#include "MyMath.h"

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

	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
	
		//左右加速
		KamataEngine::Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x -= kAcceleration;
		}
		//加速/減速
		velocity_ += acceleration;

	}

	//移動
	worldTransform_.translation_ += velocity_;

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_, textureHandle_); }
