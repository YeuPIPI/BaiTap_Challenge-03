// MathClient.cpp : Client app for MathLibrary DLL.
// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include <iostream>
#include "MathLibrary.h"
#include <Windows.h>
#include <TlHelp32.h>
using namespace std;
DWORD MyGetProcessId(LPCTSTR ProcessName) // non-conflicting function name
{
    PROCESSENTRY32 pt;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt)) { // must call this first
        do {
            if (!lstrcmpi(pt.szExeFile, ProcessName)) {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap); // close handle on failure
    return 0;
}
int GetPID(const wchar_t* target) {
    DWORD pID = 0;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(hsnap, &pe32)) { // must call this first
        do {
            if (wcscmp(pe32.szExeFile, target)) {
                CloseHandle(hsnap);
                pID = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hsnap, &pe32));
    }
    CloseHandle(hsnap);
    return pID;// close handle on failur
}
int main()
{
    ////Bai 2
    /////Hi_Im_a_DLL();
    // /Bai3
    //Print_String("hello");
    //Write_File("C://Users//duyhu//source//repos//MathClient//Test.txt");
    //return 0;
    //E:\AOE\game-de-che-1\game-de-che-1\Empiresx.exe
    //const wchar_t* process = L"Empriesx.exe";
    //DWORD PID = GetPID(process);
    /*DWORD pid = MyGetProcessId(TEXT("Empiresx.exe"));
    if (pid == 0) { printf("error 1"); getchar(); }//error
    char dll[] = "MathLibrary.dll";
    char dllPath[MAX_PATH] = { 0 };
    GetFullPathNameA(dll, MAX_PATH, dllPath, NULL);
    HANDLE hHandle = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION |PROCESS_VM_OPERATION |PROCESS_VM_WRITE |PROCESS_VM_READ,FALSE, pid);
    LPVOID dllPathAddr = VirtualAllocEx(hHandle,NULL,strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
    WriteProcessMemory(hHandle,dllPathAddr,dllPath,strlen(dllPath) + 1,NULL);
    HANDLE h_rThread = CreateRemoteThread(hHandle, NULL, NULL,(LPTHREAD_START_ROUTINE)LoadLibraryA,dllPathAddr, 0, NULL);
    WaitForSingleObject(h_rThread, INFINITE);
    CloseHandle(h_rThread);
    VirtualFreeEx(hHandle, dllPathAddr, 0, MEM_RELEASE);
    CloseHandle(hHandle);
    return 0;
    */
    ///Bai4
    LPCSTR DllPath = "C://Users//duyhu//source//repos//MathClient//x64//Debug//MathLibrary.dll"; // The Path to our DLL

    HWND hwnd = FindWindowA(NULL, "Command Prompt"); // HWND (Windows window) by Window Name
    DWORD procID; // A 32-bit unsigned integer, DWORDS are mostly used to store Hexadecimal Addresses
    GetWindowThreadProcessId(hwnd, &procID); // Getting our Process ID, as an ex. like 000027AC
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID); // Opening the Process with All Access

    // Allocate memory for the dllpath in the target process, length of the path string + null terminator
    LPVOID pDllPath = VirtualAllocEx(handle, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

    // Write the path to the address of the memory we just allocated in the target process
    WriteProcessMemory(handle, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);

    // Create a Remote Thread in the target process which calls LoadLibraryA as our dllpath as an argument -> program loads our dll
    HANDLE hLoadThread = CreateRemoteThread(handle, 0, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0, 0);

    WaitForSingleObject(hLoadThread, INFINITE); // Wait for the execution of our loader thread to finish

    cout << "Dll path allocated at: " << hex << pDllPath << endl;
    cin.get();

    VirtualFreeEx(handle, pDllPath, strlen(DllPath) + 1, MEM_RELEASE); // Free the memory allocated for our dll path

    return 0;
}