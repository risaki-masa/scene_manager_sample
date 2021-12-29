#include "Renderer.h"
#include <cassert>

using namespace rsk::rendering;

/// <summary>
/// 作成
/// </summary>
/// <param name="WINDOW">ウィンドウ</param>
bool Renderer::Create( const window::Window& WINDOW ) 
{
    assert( m_window_handle                 == nullptr );
    assert( m_front_device_context_handle   == nullptr );
    assert( m_back_device_context_handle    == nullptr );
    assert( m_back_bitmap                   == nullptr );

    m_window_handle                 = WINDOW.GetWindowHandle();
    m_front_device_context_handle   = ::GetDC( m_window_handle );
    if ( m_front_device_context_handle == nullptr ) return false;

    m_back_device_context_handle = ::CreateCompatibleDC( m_front_device_context_handle );
    if ( m_back_device_context_handle == nullptr ) return false;

    m_client_area = WINDOW.GetClientArea();
    m_back_bitmap = ::CreateCompatibleBitmap( 
        m_front_device_context_handle, 
        m_client_area.right, 
        m_client_area.bottom
    );

    if ( m_back_bitmap == nullptr ) return false;

    ::SelectObject( m_back_device_context_handle, m_back_bitmap );

    return true;
}

/// <summary>
/// 破棄
/// </summary>
void Renderer::Destroy() 
{
    ::DeleteObject( m_back_bitmap );
    ::ReleaseDC( m_window_handle, m_front_device_context_handle );
    ::ReleaseDC( m_window_handle, m_back_device_context_handle );

    m_back_bitmap                   = nullptr;
    m_front_device_context_handle   = nullptr;
    m_back_device_context_handle    = nullptr;
    m_window_handle                 = nullptr;
}

/// <summary>
/// バックバッファを塗りつぶす
/// </summary>
void Renderer::Clear() 
{
    ::PatBlt( 
        m_back_device_context_handle, 
        m_client_area.left, 
        m_client_area.top, 
        m_client_area.right, 
        m_client_area.bottom, 
        PATCOPY
    );
}

/// <summary>
/// バックバッファからフロントバッファへコピー
/// </summary>
void Renderer::CopyFromBackBufferToFrontBuffer() 
{
    ::BitBlt( 
        m_front_device_context_handle,
        m_client_area.left, 
        m_client_area.top, 
        m_client_area.right, 
        m_client_area.bottom, 
        m_back_device_context_handle, 
        0, 
        0, 
        SRCCOPY
    );
}

/// <summary>
/// 文字列を描画
/// </summary>
/// <param name="POSITION_X">X座標</param>
/// <param name="POSITION_Y">Y座標</param>
/// <param name="STRING">文字列</param>
/// <param name="RED">赤</param>
/// <param name="GREEN">緑</param>
/// <param name="BLUE">青</param>
void Renderer::DrawString( 
    const Position&             POSITION, 
    const std::wstring_view&    STRING,
    const Color&                COLOR
) {
    ::SetTextColor( 
        m_back_device_context_handle, 
        RGB( COLOR.m_red, COLOR.m_green, COLOR.m_blue )
    );

    TextOut( 
        m_back_device_context_handle, 
        POSITION.m_x, 
        POSITION.m_y, 
        STRING.data(), 
        STRING.length() 
    );
}