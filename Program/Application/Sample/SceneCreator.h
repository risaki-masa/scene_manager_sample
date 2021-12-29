#pragma once

#include "../../Scene/ISceneCreatable.h"
#include "SceneType.h"

namespace rsk::application::sample 
{
    /// <summary>
    /// シーンの作成を行うクラス
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