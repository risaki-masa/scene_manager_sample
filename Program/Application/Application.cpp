#include "Application.h"

using namespace rsk::application;

/// <summary>
/// é¿çs
/// </summary>
/// <returns>ê≥èÌÇ…èIóπÇµÇΩÇ©îªï Ç∑ÇÈíl</returns>
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
