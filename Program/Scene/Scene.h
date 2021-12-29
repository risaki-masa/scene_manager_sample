#pragma once

#include <any>
#include <functional>
#include "SceneTypeHolder.h"
#include "ISceneChangeable.h"

namespace rsk::scene 
{
    /// <summary>
    /// シーンを管理するクラス
    /// </summary>
    class Scene
    {
    public:
        Scene( const SceneTypeHolder TYPE, ISceneChangeable* changer );
        virtual ~Scene() = default;
        [[nodiscard]] virtual bool OnInitialize( const std::any& SHARED_DATA ) = 0;
        [[nodiscard]] virtual bool OnUpdate() = 0;
        virtual void OnDraw() = 0;
        virtual void OnFinalize() = 0;
        virtual void OnReceivedData( const std::any DATA, const SceneTypeHolder SENDER_TYPE );
    protected:
        template<typename T>
        [[nodiscard]] T GetType() const { return m_type.Get<T>(); }
        [[nodiscard]] ISceneChangeable* GetChanger() const;
    private:
        SceneTypeHolder     m_type      = SceneTypeHolder::NONE;
        ISceneChangeable*   m_changer   = nullptr;
    };
}