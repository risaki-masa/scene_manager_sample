#pragma once

#include <string>
#include <Windows.h>

namespace rsk::window
{
    /// <summary>
    /// ウィンドウを管理するクラス
    /// </summary>
    class Window 
    {
    public:
        [[nodiscard]] bool Create( const wchar_t* NAME, const int WIDTH, const int HEIGHT );
        void Show();
        void Destroy();
        [[nodiscard]] HWND GetWindowHandle() const;
        [[nodiscard]] RECT GetClientArea() const;
    private:
        [[nodiscard]] bool AddClass();
        void RemoveClass();
        [[nodiscard]] LRESULT CALLBACK OnRespondMessage( 
            HWND    window_handle, 
            UINT    message_type, 
            WPARAM  additional_data_1, 
            LPARAM  additional_data_2 
        );

        [[nodiscard]] static WNDPROC GetOnReceivedMessage();
        [[nodiscard]] static HCURSOR GetCursorHandle();

        HINSTANCE       m_instance_handle   = nullptr;
        HWND            m_window_handle     = nullptr;
        std::wstring    m_name              = L"";
    };
}