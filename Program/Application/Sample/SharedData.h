#pragma once

#include "../../Rendering/IRenderer.h"
#include "../../Input/InputState.h"

namespace rsk::application::sample
{
    /// <summary>
    /// ‹¤—L‚Ìî•ñ‚ğŠÇ—‚·‚é\‘¢‘Ì
    /// </summary>
    struct SharedData 
    {
        rendering::IRenderer*   m_renderer      = nullptr;
        input::InputState*      m_input_state   = nullptr;
    };
}