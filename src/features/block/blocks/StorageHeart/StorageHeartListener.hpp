#pragma once
#include <mc/src/common/world/level/BlockSourceListener.hpp>
#include <mc/src/common/world/level/BlockSource.hpp>
#include "../StorageUnit/StorageUnit.hpp"

struct StorageInfo {
	int maxStorages = 32;
	int maxStorageSize = 0;
	std::unordered_set<StorageUnit*> storageUnits = {};
};

class StorageHeartListener : public BlockSourceListener {
public:
	const BlockPos& ownerPos;
	std::shared_ptr<StorageInfo> storageInfo;

public:
	StorageHeartListener(const BlockPos& pos, std::shared_ptr<StorageInfo> info) : BlockSourceListener(), ownerPos(pos), storageInfo(info) {};
	virtual void onBlockChanged(BlockSource& source, const BlockPos& pos, uint32_t layer, const Block& block, const Block& oldBlock, int updateFlags, const ActorBlockSyncMessage* syncMsg, BlockChangedEventTarget eventTarget, Actor* blockChangeSource) override;
};

void updateStorageUnits(BlockSource& src, const BlockPos& rootPos, std::shared_ptr<StorageInfo> info);