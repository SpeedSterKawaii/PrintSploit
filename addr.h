#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <iostream>


#define nibber(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

typedef int(__cdecl* singletonprint)(int, const char*, ...); // Update CCV
singletonprint printerf = (singletonprint)(nibber(0x00671950)); // Update ADDR

/// Update print address every week.
