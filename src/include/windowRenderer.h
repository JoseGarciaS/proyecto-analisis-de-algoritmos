#pragma once
#include <unordered_map>
#include <string>
#include "imageData.h"

namespace templateWindow
{
    void Render();
};

namespace graphWindow
{
    void Render();
};

namespace knapsackWindow
{
    void Render(std::unordered_map<std::string, ImageData> &loadedImages);
};

namespace subsetsumWindow
{
    void Render();
};