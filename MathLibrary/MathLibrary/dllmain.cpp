// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <string>
/*
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}*/
/*DWORD WINAPI MainThread(LPVOID param) {
    while (true) {
        if (GetAsyncKeyState(VK_F6) & 0x80000) {
            MessageBoxA(NULL,"Hello", "Hello", MB_OK);
        }
        Sleep(100);

    }
    return 0;
}

bool WINAPI DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        MessageBoxA(NULL, "Dll injected", "Dll injected", MB_OK);
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
    return TRUE;
}*/
// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        MessageBox(0, L"Hello From testlib!", L"Hello", MB_ICONINFORMATION);

    return TRUE;
}
__declspec(dllexport) void CALLBACK myFunc(int a)
{
    MessageBox(0, L"RUNDLL32.EXE", L"RUNDLL32.EXE", MB_ICONINFORMATION);
}
extern "C" __declspec(dllexport) void mydllmain(int a)
{
    MessageBox(0, L"Hey there again!", 0, 0);
}