#include "Scene.h"

using namespace rsk::scene;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="TYPE">種類</param>
/// <param name="changer">変更者</param>
Scene::Scene( const SceneTypeHolder TYPE, ISceneChangeable* changer ) :

    m_type( TYPE ),
    m_changer( changer )

{
}

/// <summary>
/// 情報を受信
/// この関数はシーンを追加・置き換えした時に引数「DATA」を指定していると呼ばれる
/// 呼び出しのタイミングは、OnInitializeの前である
/// </summary>
/// <param name="DATA">情報</param>
/// <param name="SENDER_TYPE">送信したシーンの種類</param>
void Scene::OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE ) 
{
}

/// <summary>
/// 変更者を取得
/// </summary>
/// <returns>変更者</returns>
ISceneChangeable* Scene::GetChanger() const
{
    return m_changer;
}