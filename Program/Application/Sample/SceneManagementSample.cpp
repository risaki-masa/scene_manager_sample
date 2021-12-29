#include "SceneManagementSample.h"
#include "SceneType.h"

using namespace rsk::application::sample;

/// <summary>
/// ����������
/// </summary>
/// <returns>�������ɐ������������ʂ���l</returns>
bool SceneManagementSample::Initialize()
{
    if ( !m_window.Create( L"�V�[���Ǘ��̃T���v��", 800, 600 ) ) return false;
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
/// �X�V
/// </summary>
/// <returns>�X�V�𑱍s���邩���ʂ���l</returns>
bool SceneManagementSample::Update()
{
    m_frame_rate_controller.Control();

    if ( !m_message_dispatcher.Dispatch() ) return false;
    if ( !m_input_state.Update() )          return false;
    if ( !m_scene_manager.Update() )        return false;

    return true;
}

/// <summary>
/// �`��
/// </summary>
void SceneManagementSample::Draw()
{
    m_renderer.Clear();
    m_scene_manager.Draw();
    m_renderer.CopyFromBackBufferToFrontBuffer();
}

/// <summary>
/// �I������
/// </summary>
void SceneManagementSample::Finalize()
{
    m_scene_manager.Finalize();
    m_renderer.Destroy();
    m_window.Destroy();
}
