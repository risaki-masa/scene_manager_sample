#include "Application.h"

using namespace rsk::application;

/// <summary>
/// ���s
/// </summary>
/// <returns>����ɏI�����������ʂ���l</returns>
bool Application::Run() 
{
    if ( !Initialize() )
    {
        Finalize();
        return false;
    }

    while ( true )
    {
        if ( !Update() ) break;
        Draw();
    }

    Finalize();

    return true;
}
