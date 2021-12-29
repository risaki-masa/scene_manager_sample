#pragma once

#include "IRenderer.h"
#include "../Window/Window.h"

namespace rsk::rendering 
{
    /// <summary>
    /// ï`âÊÇçsÇ§ÉNÉâÉX
    /// </summary>
    class Renderer : public IRenderer
    {
    public:
        [[nodiscard]] bool Create( const window::Window& WINDOW );
        void Destroy();
        void Clear();
        void CopyFromBackBufferToFrontBuffer();
        void DrawString( 
            const Position&             POSITION, 
            const std::wstring_view&    STRING,
            const Color&                COLOR 
        );
    private:
        HWND    m_window_handle                 = nullptr;
        HDC     m_front_device_context_handle   = nullptr;
        HDC     m_back_device_context_handle    = nullptr;
        HBITMAP m_back_bitmap                   = nullptr;
        RECT    m_client_area;
    };
}