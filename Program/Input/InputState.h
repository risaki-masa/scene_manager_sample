#pragma once

#include <array>
#include "VirtualKeyCode.h"

namespace rsk::input 
{
    /// <summary>
    /// “ü—Íó‘Ô‚ğŠÇ—‚·‚éƒNƒ‰ƒX
    /// </summary>
    class InputState 
    {
    public:
        [[nodiscard]] bool Update();
        [[nodiscard]] bool IsPressed  ( const VirtualKeyCode CODE ) const;
        [[nodiscard]] bool IsPressing ( const VirtualKeyCode CODE ) const;
        [[nodiscard]] bool IsReleased ( const VirtualKeyCode CODE ) const;
    private:
        static const int            MAX_KEY_COUNT           = 256;
        static const unsigned int   MOST_SIGNIFICANT_BIT    = 0x80;

        using StateList = std::array<bool, MAX_KEY_COUNT>;

        StateList m_is_pressed_list     = {};
        StateList m_is_pressing_list    = {};
        StateList m_is_released_list    = {};
    };
}