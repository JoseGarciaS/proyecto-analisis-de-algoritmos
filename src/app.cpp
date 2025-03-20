#include "app.h"
#include "imgui.h"
#include "windowRenderer.h"

namespace app
{
    void RenderWindows()
    {
        ImGui::ShowDemoWindow();
        templateWindow::Render();
    }
}