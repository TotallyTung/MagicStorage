#pragma once
#include <mc/src/common/world/level/block/BlockLegacy.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include <mc/src-client/common/client/renderer/block/BlockGraphics.hpp>
#include <mc/src/common/world/item/registry/ItemRegistry.hpp>
#include <mc/src/common/world/item/BlockItem.hpp>

class CustomBlock : public BlockLegacy {
public:
	CustomBlock(const std::string& name, short id, const Material& material) : BlockLegacy(name, id, material) {};
	
	virtual void registerItem(RegisterItemsEvent&) {};
	virtual void initGraphics(InitBlockGraphicsEvent&) {};
};