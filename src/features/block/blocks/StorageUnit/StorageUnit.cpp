#include "StorageUnit.hpp"
#include <mc/src/common/world/level/BlockSource.hpp>

bool StorageUnit::use(Player& player, const BlockPos& pos, Facing::Name face) const {
	return false;
};