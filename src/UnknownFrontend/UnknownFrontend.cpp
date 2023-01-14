#include <UnknownFrontend/UnknownFrontend.h>

#include <x86/TranslatorImpl.x86.h>
#include <arm/TranslatorImpl.arm.h>

namespace ufrontend {

////////////////////////////////////////////////////////////
// Static
std::unique_ptr<UnknownFrontendTranslator>
UnknownFrontendTranslator::createTranslator(
    uir::Context &C,
    const std::string &BinaryFile,
    const std::string &SymbolFile,
    const std::string &ConfigFile,
    const Platform Platform)
{
    auto Arch = C.getArch();

    if (Arch == uir::Context::Arch::ArchX86)
    {
        return std::make_unique<UnknownFrontendTranslatorImplX86>(C, Platform, BinaryFile, SymbolFile, ConfigFile);
    }
    else if (Arch == uir::Context::Arch::ArchARM)
    {
        return std::make_unique<UnknownFrontendTranslatorImplARM>(C, Platform, BinaryFile, SymbolFile, ConfigFile);
    }

    // TODO

    return {};
}

} // namespace ufrontend
