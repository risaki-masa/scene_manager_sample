#include <SDKDDKVer.h>
#include <Windows.h>
#include <tchar.h>
#include "Application/Sample/SceneManagementSample.h"

using namespace rsk::application;

int APIENTRY _tWinMain(
    _In_        HINSTANCE   instance_handle,
    _In_opt_    HINSTANCE   previous_instance_handle,
    _In_        LPTSTR      command_line_arguments,
    _In_        int         display_type
) {
    UNREFERENCED_PARAMETER( instance_handle             );
    UNREFERENCED_PARAMETER( previous_instance_handle    );
    UNREFERENCED_PARAMETER( command_line_arguments      );
    UNREFERENCED_PARAMETER( display_type                );

    auto application = sample::SceneManagementSample();
    if ( !application.Run() ) return -1;

    return 0;
}
