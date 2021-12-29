#include "SceneManager.h"
#include "Scene.h"
#include <cassert>

using namespace rsk::scene;

/// <summary>
/// ������
/// </summary>
/// <param name="FIRST_SCENE_TYPE">�ŏ��ɍ��V�[���̎��</param>
/// <param name="CREATOR">�쐬��</param>
/// <param name="SHARING_DATA">�V�[���ɋ��L������</param>
/// <returns>���������������������ʂ���l</returns>
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
/// �X�V
/// </summary>
/// <returns>�����𑱍s���邩���ʂ���l</returns>
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
/// �`��
/// </summary>
void SceneManager::Draw() 
{
    for ( auto& scene : m_scenes ) scene->OnDraw();
}

/// <summary>
/// �I��
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
/// �ǉ�
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="SENDING_DATA">���M������</param>
/// <param name="SENDER_TYPE">���M�����V�[���̎��</param>
/// <returns>�ǉ��ɐ������������ʂ���l</returns>
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
/// ����
/// </summary>
void SceneManager::Pop() 
{
    m_scenes.front()->OnFinalize();
    m_scenes.pop_front();
}

/// <summary>
/// �u������
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="SENDING_DATA">���M������</param>
/// <param name="SENDER_TYPE">���M�����V�[���̎��</param>
/// <returns>�u�������ɐ������������ʂ���l</returns>
bool SceneManager::Replace( 
    const SceneTypeHolder   TYPE,
    const std::any&         SENDING_DATA, 
    const SceneTypeHolder   SENDER_TYPE
) {
    Pop();
    const auto IS_COMPLETED = Push( TYPE, SENDING_DATA, SENDER_TYPE );

    return IS_COMPLETED;
}
