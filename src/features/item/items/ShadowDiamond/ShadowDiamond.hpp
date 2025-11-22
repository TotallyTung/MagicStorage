#pragma once
#include <mc/src/common/world/item/Item.hpp>

class ShadowDiamond : public Item {
public:
	inline static std::string identifier = "magic_storage:shadow_diamond";
	ShadowDiamond(const std::string& name, short id) : Item(name, id) {
		setIconInfo("magic_storage:shadow_diamond", 0);
	}
};