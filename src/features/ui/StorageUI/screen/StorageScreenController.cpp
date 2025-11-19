#include "StorageScreenController.hpp"
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src/common/world/containers/ContainerFactory.hpp>
#include <features/ui/StorageUI/container/manager/StorageManagerModel.hpp>

StorageScreenController::StorageScreenController(std::shared_ptr<ClientInstanceScreenModel> model, InteractionModel interaction, std::shared_ptr<StorageInfo> info) : ContainerScreenController(model, interaction), storageInfo(info) {
	auto& player = *model->getPlayer();
	setAssociatedEntityUniqueID(player.getUniqueID());
	auto managerModel = ContainerFactory::clientCreateContainerManagerModel<StorageManagerModel>(player, ContainerID::CONTAINER_ID_NONE, player);
	_registerBindings();
	_registerCoalesceOrder();
	_registerAutoPlaceOrder();
}