#pragma once
#include <unordered_set>
#include <mc/src/common/world/level/BlockPos.hpp>

struct StorageInfo {
	int maxStorages = 32;
	int storageCapacity = 0;
	std::unordered_set<BlockPos> storageUnits;
	bool hasCraftingInterface = false;
};

enum class StorageCoreError {
	NONE = 0,
	CONNECTION_ERROR = 1,
	STORAGE_LIMIT_ERROR = 2,
};