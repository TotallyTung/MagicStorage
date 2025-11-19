#include "StorageManagerModel.hpp"
#include <mc/src/common/world/containers/models/InventoryContainerModel.hpp>
#include <mc/src/common/world/containers/models/PlayerUIContainerModel.hpp>
#include <mc/src/common/world/actor/player/Inventory.hpp>
#include <features/ui/StorageUI/container/model/StorageContainerModel.hpp>

StorageManagerModel::StorageManagerModel(ContainerID id, Player& player) : ContainerManagerModel(id, player) {
	auto& supplies = mPlayer.getSupplies();
	auto containerSize = supplies.mInventory->getContainerSize();
	//_addContainer(std::make_shared<StorageContainerModel>(ContainerEnumName::ContainerItems, 104, mPlayer));
	_addContainer(std::make_shared<PlayerUIContainerModel>(ContainerEnumName::CursorContainer, mPlayer));
	_addContainer(std::make_shared<InventoryContainerModel>(ContainerEnumName::HotbarContainer, 9, mPlayer));
	_addContainer(std::make_shared<InventoryContainerModel>(ContainerEnumName::InventoryContainer, containerSize - 9, mPlayer));
	_addContainer(std::make_shared<InventoryContainerModel>(ContainerEnumName::CombinedHotbarAndInventoryContainer, containerSize, mPlayer));
}