#pragma once
#include <mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <features/block/blocks/StorageHeart/StorageEnums.hpp>

class StorageScreenController : public ContainerScreenController {
public:
	BlockPos pos;
	std::shared_ptr<StorageInfo> storageInfo;

public:
	StorageScreenController(std::shared_ptr<ClientInstanceScreenModel> model, InteractionModel interaction, std::shared_ptr<StorageInfo> info);


};