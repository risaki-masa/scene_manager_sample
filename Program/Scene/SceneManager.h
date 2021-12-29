#pragma once

#include <list>
#include "ISceneChangeable.h"
#include "ISceneCreatable.h"

namespace rsk::scene 
{
    /// <summary>
    /// シーンを管理するクラス
    /// </summary>
    class SceneManager
    {
    public:
        [[nodiscard]] bool Initialize( 
            const SceneTypeHolder   FIRST_SCENE_TYPE, 
            const ISceneCreatable*  CREATOR,
            const std::any&         SHARING_DATA = std::any()
        );
        [[nodiscard]] bool Update();
        void Draw();
        void Finalize();
    private:
        /// <summary>
        /// シーンの変更を行うクラス
        /// </summary>
        class SceneChanger : public ISceneChangeable 
        {
        public:
            explicit SceneChanger( SceneManager* manager );
            ~SceneChanger() = default;
            void Push( 
                const SceneTypeHolder   TYPE, 
                const std::any&         SENDING_DATA    = std::any(),
                const SceneTypeHolder   SENDER_TYPE     = SceneTypeHolder::NONE
            ) override;
            void Pop() override;
            void Replace( 
                const SceneTypeHolder   TYPE, 
                const std::any&         SENDING_DATA,
                const SceneTypeHolder   SENDER_TYPE
            ) override;
            [[nodiscard]] bool Change();
        private:
            /// <summary>
            /// 変更の種類を管理する列挙型
            /// </summary>
            enum class ChangeType
            {
                PUSH,
                POP,
                REPLACE,

                NONE,
            };

            /// <summary>
            /// パラメータ( 変更を媒介するための情報 )を管理する構造体
            /// </summary>
            struct ChangeParameter 
            {
                SceneTypeHolder m_scene_type;
                ChangeType      m_change_type;
                std::any        m_sending_data;
                SceneTypeHolder m_sender_type;

                [[nodiscard]] ChangeParameter( 
                    const SceneTypeHolder   SCENE_TYPE,
                    const ChangeType        CHANGE_TYPE,
                    const std::any&         SENDING_DATA,
                    const SceneTypeHolder   SENDER_TYPE
                ) :

                    m_scene_type( SCENE_TYPE ),
                    m_change_type( CHANGE_TYPE ),
                    m_sending_data( SENDING_DATA ),
                    m_sender_type( SENDER_TYPE )

                {
                }
            };

            [[nodiscard]] bool ChangeByParameter( const ChangeParameter& PARAMETER );

            SceneManager*               m_manager = nullptr;
            std::list<ChangeParameter>  m_parameters;
        };

        [[nodiscard]] bool Push( 
            const SceneTypeHolder   TYPE, 
            const std::any&         SENDING_DATA, 
            const SceneTypeHolder   SENDER_TYPE
        );
        void Pop();
        [[nodiscard]] bool Replace( 
            const SceneTypeHolder   TYPE,
            const std::any&         SENDING_DATA, 
            const SceneTypeHolder   SENDER_TYPE
        );

        const ISceneCreatable*          m_CREATOR = nullptr;
        
        std::any                        m_sharing_data;
        std::unique_ptr<SceneChanger>   m_changer = nullptr;
        std::list<ScenePtr>             m_scenes;
    };
}