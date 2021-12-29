#include "MessageDispatcher.h"

using namespace rsk::message;

/// <summary>
/// メッセージを発送
/// </summary>
/// <returns>終了のメッセージが発送されたか判別する値</returns>
bool MessageDispatcher::Dispatch() const 
{
    auto info = MSG();

    while ( PeekMessage( &info, nullptr, 0, 0, PM_REMOVE ) != 0 )
    {
        const auto IS_QUIT = info.message == WM_QUIT;
        if ( IS_QUIT ) return false;

        ::TranslateMessage( &info );
        DispatchMessage( &info );
    }

    return true;
}