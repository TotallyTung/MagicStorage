#include "StorageHeart.hpp"
#include <mc/src/common/world/level/BlockSource.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src-client/common/client/gui/gui/GuiData.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src/common/world/actor/Actor.hpp>
#include <mc/src-deps/core/math/Math.hpp>

static inline std::deque<BlockPos> getPosAroundBlock(BlockPos pos) {
	return {
		BlockPos(pos.x + 1, pos.y, pos.z),
		BlockPos(pos.x - 1, pos.y, pos.z),
		BlockPos(pos.x, pos.y + 1, pos.z),
		BlockPos(pos.x, pos.y - 1, pos.z),
		BlockPos(pos.x, pos.y, pos.z + 1),
		BlockPos(pos.x, pos.y, pos.z - 1)
	};
}

static constexpr std::string getStorageErrorMessage(StorageCoreError errorType) {
	switch (errorType) {
	case StorageCoreError::CONNECTION_ERROR:
		return "Multiple hearts are connected to the same storage system!";

	case StorageCoreError::STORAGE_LIMIT_ERROR:
		return "You have reached the maximum number of connected storage units (32).";

	default:
		return "";
	}
}

static std::pair<bool, StorageCoreError> updateStorageUnits(BlockSource& src, const BlockPos& rootPos, std::shared_ptr<StorageInfo> info) {
	info->storageUnits.clear();

	std::deque<BlockPos> queue = getPosAroundBlock(rootPos);

	std::unordered_set<BlockPos> visited;

	visited.insert(rootPos);
	visited.insert(queue.begin(), queue.end());

	while (!queue.empty()) {
		auto& node = queue.front();
		queue.pop_front();
		visited.insert(node);

		auto& block = src.getBlock(node);
		auto& blockName = block.mLegacyBlock->mNameInfo.mFullName.getString();
		if (blockName == "mstorage:storage_unit") {
			info->storageUnits.insert(node);
			for (auto& i : getPosAroundBlock(node)) {
				if (!visited.contains(i)) queue.push_back(i);
			}
		}
		else if (blockName == "mstorage:crafting_interface") info->hasCraftingInterface = true;
		else if (blockName == "mstorage:storage_heart") return { false, StorageCoreError::CONNECTION_ERROR };
		else if (info->storageUnits.size() > info->maxStorages) return { false, StorageCoreError::STORAGE_LIMIT_ERROR };
	}
	return { true, StorageCoreError::NONE };
};

bool StorageHeart::use(Player& player, const BlockPos& pos, Facing::Name face) const {
	auto result = updateStorageUnits(player.getDimensionBlockSource(), pos, storageInfo);
	if (player.isClientSide()) {
		auto client = Amethyst::GetClientCtx().mClientInstance;
		auto guiData = client->mGuiData.get();
		if (!result.first) {
			guiData->displayLocalizedMessage(std::format("§g{} [{}]", getStorageErrorMessage(result.second), magic_enum::enum_name(result.second)));
		}
		else {
			guiData->displayLocalizedMessage(std::format("Connected storages: {} | Crafting Interface: {}", storageInfo->storageUnits.size(), storageInfo->hasCraftingInterface));
		}
	}
	return true;
};