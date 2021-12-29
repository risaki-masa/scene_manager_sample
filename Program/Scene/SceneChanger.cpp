#include "SceneManager.h"
#include <cassert>

using namespace rsk::scene;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="manager">�Ǘ���</param>
SceneManager::SceneChanger::SceneChanger( SceneManager* manager ) : 

    m_manager( manager )

{
}

/// <summary>
/// �ǉ�
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="SENDING_DATA">���M������</param>
/// <param name="SENDER_TYPE">���M�����V�[���̎��</param>
void SceneManager::SceneChanger::Push( 
    const SceneTypeHolder   TYPE, 
    const std::any&         SENDING_DATA,
    const SceneTypeHolder   SENDER_TYPE
) {
    m_parameters.emplace_back( TYPE, ChangeType::PUSH, SENDING_DATA, SENDER_TYPE );
}

/// <summary>
/// ����
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
/// �u������
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="SENDING_DATA">���M������</param>
/// <param name="SENDER_TYPE">���M�����V�[���̎��</param>
void SceneManager::SceneChanger::Replace( 
    const SceneTypeHolder   TYPE, 
    const std::any&         SENDING_DATA,
    const SceneTypeHolder   SENDER_TYPE
) {
    m_parameters.emplace_back( TYPE, ChangeType::REPLACE, SENDING_DATA, SENDER_TYPE );
}

/// <summary>
/// �ύX
/// </summary>
/// <returns>�ύX���������������ʂ���l</returns>
bool SceneManager::SceneChanger::Change() 
{
    // �ύX���ł��V�[����ǉ��ł���悤�ɂ��邽�߁A
    // �擪�̗v�f��1�����o���ď�������
    while ( !m_parameters.empty() )
    {
        if ( !ChangeByParameter( m_parameters.front() ) ) return false;
        m_parameters.pop_front();
    }

    return true;
}

/// <summary>
/// �p�����[�^�ŕύX
/// </summary>
/// <param name="PARAMETER">�p�����[�^</param>
/// <returns>�ύX���������������ʂ���l</returns>
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
