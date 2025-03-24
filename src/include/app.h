#pragma once

#include "imageData.h"
#include <unordered_map>
#include <string>

namespace app
{
    void RenderWindows(std::unordered_map<std::string, ImageData> &loadedImages);
}