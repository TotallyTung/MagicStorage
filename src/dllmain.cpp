#include "dllmain.hpp"
#include "features/MagicStorage.hpp"

ModFunction void Initialize(AmethystContext& ctx, const Amethyst::Mod& mod)  {
    Amethyst::InitializeAmethystMod(ctx, mod);

    MagicStorage::initEvents(Amethyst::GetEventBus());
}
