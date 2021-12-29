#include "Scene1.h"
#include "SceneType.h"
#include "SceneSenderData.h"
#include <format>

using namespace rsk::application::sample;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="changer">�V�[���̕ύX��</param>
Scene1::Scene1( 
    const scene::SceneTypeHolder    TYPE, 
    scene::ISceneChangeable*        changer 
) : 

    Scene( TYPE, changer ) 

{
}

/// <summary>
/// ���������鎞�̏���
/// </summary>
/// <param name="SHARED_DATA">���L�̏��</param>
/// <returns>�������ɐ������������ʂ���l</returns>
bool Scene1::OnInitialize( const std::any& SHARED_DATA ) 
{
    const auto CAST_DATA    = std::any_cast<SceneSharedData*>( SHARED_DATA );
    m_renderer              = CAST_DATA->m_renderer;
    m_input_state           = CAST_DATA->m_input_state;

    return true;
}

/// <summary>
/// �X�V���鎞�̏���
/// </summary>
/// <returns>�X�V�𑱍s���邩���ʂ���l</returns>
bool Scene1::OnUpdate() 
{
    if ( !m_can_update ) 
    { 
        // �V�[�����������u�Ԃ� m_can_update �� true �ɂ���ƁA
        // IsPressed( input::VirtualKeyCode::R ) �ɂ��S�ẴV�[����������Ă��܂����߁A1�t���[���ҋ@���Ă��� true �ɂ���
        if ( m_is_updating_from_next ) 
        {
            m_is_updating_from_next = false;
            m_can_update            = true;
        }

        return true;
    }

    if ( m_input_state->IsPressed( input::VirtualKeyCode::A ) ) 
    {
        auto sender_data            = SceneSenderData();
        sender_data.m_scene_count   = m_scene_count + 1;
        sender_data.m_on_pop        = [this] { m_is_updating_from_next = true; };

        GetChanger()->Push( SceneType::SCENE_2, sender_data );
        m_can_update = false;
    }
    else if ( m_input_state->IsPressed( input::VirtualKeyCode::S ) ) 
    {
        auto sender_data            = SceneSenderData();
        sender_data.m_scene_count   = m_scene_count;
        sender_data.m_on_pop        = m_on_pop;

        GetChanger()->Replace( SceneType::SCENE_2, sender_data );
    }
    else if ( m_input_state->IsPressed( input::VirtualKeyCode::R ) ) 
    {
        GetChanger()->Pop();
        if ( m_on_pop != nullptr ) m_on_pop();
    }

    return true;
}

/// <summary>
/// �`�悷�鎞�̏���
/// </summary>
void Scene1::OnDraw() 
{
    m_renderer->DrawString( 
        Position{ 10, 10 + m_scene_count * 20 }, 
        std::format( L"{}. �V�[��1", m_scene_count ),
        Color{ 255, 0, 0 }
    );
}

/// <summary>
/// �I�����鎞�̏���
/// </summary>
void Scene1::OnFinalize() 
{
}

/// <summary>
/// ������M�������̏���
/// </summary>
/// <param name="DATA">���</param>
/// <param name="SENDER_TYPE">���M�҂̎��</param>
void Scene1::OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE ) 
{
    if ( !DATA.has_value() ) return;

    const auto CAST_DATA    = std::any_cast<SceneSenderData>( DATA );
    m_scene_count           = CAST_DATA.m_scene_count;
    m_on_pop                = CAST_DATA.m_on_pop;
}