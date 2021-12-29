#pragma once

#include <string_view>

namespace rsk::rendering 
{
    /// <summary>
    /// �`��ł������̃C���^�[�t�F�[�X
    /// </summary>
    class IRenderer 
    {
    public:
        /// <summary>
        /// ���W���Ǘ�����\����
        /// </summary>
        struct Position 
        {
            int m_x = 0;
            int m_y = 0;
        };

        /// <summary>
        /// �F���Ǘ�����\����
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