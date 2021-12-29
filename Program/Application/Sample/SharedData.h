#pragma once

#include "../../Rendering/IRenderer.h"
#include "../../Input/InputState.h"

namespace rsk::application::sample
{
    /// <summary>
    /// ���L�̏����Ǘ�����\����
    /// </summary>
    struct SharedData 
    {
        rendering::IRenderer*   m_renderer      = nullptr;
        input::InputState*      m_input_state   = nullptr;
    };
}