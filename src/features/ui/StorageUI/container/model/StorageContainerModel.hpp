#pragma once
#include <mc/src/common/world/containers/models/ContainerModel.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <features/ui/StorageUI/container/StorageContainer.hpp>

class StorageContainerModel : ContainerModel {
public:
	std::unique_ptr<StorageContainer> mContainer;
	Player& mPlayer;

public:
	StorageContainerModel(ContainerEnumName name, int size, Player& player);

	virtual Container* _getContainer() override;
	virtual int _getContainerOffset() override;
	virtual ContainerWeakRef getContainerWeakRef() override;
};