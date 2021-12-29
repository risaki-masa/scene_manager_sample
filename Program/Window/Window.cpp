#include "Window.h"
#include <cassert>
#include <functional>

using namespace rsk::window;

/// <summary>
/// ウィンドウを作成
/// </summary>
/// <param name="NAME">名前</param>
/// <param name="WIDTH">幅</param>
/// <param name="HEIGHT">高さ</param>
/// <returns>作成が成功したか判別する値</returns>
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
/// ウィンドウを表示
/// </summary>
void Window::Show() 
{
    assert( m_window_handle != nullptr );

    ::ShowWindow    ( m_window_handle, SW_SHOW );
    ::UpdateWindow  ( m_window_handle );
}

/// <summary>
/// ウィンドウを破棄
/// </summary>
void Window::Destroy() 
{
    if ( m_window_handle == nullptr ) return;

    ::DestroyWindow( m_window_handle );
    m_window_handle = nullptr;

    RemoveClass();
}

/// <summary>
/// クライアント領域を取得
/// </summary>
/// <returns>クライアント領域</returns>
RECT Window::GetClientArea() const 
{
    auto area = RECT();
    ::GetClientRect( m_window_handle, &area );

    return area;
}

/// <summary>
/// ウィンドウハンドルを取得
/// </summary>
/// <returns>ウィンドウハンドル</returns>
HWND Window::GetWindowHandle() const 
{
    return m_window_handle;
}

/// <summary>
/// ウィンドウクラスを追加
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
/// ウィンドウクラスを除く
/// </summary>
void Window::RemoveClass() 
{
    if ( m_name.empty() ) return;

    UnregisterClass( m_name.c_str(), m_instance_handle );

    m_instance_handle = nullptr;
    m_name.clear();
}

/// <summary>
/// メッセージを応答する時の処理
/// </summary>
/// <param name="window_handle">ウィンドウハンドル</param>
/// <param name="message_type">メッセージの種類</param>
/// <param name="additional_data_1">追加情報1</param>
/// <param name="additional_data_2">追加情報2</param>
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
/// メッセージを受信した時の処理を取得
/// </summary>
/// <returns>メッセージを受信した時の処理</returns>
WNDPROC Window::GetOnReceivedMessage() 
{
    return []( 
        HWND    window_handle, 
        UINT    message_type, 
        WPARAM  additional_data_1, 
        LPARAM  additional_data_2 
    ) {
        auto window = reinterpret_cast<Window*>( GetWindowLongPtr( window_handle, GWLP_USERDATA ) );

        // WM_CREATE以前のメッセージは、まだユーザーデータにウィンドウが設定できてないため、
        // デフォルトのプロシージャで処理
        if ( window == nullptr ) 
        {
            return DefWindowProc( window_handle, message_type, additional_data_1, additional_data_2 );
        }

        return window->OnRespondMessage( window_handle, message_type, additional_data_1, additional_data_2 );
    };
}

/// <summary>
/// カーソルハンドルを取得
/// </summary>
/// <returns>カーソルハンドル</returns>
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