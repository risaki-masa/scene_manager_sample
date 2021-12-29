#include "Scene1.h"
#include "SceneType.h"
#include "SceneSenderData.h"
#include <format>

using namespace rsk::application::sample;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="TYPE">シーンの種類</param>
/// <param name="changer">シーンの変更者</param>
Scene1::Scene1( 
    const scene::SceneTypeHolder    TYPE, 
    scene::ISceneChangeable*        changer 
) : 

    Scene( TYPE, changer ) 

{
}

/// <summary>
/// 初期化する時の処理
/// </summary>
/// <param name="SHARED_DATA">共有の情報</param>
/// <returns>初期化に成功したか判別する値</returns>
bool Scene1::OnInitialize( const std::any& SHARED_DATA ) 
{
    const auto CAST_DATA    = std::any_cast<SceneSharedData*>( SHARED_DATA );
    m_renderer              = CAST_DATA->m_renderer;
    m_input_state           = CAST_DATA->m_input_state;

    return true;
}

/// <summary>
/// 更新する時の処理
/// </summary>
/// <returns>更新を続行するか判別する値</returns>
bool Scene1::OnUpdate() 
{
    if ( !m_can_update ) 
    { 
        // シーンを除いた瞬間に m_can_update を true にすると、
        // IsPressed( input::VirtualKeyCode::R ) により全てのシーンが除かれてしまうため、1フレーム待機してから true にする
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
/// 描画する時の処理
/// </summary>
void Scene1::OnDraw() 
{
    m_renderer->DrawString( 
        Position{ 10, 10 + m_scene_count * 20 }, 
        std::format( L"{}. シーン1", m_scene_count ),
        Color{ 255, 0, 0 }
    );
}

/// <summary>
/// 終了する時の処理
/// </summary>
void Scene1::OnFinalize() 
{
}

/// <summary>
/// 情報を受信した時の処理
/// </summary>
/// <param name="DATA">情報</param>
/// <param name="SENDER_TYPE">送信者の種類</param>
void Scene1::OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE ) 
{
    if ( !DATA.has_value() ) return;

    const auto CAST_DATA    = std::any_cast<SceneSenderData>( DATA );
    m_scene_count           = CAST_DATA.m_scene_count;
    m_on_pop                = CAST_DATA.m_on_pop;
}