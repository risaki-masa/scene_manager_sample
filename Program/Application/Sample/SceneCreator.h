#pragma once

#include "../../Scene/ISceneCreatable.h"
#include "SceneType.h"

namespace rsk::application::sample 
{
    /// <summary>
    /// �V�[���̍쐬���s���N���X
    /// </summary>
    class SceneCreator : public scene::ISceneCreatable 
    {
    public:
        using ScenePtr          = scene::ScenePtr;
        using SceneTypeHolder   = scene::SceneTypeHolder;
        using ISceneChangeable  = scene::ISceneChangeable;

        ScenePtr Create( 
            const SceneTypeHolder   TYPE, 
            ISceneChangeable*       changer 
        ) const override;
    };
}