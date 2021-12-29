#include "Scene.h"

using namespace rsk::scene;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="TYPE">���</param>
/// <param name="changer">�ύX��</param>
Scene::Scene( const SceneTypeHolder TYPE, ISceneChangeable* changer ) :

    m_type( TYPE ),
    m_changer( changer )

{
}

/// <summary>
/// ������M
/// ���̊֐��̓V�[����ǉ��E�u�������������Ɉ����uDATA�v���w�肵�Ă���ƌĂ΂��
/// �Ăяo���̃^�C�~���O�́AOnInitialize�̑O�ł���
/// </summary>
/// <param name="DATA">���</param>
/// <param name="SENDER_TYPE">���M�����V�[���̎��</param>
void Scene::OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE ) 
{
}

/// <summary>
/// �ύX�҂��擾
/// </summary>
/// <returns>�ύX��</returns>
ISceneChangeable* Scene::GetChanger() const
{
    return m_changer;
}