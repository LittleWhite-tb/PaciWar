#include "Settings.hpp"

#include "version.hpp"

const std::string Settings::windowName = "PaciWar v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH " - " VERSION_SHA;

const std::string Settings::fontPath = "./data/DejaVuSansMono.ttf";
#if DEBUG_INFO == 1
    const std::string Settings::debugFontPath = "./data/DejaVuSansMono.ttf";
#endif
