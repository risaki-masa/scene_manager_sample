#pragma once

#include <string_view>

namespace rsk::rendering 
{
    /// <summary>
    /// 描画できる昨日のインターフェース
    /// </summary>
    class IRenderer 
    {
    public:
        /// <summary>
        /// 座標を管理する構造体
        /// </summary>
        struct Position 
        {
            int m_x = 0;
            int m_y = 0;
        };

        /// <summary>
        /// 色を管理する構造体
        /// </summary>
        struct Color
        {
            int m_red   = 0;
            int m_green = 0;
            int m_blue  = 0;
        };

        virtual void DrawString( 
            const Position&             POSITION, 
            const std::wstring_view&    STRING,
            const Color&                COLOR
        ) = 0;
    };
}