#pragma once

#include "../../Rendering/IRenderer.h"
#include "../../Input/InputState.h"

namespace rsk::application::sample
{
    /// <summary>
    /// 共有の情報を管理する構造体
    /// </summary>
    struct SharedData 
    {
        rendering::IRenderer*   m_renderer      = nullptr;
        input::InputState*      m_input_state   = nullptr;
    };
}