#pragma once

#include <Windows.h>

namespace rsk::input 
{
    /// <summary>
    /// 仮想キーコードを管理する列挙型
    /// </summary>
    enum class VirtualKeyCode
    {
        NUMBER_0        = '0',
        NUMBER_1        = '1',
        NUMBER_2        = '2',
        NUMBER_3        = '3',
        NUMBER_4        = '4',
        NUMBER_5        = '5',
        NUMBER_6        = '6',
        NUMBER_7        = '7',
        NUMBER_8        = '8',
        NUMBER_9        = '9',

        A               = 'A',
        B               = 'B',
        C               = 'C',
        D               = 'D',
        E               = 'E',
        F               = 'F',
        G               = 'G',
        H               = 'H',
        I               = 'I',
        J               = 'J',
        K               = 'K',
        L               = 'L',
        M               = 'M',
        N               = 'N',
        O               = 'O',
        P               = 'P',
        Q               = 'Q',
        R               = 'R',
        S               = 'S',
        T               = 'T',
        U               = 'U',
        V               = 'V',
        W               = 'W',
        X               = 'X',
        Y               = 'Y',
        Z               = 'Z',

        SHIFT           = VK_SHIFT,
        CONTROL         = VK_CONTROL,
        ALT             = VK_MENU,
        ENTER           = VK_RETURN,
        BACKSPACE       = VK_BACK,
        DEL             = VK_DELETE,
        ESCAPE          = VK_ESCAPE,
        SPACE           = VK_SPACE,
        TAB             = VK_TAB,
        PRINT_SCREEN    = VK_SNAPSHOT,

        LEFT_ARROW      = VK_LEFT,
        RIGHT_ARROW     = VK_RIGHT,
        UP_ARROW        = VK_UP,
        DOWN_ARROW      = VK_DOWN,

        MOUSE_LEFT      = VK_LBUTTON,
        MOUSE_RIGHT     = VK_RBUTTON,
        MOUSE_MIDDLE    = VK_MBUTTON,
    };
}