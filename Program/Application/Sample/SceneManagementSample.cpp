#include "SceneManagementSample.h"
#include "SceneType.h"

using namespace rsk::application::sample;

/// <summary>
/// 初期化処理
/// </summary>
/// <returns>初期化に成功したか判別する値</returns>
bool SceneManagementSample::Initialize()
{
    if ( !m_window.Create( L"シーン管理のサンプル", 800, 600 ) ) return false;
    m_window.Show();

    if ( !m_renderer.Create( m_window ) ) return false;

    m_shared_data.m_renderer    = &m_renderer;
    m_shared_data.m_input_state = &m_input_state;

    const auto IS_INITIALIZED_SCENE_MANAGER = m_scene_manager.Initialize(
        SceneType::SCENE_1,
        &m_scene_creator,
        &m_shared_data
    );

    if ( !IS_INITIALIZED_SCENE_MANAGER ) return false;

    return true;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>更新を続行するか判別する値</returns>
bool SceneManagementSample::Update()
{
    m_frame_rate_controller.Control();

    if ( !m_message_dispatcher.Dispatch() ) return false;
    if ( !m_input_state.Update() )          return false;
    if ( !m_scene_manager.Update() )        return false;

    return true;
}

/// <summary>
/// 描画
/// </summary>
void SceneManagementSample::Draw()
{
    m_renderer.Clear();
    m_scene_manager.Draw();
    m_renderer.CopyFromBackBufferToFrontBuffer();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManagementSample::Finalize()
{
    m_scene_manager.Finalize();
    m_renderer.Destroy();
    m_window.Destroy();
}
