#pragma once
#include "../../CustomBlock.hpp"

class CraftingInterface : public CustomBlock {
public:
	inline static const std::string identifier = "mstorage:crafting_interface";

public:
	CraftingInterface(const std::string& name, short id) : CustomBlock(name, id, Material::getMaterial(MaterialType::Solid)) {};

	virtual void registerItem(RegisterItemsEvent& ev) override {
		auto& constructionTab = ev.mCreativeItemRegistry.GetVanillaCategory(CreativeItemCategory::Construction);

		ev.itemRegistry.registerItemShared<BlockItem>(
			mNameInfo.mFullName.getString(),
			getBlockItemId(),
			mNameInfo.mFullName
		);

		constructionTab.AddCreativeItem(*this);
	}

	virtual void initGraphics(InitBlockGraphicsEvent& ev) override {
		BlockGraphics* radioactiveSubstanceBG = BlockGraphics::createBlockGraphics(mNameInfo.mFullName, BlockShape::BLOCK);
		radioactiveSubstanceBG->setTextureItem(identifier);
		radioactiveSubstanceBG->setDefaultCarriedTextures();
	}

	virtual bool use(Player& player, const BlockPos& pos, Facing::Name face) const override;
};