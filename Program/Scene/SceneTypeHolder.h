#pragma once

#include <climits>

namespace rsk::scene
{
    /// <summary>
    /// シーンの種類を保持するクラス
    /// </summary>
    class SceneTypeHolder
    {
    public:
        /// <summary>
        /// 無効値を管理する列挙型
        /// </summary>
        enum 
        {
            NONE = INT_MIN,
        };

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="TYPE">種類</param>
        template<typename T>
        SceneTypeHolder( const T TYPE ) : 

            m_type( static_cast<int>( TYPE ) ) 

        {
            static_assert( std::is_enum<T>::value );
        }

        /// <summary>
        /// 種類を取得
        /// </summary>
        /// <returns>種類</returns>
        template<typename T>
        [[nodiscard]] T Get() const { return static_cast<T>( m_type ); }
    private:
        int m_type = SceneTypeHolder::NONE;
    };
}