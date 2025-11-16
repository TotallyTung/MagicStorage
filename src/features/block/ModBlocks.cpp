#include "ModBlocks.hpp"
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <mc/src/common/world/item/registry/ItemRegistry.hpp>
#include <mc/src/common/world/item/BlockItem.hpp>
#include <mc/src-client/common/client/renderer/block/BlockGraphics.hpp>
#include "blocks/StorageComponent/StorageComponent.hpp"
#include "blocks/StorageHeart/StorageHeart.hpp"
#include "blocks/StorageUnit/StorageUnit.hpp"
#include "blocks/CraftingInterface/CraftingInterface.hpp"

std::unordered_map<std::string, WeakPtr<CustomBlock>> ModBlocks::customBlocks = {};

WeakPtr<CustomBlock> ModBlocks::getBlock(const std::string& identifier) {
	auto it = customBlocks.find(identifier);
	if (it == customBlocks.end()) return nullptr;
	return it->second;
}

void ModBlocks::registerBlocks(RegisterBlocksEvent& ev) {
	customBlocks[StorageComponent::identifier] = BlockTypeRegistry::registerBlock<StorageComponent>(StorageComponent::identifier, ev.blockDefinitions.getNextBlockId());
	customBlocks[StorageHeart::identifier] = BlockTypeRegistry::registerBlock<StorageHeart>(StorageHeart::identifier, ev.blockDefinitions.getNextBlockId());
	customBlocks[StorageUnit::identifier] = BlockTypeRegistry::registerBlock<StorageUnit>(StorageUnit::identifier, ev.blockDefinitions.getNextBlockId());
	customBlocks[CraftingInterface::identifier] = BlockTypeRegistry::registerBlock<CraftingInterface>(CraftingInterface::identifier, ev.blockDefinitions.getNextBlockId());
}

void ModBlocks::registerBlockItems(RegisterItemsEvent& ev) {
	for (auto& it : customBlocks) it.second->registerItem(ev);
}

void ModBlocks::InitBlockGraphics(InitBlockGraphicsEvent& ev) {
	for (auto& it : customBlocks) it.second->initGraphics(ev);
}