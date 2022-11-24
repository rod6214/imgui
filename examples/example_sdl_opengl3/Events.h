#pragma once

#include <SDL_stdinc.h>

namespace POTYPROM
{
    typedef struct _WINDOWS_DATA
    {
        Uint32 timestamp;
        Uint32 windowID;
    } EventInfo_t;

    typedef struct _FOCUS_ARGS
    {
    } FocusArgs_t;
}
