#include "StorageHeartListener.hpp"
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src/common/world/actor/Actor.hpp>

std::vector<BlockPos> getPosAroundBlock(BlockPos pos) {
	return {
		BlockPos(pos.x + 1, pos.y, pos.z),
		BlockPos(pos.x - 1, pos.y, pos.z),
		BlockPos(pos.x, pos.y + 1, pos.z),
		BlockPos(pos.x, pos.y - 1, pos.z),
		BlockPos(pos.x, pos.y, pos.z + 1),
		BlockPos(pos.x, pos.y, pos.z - 1)
	};
}

void updateStorageUnits(BlockSource& src, const BlockPos& rootPos, std::shared_ptr<StorageInfo> info) {
	info->storageUnits.clear();

	std::vector<BlockPos> queue = getPosAroundBlock(rootPos);

	std::unordered_set<BlockPos> visited = {};

	while (!queue.empty()) {
		if (info->storageUnits.size() > info->maxStorages) return;

		auto& node = queue.back();
		queue.pop_back();

		auto legacy = src.getBlock(node).mLegacyBlock;
		if (!visited.contains(node) && legacy->mNameInfo.mFullName.getString() == "mstorage:storage_unit") {
			visited.insert(node);
			auto around = getPosAroundBlock(node);
			queue.insert(queue.end(), around.begin(), around.end());
			Log::Info("good storage");
			info->storageUnits.insert(reinterpret_cast<StorageUnit*>(legacy.get()));
		}
	}
};

void StorageHeartListener::onBlockChanged(
	BlockSource& src,
	const BlockPos& pos,
	uint32_t layer,
	const Block& block,
	const Block& oldBlock,
	int updateFlags,
	const ActorBlockSyncMessage* syncMsg,
	BlockChangedEventTarget eventTarget,
	Actor* blockChangeSource
) {
	if (oldBlock.mLegacyBlock->mNameInfo.mFullName.getString() == "mstorage:storage_unit" || block.mLegacyBlock->mNameInfo.mFullName.getString() == "mstorage:storage_unit") {
		updateStorageUnits(src, ownerPos, storageInfo);
	}
}