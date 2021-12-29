#include "FrameRateController.h"
#include <thread>

using namespace rsk::time;
using namespace std::literals::chrono_literals;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="FPS">1�b�Ԃɂ�����t���[����</param>
FrameRateController::FrameRateController( const int FPS ) :

    m_required_time( 1000000us / FPS )

{
}

/// <summary>
/// ����
/// </summary>
void FrameRateController::Control() 
{
    const auto END_TIME     = Clock::now();
    const auto ELAPSED_TIME = std::chrono::duration_cast<Microseconds>( END_TIME - m_start_time );
    const auto SHOULD_WAIT  = ELAPSED_TIME < m_required_time;
    const auto WAITING_TIME = SHOULD_WAIT ? m_required_time - ELAPSED_TIME : Microseconds::zero();
    
    m_start_time = END_TIME + WAITING_TIME;
    if ( SHOULD_WAIT ) std::this_thread::sleep_until( m_start_time );
}