#pragma once
#include <mc/src/common/world/item/Item.hpp>

class ShadowDiamond : public Item {
public:
	inline static std::string identifier = "mstorage:shadow_diamond";
	ShadowDiamond(const std::string& name, short id) : Item(name, id) {
		setIconInfo("mstorage:shadow_diamond", 0);
	}
};