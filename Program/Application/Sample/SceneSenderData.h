#pragma once

#include <functional>

namespace rsk::application::sample 
{
    /// <summary>
    /// シーンの送信情報
    /// </summary>
    struct SceneSenderData
    {
        int                     m_scene_count   = 1;
        std::function<void()>   m_on_pop        = nullptr;
    };
}