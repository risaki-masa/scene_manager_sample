#include "Renderer.h"
#include <cassert>

using namespace rsk::rendering;

/// <summary>
/// �쐬
/// </summary>
/// <param name="WINDOW">�E�B���h�E</param>
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
/// �j��
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
/// �o�b�N�o�b�t�@��h��Ԃ�
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
/// �o�b�N�o�b�t�@����t�����g�o�b�t�@�փR�s�[
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
/// �������`��
/// </summary>
/// <param name="POSITION_X">X���W</param>
/// <param name="POSITION_Y">Y���W</param>
/// <param name="STRING">������</param>
/// <param name="RED">��</param>
/// <param name="GREEN">��</param>
/// <param name="BLUE">��</param>
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