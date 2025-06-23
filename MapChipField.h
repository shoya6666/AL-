#pragma once
#include "KamataEngine.h"

enum class MapChipType {
	kBlank,
	kBlock,
};

class MapChipField {

public:
	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical() const { return kNumBlockVirtical; }
	uint32_t GetNumBlockHorizontal() const { return kNumBlockHorizontal; }

private:
	// 一ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの偶数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	struct MapChipData {
		std::vector<std::vector<MapChipType>> data;
	};

	MapChipData mapChipData_;

};
