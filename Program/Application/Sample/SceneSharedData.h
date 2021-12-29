#pragma once

#include "../../Rendering/IRenderer.h"
#include "../../Input/InputState.h"

namespace rsk::application::sample
{
    /// <summary>
    /// �V�[���̋��L�����Ǘ�����\����
    /// </summary>
    struct SceneSharedData 
    {
        rendering::IRenderer*   m_renderer      = nullptr;
        input::InputState*      m_input_state   = nullptr;
    };
}