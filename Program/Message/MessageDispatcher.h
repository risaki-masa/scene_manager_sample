#pragma once

#include <Windows.h>

namespace rsk::message 
{
    /// <summary>
    /// メッセージを発送するクラス
    /// </summary>
    class MessageDispatcher 
    {
    public:
        [[nodiscard]] bool Dispatch() const;
    };
}