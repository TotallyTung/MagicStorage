#include "ModItems.hpp"
#include <mc/src/common/world/item/registry/ItemRegistry.hpp>
#include "items/ShadowDiamond/ShadowDiamond.hpp"

void ModItems::registerItems(RegisterItemsEvent& ev) {
	ev.itemRegistry.registerItemShared<ShadowDiamond>(ShadowDiamond::identifier, ev.itemRegistry.getNextItemID());
}