#pragma once
#include <magic_enum/magic_enum.hpp>
#include "../../CustomBlock.hpp"

struct StorageInfo {
	int maxStorages = 32;
	int storageCapacity = 0;
	std::unordered_set<BlockPos> storageUnits;
	bool hasCraftingInterface = false;
};

enum class StorageCoreError {
	NONE = 0,
	CONNECTION_ERROR = 1,
	STORAGE_LIMIT_ERROR = 2,
};

class StorageHeart : public CustomBlock {
public:
	inline static const std::string identifier = "mstorage:storage_heart";
	std::shared_ptr<StorageInfo> storageInfo = std::make_shared<StorageInfo>();

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
};