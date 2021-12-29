#pragma once

#include "../../Rendering/IRenderer.h"
#include "../../Input/InputState.h"

namespace rsk::application::sample
{
    /// <summary>
    /// シーンの共有情報を管理する構造体
    /// </summary>
    struct SceneSharedData 
    {
        rendering::IRenderer*   m_renderer      = nullptr;
        input::InputState*      m_input_state   = nullptr;
    };
}