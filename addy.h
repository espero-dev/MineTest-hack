#pragma once
#include <corecrt_math.h>
#include <stdlib.h>
#include <iostream>
#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA("minetest"))

typedef int(__cdecl *SSS)();
SSS SS = (SSS)x(0xBB5240);

typedef int(__cdecl *SSK)(float);
SSK KA = (SSK)x(0xBB5D03);

typedef int(__cdecl *SKP)(float);
SKP KP = (SKP)x(0xBB5824);

typedef int(__cdecl *fly)();
fly f = (fly)x(0xB64D64);

//typedef int(__cdecl *SSS)(int, const char *, ...);
//SSS SS = (SSS)x(0xBB5240);

void Execute(const char * type, const char *message)
{
	if (type == "stop")
	{
		SS();
	}
	else if (type == "SSKA")
	{
		float hell;
		try {
			float myFloat = std::atof(message);
			hell = myFloat;
			std::cout << "Converted float: " << myFloat << std::endl;
		} catch (const std::invalid_argument& e) {
			std::cerr << "Invalid argument: " << e.what() << std::endl;
		}
		KA(hell);
	}
	else if (type == "fly")
	{
		f();
	}
}
