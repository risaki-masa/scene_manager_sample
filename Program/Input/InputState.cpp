#include "InputState.h"

using namespace rsk::input;

/// <summary>
/// 更新
/// </summary>
/// <returns>更新に成功したか判別する値</returns>
bool InputState::Update() 
{
    BYTE state[ MAX_KEY_COUNT ] = {};
    if ( !GetKeyboardState( state ) ) return false;

    for ( int i = 0; i < MAX_KEY_COUNT; ++i )
    {
        const auto IS_PRESSING              = ( state[i] & MOST_SIGNIFICANT_BIT ) != 0;
        const auto IS_PRESSING_IN_PREVIOUS  = m_is_pressing_list[ i ];

        m_is_pressed_list [ i ] = IS_PRESSING ? !IS_PRESSING_IN_PREVIOUS : false;
        m_is_pressing_list[ i ] = IS_PRESSING;
        m_is_released_list[ i ] = IS_PRESSING ? false : IS_PRESSING_IN_PREVIOUS;
    }

    return true;
}

/// <summary>
/// キーを押したか判別する値を取得
/// </summary>
/// <param name="CODE">キーコード</param>
/// <returns>キーを押したか判別する値</returns>
bool InputState::IsPressed( const VirtualKeyCode CODE ) const
{
    return m_is_pressed_list[ static_cast<int>( CODE ) ];
}

/// <summary>
/// キーを押しているか判別する値を取得
/// </summary>
/// <param name="CODE">キーコード</param>
/// <returns>キーを押しているか判別する値</returns>
bool InputState::IsPressing( const VirtualKeyCode CODE ) const
{
    return m_is_pressing_list[ static_cast<int>( CODE ) ];
}

/// <summary>
/// キーを離したか判別する値を取得
/// </summary>
/// <param name="CODE">キーコード</param>
/// <returns>キーを離したか判別する値</returns>
bool InputState::IsReleased( const VirtualKeyCode CODE ) const
{
    return m_is_released_list[ static_cast<int>( CODE ) ];
}
