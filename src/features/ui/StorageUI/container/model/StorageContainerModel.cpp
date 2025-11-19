#include "StorageContainerModel.hpp"
#include <mc/src/common/world/containers/models/ContainerModel.hpp>

StorageContainerModel::StorageContainerModel(ContainerEnumName name, int size, Player& player) : ContainerModel(name, size, ContainerCategory::Default, true), mPlayer(player) {
	mContainer = std::make_unique<StorageContainer>();
}

Container* StorageContainerModel::_getContainer() {
	return mContainer.get();
}

int StorageContainerModel::_getContainerOffset() {
	return 0;
}

ContainerWeakRef StorageContainerModel::getContainerWeakRef() {
	auto* container = _getContainer();
	return ContainerWeakRef{
		mPlayer.getUniqueID(),
		ActorContainerType::ContainerComponent,
		BlockPos(0, 0, 0),
		container->mContainerRuntimeId
	};
}