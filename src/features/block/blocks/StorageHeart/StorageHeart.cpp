#include "StorageHeart.hpp"
#include <mc/src/common/world/level/BlockSource.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src-client/common/client/gui/gui/GuiData.hpp>
#include <amethyst/runtime/ModContext.hpp>

bool StorageHeart::use(Player& player, const BlockPos& pos, Facing::Name face) const {
	updateStorageUnits(player.getDimensionBlockSource(), pos, storageInfo);
	if (player.isClientSide()) {
		auto client = Amethyst::GetClientCtx().mClientInstance;
		client->mGuiData->displayLocalizedMessage(std::format("Connected storages: {}", storageInfo->storageUnits.size()));
	}
	return true;
};

void StorageHeart::onPlace(BlockSource& src, const BlockPos& pos) const {
	updateStorageUnits(src, pos, storageInfo);
	listener = std::make_shared<StorageHeartListener>(pos, storageInfo);
	src.addListener(*listener.get());
};

void StorageHeart::onRemove(BlockSource& src, const BlockPos& pos) const {
	if (listener) src.removeListener(*listener.get());
};