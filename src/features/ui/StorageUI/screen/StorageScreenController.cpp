#include "StorageScreenController.hpp"
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src/common/world/containers/ContainerFactory.hpp>

StorageScreenController::StorageScreenController(std::shared_ptr<ClientInstanceScreenModel> model, std::shared_ptr<StorageInfo> info)
	: ClientInstanceScreenController(model), storageInfo(info) {
	_registerBindings();
}

void StorageScreenController::_registerBindings() {

}