#include "Window.h"
#include <cassert>
#include <functional>

using namespace rsk::window;

/// <summary>
/// �E�B���h�E���쐬
/// </summary>
/// <param name="NAME">���O</param>
/// <param name="WIDTH">��</param>
/// <param name="HEIGHT">����</param>
/// <returns>�쐬���������������ʂ���l</returns>
bool Window::Create( const wchar_t* NAME, const int WIDTH, const int HEIGHT ) 
{
    assert( m_instance_handle   == nullptr );
    assert( m_window_handle     == nullptr );
    assert( m_name.empty() );

    m_instance_handle   = GetModuleHandle( nullptr );
    m_name              = NAME;

    if ( !AddClass() ) return false;

    m_window_handle = CreateWindow(
        NAME,
        NAME,
        WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIDTH,
        HEIGHT,
        nullptr,
        nullptr,
        m_instance_handle,
        nullptr
    );

    if ( m_window_handle == nullptr ) return false;
    SetWindowLongPtr( m_window_handle, GWLP_USERDATA, reinterpret_cast<LONG>( this ) );

    return true;
}

/// <summary>
/// �E�B���h�E��\��
/// </summary>
void Window::Show() 
{
    assert( m_window_handle != nullptr );

    ::ShowWindow    ( m_window_handle, SW_SHOW );
    ::UpdateWindow  ( m_window_handle );
}

/// <summary>
/// �E�B���h�E��j��
/// </summary>
void Window::Destroy() 
{
    if ( m_window_handle == nullptr ) return;

    ::DestroyWindow( m_window_handle );
    m_window_handle = nullptr;

    RemoveClass();
}

/// <summary>
/// �N���C�A���g�̈���擾
/// </summary>
/// <returns>�N���C�A���g�̈�</returns>
RECT Window::GetClientArea() const 
{
    auto area = RECT();
    ::GetClientRect( m_window_handle, &area );

    return area;
}

/// <summary>
/// �E�B���h�E�n���h�����擾
/// </summary>
/// <returns>�E�B���h�E�n���h��</returns>
HWND Window::GetWindowHandle() const 
{
    return m_window_handle;
}

/// <summary>
/// �E�B���h�E�N���X��ǉ�
/// </summary>
/// <returns></returns>
bool Window::AddClass() 
{
    const auto WINDOW_CLASS = WNDCLASSEXW
    {
        .cbSize         = sizeof( WNDCLASSEXW ),
        .style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        .lpfnWndProc    = GetOnReceivedMessage(),
        .cbClsExtra     = 0,
        .cbWndExtra     = 0,
        .hInstance      = m_instance_handle,
        .hIcon          = nullptr,
        .hCursor        = GetCursorHandle(),
        .hbrBackground  = static_cast<HBRUSH>( ::GetStockObject( WHITE_BRUSH ) ),
        .lpszMenuName   = nullptr,
        .lpszClassName  = m_name.c_str(),
        .hIconSm        = nullptr,
    };

    return ::RegisterClassExW( &WINDOW_CLASS ) != 0;
}

/// <summary>
/// �E�B���h�E�N���X������
/// </summary>
void Window::RemoveClass() 
{
    if ( m_name.empty() ) return;

    UnregisterClass( m_name.c_str(), m_instance_handle );

    m_instance_handle = nullptr;
    m_name.clear();
}

/// <summary>
/// ���b�Z�[�W���������鎞�̏���
/// </summary>
/// <param name="window_handle">�E�B���h�E�n���h��</param>
/// <param name="message_type">���b�Z�[�W�̎��</param>
/// <param name="additional_data_1">�ǉ����1</param>
/// <param name="additional_data_2">�ǉ����2</param>
/// <returns></returns>
LRESULT CALLBACK Window::OnRespondMessage( 
    HWND    window_handle, 
    UINT    message_type, 
    WPARAM  additional_data_1, 
    LPARAM  additional_data_2 
) {
    switch ( message_type )
    {
    case WM_DESTROY:
        ::PostQuitMessage( 0 );

        m_window_handle = nullptr;
        RemoveClass();
        break;
    default:
        return DefWindowProc( window_handle, message_type, additional_data_1, additional_data_2 );
    }

    return 0;
}

/// <summary>
/// ���b�Z�[�W����M�������̏������擾
/// </summary>
/// <returns>���b�Z�[�W����M�������̏���</returns>
WNDPROC Window::GetOnReceivedMessage() 
{
    return []( 
        HWND    window_handle, 
        UINT    message_type, 
        WPARAM  additional_data_1, 
        LPARAM  additional_data_2 
    ) {
        auto window = reinterpret_cast<Window*>( GetWindowLongPtr( window_handle, GWLP_USERDATA ) );

        // WM_CREATE�ȑO�̃��b�Z�[�W�́A�܂����[�U�[�f�[�^�ɃE�B���h�E���ݒ�ł��ĂȂ����߁A
        // �f�t�H���g�̃v���V�[�W���ŏ���
        if ( window == nullptr ) 
        {
            return DefWindowProc( window_handle, message_type, additional_data_1, additional_data_2 );
        }

        return window->OnRespondMessage( window_handle, message_type, additional_data_1, additional_data_2 );
    };
}

/// <summary>
/// �J�[�\���n���h�����擾
/// </summary>
/// <returns>�J�[�\���n���h��</returns>
HCURSOR Window::GetCursorHandle() 
{
    const auto CURSOR_HANDLE = LoadImage(
        nullptr,
        IDC_ARROW,
        IMAGE_CURSOR,
        0,
        0,
        LR_DEFAULTSIZE | LR_SHARED
    );

    return static_cast<HCURSOR>( CURSOR_HANDLE );
}