#include "SceneManager.h"
#include "Scene.h"
#include <cassert>

using namespace rsk::scene;

/// <summary>
/// 初期化
/// </summary>
/// <param name="FIRST_SCENE_TYPE">最初に作るシーンの種類</param>
/// <param name="CREATOR">作成者</param>
/// <param name="SHARING_DATA">シーンに共有する情報</param>
/// <returns>初期化が成功したか判別する値</returns>
bool SceneManager::Initialize( 
    const SceneTypeHolder   FIRST_SCENE_TYPE, 
    const ISceneCreatable*  CREATOR,
    const std::any&         SHARING_DATA 
) {
    assert( m_CREATOR == nullptr );
    assert( !m_sharing_data.has_value() );
    assert( m_changer == nullptr );

    m_CREATOR       = CREATOR;
    m_sharing_data  = SHARING_DATA;
    m_changer       = std::make_unique<SceneChanger>( this );

    m_changer->Push( FIRST_SCENE_TYPE );

    return true;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>処理を続行するか判別する値</returns>
bool SceneManager::Update()
{
    if ( !m_changer->Change() ) return false;
    if ( m_scenes.empty() )     return false;

    for ( auto& scene : m_scenes )
    {
        if ( !scene->OnUpdate() ) return false;
    }

    return true;
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Draw() 
{
    for ( auto& scene : m_scenes ) scene->OnDraw();
}

/// <summary>
/// 終了
/// </summary>
void SceneManager::Finalize() 
{
    for ( auto& scene : m_scenes ) scene->OnFinalize();
    m_scenes.clear();

    m_CREATOR = nullptr;
    m_sharing_data.reset();
    m_changer.reset();
}

/// <summary>
/// 追加
/// </summary>
/// <param name="TYPE">シーンの種類</param>
/// <param name="SENDING_DATA">送信する情報</param>
/// <param name="SENDER_TYPE">送信したシーンの種類</param>
/// <returns>追加に成功したか判別する値</returns>
bool SceneManager::Push( 
    const SceneTypeHolder   TYPE,
    const std::any&         SENDING_DATA, 
    const SceneTypeHolder   SENDER_TYPE
) {
    auto scene = m_CREATOR->Create( TYPE, m_changer.get() );

    scene->OnReceivedData( SENDING_DATA, SENDER_TYPE );
    if ( !scene->OnInitialize( m_sharing_data ) )   return false;

    m_scenes.push_front( std::move( scene ) );

    return true;
}

/// <summary>
/// 除去
/// </summary>
void SceneManager::Pop() 
{
    m_scenes.front()->OnFinalize();
    m_scenes.pop_front();
}

/// <summary>
/// 置き換え
/// </summary>
/// <param name="TYPE">シーンの種類</param>
/// <param name="SENDING_DATA">送信する情報</param>
/// <param name="SENDER_TYPE">送信したシーンの種類</param>
/// <returns>置き換えに成功したか判別する値</returns>
bool SceneManager::Replace( 
    const SceneTypeHolder   TYPE,
    const std::any&         SENDING_DATA, 
    const SceneTypeHolder   SENDER_TYPE
) {
    Pop();
    const auto IS_COMPLETED = Push( TYPE, SENDING_DATA, SENDER_TYPE );

    return IS_COMPLETED;
}
