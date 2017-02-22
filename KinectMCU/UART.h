#include <iostream>
#include <stdio.h>
#include <Windows.h>


class UART
{
public:
	UART(int baudIn, int byteSizeIn, int stopBitsIn, int parityIn);
	
	bool UARTInit(char* COMport);
	bool configUART();
	bool configTimeouts();

	bool sendData(char* data, DWORD bytesToWrite);

	~UART();

private:
	HANDLE serial;
	COMMTIMEOUTS timeouts;
	DCB serialParams;

	int baud, byteSize, stopBits;
	bool parity;

	DWORD bytesWritten;
	OVERLAPPED olWrite;


};

