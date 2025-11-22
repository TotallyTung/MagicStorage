#pragma once
#include <mc/src-client/common/client/gui/screens/controllers/ClientInstanceScreenController.hpp>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <features/block/blocks/StorageHeart/StorageEnums.hpp>

class StorageScreenController : public ClientInstanceScreenController {
public:
	std::shared_ptr<StorageInfo> storageInfo;

public:
	StorageScreenController(std::shared_ptr<ClientInstanceScreenModel> model, std::shared_ptr<StorageInfo> info);

	void _registerBindings();
};