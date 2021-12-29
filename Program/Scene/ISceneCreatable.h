#pragma once

#include <memory>
#include "SceneTypeHolder.h"

namespace rsk::scene
{
    class Scene;
    class ISceneChangeable;

    using ScenePtr = std::shared_ptr<Scene>;

    /// <summary>
    /// �V�[�����쐬�ł���@�\�̃C���^�[�t�F�[�X
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