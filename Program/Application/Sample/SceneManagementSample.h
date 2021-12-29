#pragma once

#include "../Application.h"
#include "../../Window/Window.h"
#include "../../Rendering/Renderer.h"
#include "../../Message/MessageDispatcher.h"
#include "../../Scene/SceneManager.h"
#include "SceneCreator.h"
#include "../../Input/InputState.h"
#include "../../Time/FrameRateController.h"
#include "SharedData.h"

namespace rsk::application::sample
{
    /// <summary>
    /// シーン管理のサンプルを管理するクラス
    /// </summary>
    class SceneManagementSample : public Application
    {
    private:
        [[nodiscard]] bool Initialize() override final;
        [[nodiscard]] bool Update()     override final;
        void Draw()                     override final;
        void Finalize()                 override final;

        window::Window              m_window;
        rendering::Renderer         m_renderer;
        message::MessageDispatcher  m_message_dispatcher;
        scene::SceneManager         m_scene_manager;
        SceneCreator                m_scene_creator;
        input::InputState           m_input_state;
        time::FrameRateController   m_frame_rate_controller;
        SharedData                  m_shared_data;
    };
}