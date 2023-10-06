#pragma once
#ifndef MyGLAPI
#if BUILD_SHARED
    #if DLLEXPORT
    #define MyGLAPI __declspec(dllexport)
    #else
    #define MyGLAPI __declspec(dllimport)
    #endif
#else
#define MyGLAPI
#endif
#endif

