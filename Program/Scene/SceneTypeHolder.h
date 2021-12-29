#pragma once

#include <climits>

namespace rsk::scene
{
    /// <summary>
    /// �V�[���̎�ނ�ێ�����N���X
    /// </summary>
    class SceneTypeHolder
    {
    public:
        /// <summary>
        /// �����l���Ǘ�����񋓌^
        /// </summary>
        enum 
        {
            NONE = INT_MIN,
        };

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        /// <param name="TYPE">���</param>
        template<typename T>
        SceneTypeHolder( const T TYPE ) : 

            m_type( static_cast<int>( TYPE ) ) 

        {
            static_assert( std::is_enum<T>::value );
        }

        /// <summary>
        /// ��ނ��擾
        /// </summary>
        /// <returns>���</returns>
        template<typename T>
        [[nodiscard]] T Get() const { return static_cast<T>( m_type ); }
    private:
        int m_type = SceneTypeHolder::NONE;
    };
}