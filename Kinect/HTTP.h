

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinInet.h>
#include <cstdlib>

#pragma comment (lib, "WinInet.lib")
#pragma comment (lib, "urlmon.lib")

#define POST	1
#define GET		0

class HTTP
{
public:
	HTTP();

	void Request(int method, LPCSTR host, LPCSTR url, LPCSTR header, LPSTR data);
	
	~HTTP();
};

