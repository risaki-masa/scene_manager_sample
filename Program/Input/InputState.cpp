#include "InputState.h"

using namespace rsk::input;

/// <summary>
/// �X�V
/// </summary>
/// <returns>�X�V�ɐ������������ʂ���l</returns>
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
/// �L�[�������������ʂ���l���擾
/// </summary>
/// <param name="CODE">�L�[�R�[�h</param>
/// <returns>�L�[�������������ʂ���l</returns>
bool InputState::IsPressed( const VirtualKeyCode CODE ) const
{
    return m_is_pressed_list[ static_cast<int>( CODE ) ];
}

/// <summary>
/// �L�[�������Ă��邩���ʂ���l���擾
/// </summary>
/// <param name="CODE">�L�[�R�[�h</param>
/// <returns>�L�[�������Ă��邩���ʂ���l</returns>
bool InputState::IsPressing( const VirtualKeyCode CODE ) const
{
    return m_is_pressing_list[ static_cast<int>( CODE ) ];
}

/// <summary>
/// �L�[�𗣂��������ʂ���l���擾
/// </summary>
/// <param name="CODE">�L�[�R�[�h</param>
/// <returns>�L�[�𗣂��������ʂ���l</returns>
bool InputState::IsReleased( const VirtualKeyCode CODE ) const
{
    return m_is_released_list[ static_cast<int>( CODE ) ];
}
