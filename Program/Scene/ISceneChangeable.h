#pragma once

#include <any>
#include "SceneTypeHolder.h"

namespace rsk::scene 
{
    /// <summary>
    /// シーンを変更できる機能のインターフェース
    /// </summary>
    class ISceneChangeable 
    {
    public:
        virtual ~ISceneChangeable() = default;
        virtual void Push( 
            const SceneTypeHolder   TYPE, 
            const std::any&         SENDING_DATA    = std::any(),
            const SceneTypeHolder   SENDER_TYPE     = SceneTypeHolder::NONE
        ) = 0;
        virtual void Pop()  = 0;
        virtual void Replace( 
            const SceneTypeHolder   TYPE, 
            const std::any&         SENDING_DATA    = std::any(),
            const SceneTypeHolder   SENDER_TYPE     = SceneTypeHolder::NONE
        ) = 0;
    };
}