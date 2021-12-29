#include "SceneManager.h"
#include <cassert>

using namespace rsk::scene;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="manager">管理者</param>
SceneManager::SceneChanger::SceneChanger( SceneManager* manager ) : 

    m_manager( manager )

{
}

/// <summary>
/// 追加
/// </summary>
/// <param name="TYPE">シーンの種類</param>
/// <param name="SENDING_DATA">送信する情報</param>
/// <param name="SENDER_TYPE">送信したシーンの種類</param>
void SceneManager::SceneChanger::Push( 
    const SceneTypeHolder   TYPE, 
    const std::any&         SENDING_DATA,
    const SceneTypeHolder   SENDER_TYPE
) {
    m_parameters.emplace_back( TYPE, ChangeType::PUSH, SENDING_DATA, SENDER_TYPE );
}

/// <summary>
/// 除去
/// </summary>
void SceneManager::SceneChanger::Pop() 
{
    m_parameters.emplace_back( 
        SceneTypeHolder::NONE, 
        ChangeType::POP,
        std::any(),
        SceneTypeHolder::NONE
    );
}

/// <summary>
/// 置き換え
/// </summary>
/// <param name="TYPE">シーンの種類</param>
/// <param name="SENDING_DATA">送信する情報</param>
/// <param name="SENDER_TYPE">送信したシーンの種類</param>
void SceneManager::SceneChanger::Replace( 
    const SceneTypeHolder   TYPE, 
    const std::any&         SENDING_DATA,
    const SceneTypeHolder   SENDER_TYPE
) {
    m_parameters.emplace_back( TYPE, ChangeType::REPLACE, SENDING_DATA, SENDER_TYPE );
}

/// <summary>
/// 変更
/// </summary>
/// <returns>変更が成功したか判別する値</returns>
bool SceneManager::SceneChanger::Change() 
{
    // 変更中でもシーンを追加できるようにするため、
    // 先頭の要素を1つずつ取り出して処理する
    while ( !m_parameters.empty() )
    {
        if ( !ChangeByParameter( m_parameters.front() ) ) return false;
        m_parameters.pop_front();
    }

    return true;
}

/// <summary>
/// パラメータで変更
/// </summary>
/// <param name="PARAMETER">パラメータ</param>
/// <returns>変更が成功したか判別する値</returns>
bool SceneManager::SceneChanger::ChangeByParameter( const ChangeParameter& PARAMETER ) 
{
    const auto CHANGE_TYPE = PARAMETER.m_change_type;

    if ( CHANGE_TYPE == ChangeType::PUSH ) 
    {
        return m_manager->Push( 
            PARAMETER.m_scene_type, 
            PARAMETER.m_sending_data, 
            PARAMETER.m_sender_type
        );
    }

    if ( CHANGE_TYPE == ChangeType::REPLACE ) 
    {
        return m_manager->Replace(
            PARAMETER.m_scene_type, 
            PARAMETER.m_sending_data,
            PARAMETER.m_sender_type 
        );
    }

    assert( CHANGE_TYPE == ChangeType::POP );
    m_manager->Pop();

    return true;
}
