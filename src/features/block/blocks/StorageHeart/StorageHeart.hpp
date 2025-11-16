#pragma once
#include "../../CustomBlock.hpp"
#include "../StorageUnit/StorageUnit.hpp"
#include "StorageHeartListener.hpp"

class StorageHeart : public CustomBlock {
public:
	inline static const std::string identifier = "mstorage:storage_heart";
	std::shared_ptr<StorageInfo> storageInfo = std::make_shared<StorageInfo>();
	mutable std::shared_ptr<StorageHeartListener> listener = nullptr;

public:
	StorageHeart(const std::string& name, short id) : CustomBlock(name, id, Material::getMaterial(MaterialType::Solid)) {};

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
	virtual void onPlace(BlockSource& src, const BlockPos& pos) const;
	virtual void onRemove(BlockSource& src, const BlockPos& pos) const;
};