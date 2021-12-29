#pragma once

#include <memory>
#include "SceneTypeHolder.h"

namespace rsk::scene
{
    class Scene;
    class ISceneChangeable;

    using ScenePtr = std::shared_ptr<Scene>;

    /// <summary>
    /// シーンを作成できる機能のインターフェース
    /// </summary>
    class ISceneCreatable
    {
    public:
        virtual ~ISceneCreatable() = default;
        virtual ScenePtr Create( 
            const SceneTypeHolder   TYPE, 
            ISceneChangeable*       changer
        ) const = 0;
    };
}