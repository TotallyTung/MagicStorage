#include "MagicStorage.hpp"
#include <amethyst/runtime/events/GameEvents.hpp>
#include "item/ModItems.hpp"
#include "block/ModBlocks.hpp"

void MagicStorage::initEvents(Amethyst::EventBus& bus) {
	bus.AddListener<RegisterItemsEvent>(&ModItems::registerItems);
	bus.AddListener<RegisterBlocksEvent>(&ModBlocks::registerBlocks);
	bus.AddListener<InitBlockGraphicsEvent>(&ModBlocks::InitBlockGraphics);
	bus.AddListener<RegisterItemsEvent>(&ModBlocks::registerBlockItems);
}