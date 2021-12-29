#pragma once

#include <chrono>

namespace rsk::time 
{
    /// <summary>
    /// フレームレートを制御するクラス
    /// </summary>
    class FrameRateController 
    {
    public:
        FrameRateController( const int FPS = 60 );
        void Control();
    private:
        using Clock         = std::chrono::steady_clock;
        using TimePoint     = Clock::time_point;
        using Microseconds  = std::chrono::microseconds;

        TimePoint       m_start_time;
        Microseconds    m_required_time;
    };
}