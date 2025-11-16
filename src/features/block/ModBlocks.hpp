#pragma once
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include "CustomBlock.hpp"

class ModBlocks {
public:
	static std::unordered_map<std::string, WeakPtr<CustomBlock>> customBlocks;
	static WeakPtr<CustomBlock> getBlock(const std::string& identifier);
	static void registerBlocks(RegisterBlocksEvent&);
	static void registerBlockItems(RegisterItemsEvent&);
	static void InitBlockGraphics(InitBlockGraphicsEvent&);
};