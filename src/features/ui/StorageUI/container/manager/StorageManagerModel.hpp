#pragma once
#include <mc/src/common/world/containers/managers/models/ContainerManagerModel.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>

class StorageManagerModel : public ContainerManagerModel {
public:
	StorageManagerModel(ContainerID id, Player& player);


};