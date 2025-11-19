#pragma once
#include "../../CustomBlock.hpp"

class StorageUnit : public CustomBlock {
private:

public:
	inline static const std::string identifier = "mstorage:storage_unit";
	StorageUnit(const std::string& name, short id) : CustomBlock(name, id, Material::getMaterial(MaterialType::Solid)) {};

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
		BlockGraphics* blockGraphic = BlockGraphics::createBlockGraphics(mNameInfo.mFullName, BlockShape::BLOCK);
		blockGraphic->setTextureItem(identifier);
		blockGraphic->setDefaultCarriedTextures();
	}

	virtual bool use(Player& player, const BlockPos& pos, Facing::Name face) const override;
};