#pragma once

#include "../../Scene/Scene.h"
#include "SceneSharedData.h"

namespace rsk::application::sample
{
    using Scene             = scene::Scene;
    using SceneTypeHolder   = scene::SceneTypeHolder;
    using Position          = rendering::IRenderer::Position;
    using Color             = rendering::IRenderer::Color;

    /// <summary>
    /// シーン1を管理するクラス
    /// </summary>
    class Scene1 : public Scene 
    {
    public:
        Scene1( 
            const scene::SceneTypeHolder    TYPE, 
            scene::ISceneChangeable*        changer  
        );
        [[nodiscard]] bool OnInitialize( const std::any& SHARED_DATA ) override;
        [[nodiscard]] bool OnUpdate() override;
        void OnDraw() override;
        void OnFinalize() override;
        void OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE ) override;
    private:
        rendering::IRenderer*   m_renderer              = nullptr;
        input::InputState*      m_input_state           = nullptr;
        int                     m_scene_count           = 1;
        std::function<void()>   m_on_pop                = nullptr;
        bool                    m_can_update            = true;
        bool                    m_is_updating_from_next = false;
    };
}