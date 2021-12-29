#include "SceneCreator.h"
#include "Scene1.h"
#include "Scene2.h"
#include <cassert>

using namespace rsk::application::sample;

/// <summary>
/// �V�[�����쐬
/// </summary>
/// <param name="TYPE">�V�[���̎��</param>
/// <param name="changer">�V�[���̕ύX��</param>
/// <returns>�V�[��</returns>
SceneCreator::ScenePtr SceneCreator::Create( 
    const SceneTypeHolder   TYPE, 
    ISceneChangeable*       changer 
) const {
    switch ( TYPE.Get<SceneType>() )
    {
    case SceneType::SCENE_1:
        return std::make_shared<Scene1>( TYPE, changer );
    case SceneType::SCENE_2:
        return std::make_shared<Scene2>( TYPE, changer );
    }

    assert( false );
    return nullptr;
}