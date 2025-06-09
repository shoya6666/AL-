#include "Skydome.h"
using namespace KamataEngine;
void Skydome::Initialize(Model* model,Camera* camera) {

	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	camera_ = camera;
}
Skydome::~Skydome() {}

void Skydome::Update() { worldTransform_.TransferMatrix(); }

void Skydome::Draw() { model_->Draw(worldTransform_, *camera_); }
