#pragma once

#include <Windows.h>

namespace rsk::message 
{
    /// <summary>
    /// ���b�Z�[�W�𔭑�����N���X
    /// </summary>
    class MessageDispatcher 
    {
    public:
        [[nodiscard]] bool Dispatch() const;
    };
}