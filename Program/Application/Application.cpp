#include "Application.h"

using namespace rsk::application;

/// <summary>
/// 実行
/// </summary>
/// <returns>正常に終了したか判別する値</returns>
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
