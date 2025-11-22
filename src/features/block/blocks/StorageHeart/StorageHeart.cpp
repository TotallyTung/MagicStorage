#include "StorageHeart.hpp"
#include <mc/src/common/world/level/BlockSource.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src-client/common/client/gui/gui/GuiData.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src/common/world/actor/Actor.hpp>
#include <mc/src-deps/core/math/Math.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp>
#include <mc/src-client/common/client/gui/screens/SceneCreationUtils.hpp>
#include <mc/src-client/common/client/gui/screens/SceneFactory.hpp>
#include <mc/src-client/common/client/gui/screens/UIScene.hpp>
#include <features/ui/StorageUI/screen/StorageScreenController.hpp>

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
		if (blockName == "magic_storage:storage_unit") {
			info->storageUnits.insert(node);
			for (auto& i : getPosAroundBlock(node)) {
				if (!visited.contains(i)) queue.push_back(i);
			}
		}
		else if (blockName == "magic_storage:crafting_interface") info->hasCraftingInterface = true;
		else if (blockName == "magic_storage:storage_heart") return { false, StorageCoreError::CONNECTION_ERROR };
		else if (info->storageUnits.size() > info->maxStorages) return { false, StorageCoreError::STORAGE_LIMIT_ERROR };
	}
	return { true, StorageCoreError::NONE };
};

bool StorageHeart::use(Player& player, const BlockPos& pos, Facing::Name face) const {
	auto result = updateStorageUnits(player.getDimensionBlockSource(), pos, storageInfo);
	if (player.isClientSide()) {
		auto& client = *Amethyst::GetClientCtx().mClientInstance;
		auto& game = *client.mMinecraftGame;
		auto guiData = client.mGuiData.get();
		if (!result.first) {
			guiData->displayLocalizedMessage(std::format("§g{} [{}]", getStorageErrorMessage(result.second), magic_enum::enum_name(result.second)));
		}
		else {
			guiData->displayLocalizedMessage(std::format("Connected storages: {} | Crafting Interface: {}", storageInfo->storageUnits.size(), storageInfo->hasCraftingInterface));
			auto& factory = *client.mSceneFactory;
			auto model = SceneCreationUtils::_createModel<ClientInstanceScreenModel>(
				factory,
				game,
				client,
				factory.mAdvancedGraphicOptions
			);
			auto controller = std::make_shared<StorageScreenController>(model, this->storageInfo);
			auto scene = factory.createUIScene(game, client, "magic_storage.storage_screen", controller);
			auto screen = factory._createScreen(scene);
			factory.getCurrentSceneStack()->pushScreen(screen, false);
		}
	}
	return true;
};