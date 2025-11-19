#pragma once
#include <mc/src/common/world/Container.hpp>
#include <mc/src/common/world/item/ItemStack.hpp>

class StorageContainer : public Container {
public:
	std::vector<ItemStack> mItems;

public:
	StorageContainer();
};