/**
 * @file
 * @brief Header file for the UART class
 */
#include <iostream>
#include <stdio.h>
#include <Windows.h>

/**
 * UART class contains the functions for communicating with serial
 * to a COM port
 */
class UART
{
public:
	UART();
	UART(DWORD baudIn, BYTE byteSizeIn, BYTE stopBitsIn, BYTE parityIn);
	
	void setBaudRate(DWORD baudIn);
	void setByteSize(BYTE byteSizeIn);
	void setStopBits(BYTE stopBitsIn);
	void setParity(BYTE parityIn);

	bool UARTInit(char* COMport);
	bool configUART();
	bool configTimeouts();

	bool sendData(char* data, DWORD bytesToWrite);
	bool receiveData(char* data, DWORD bytesToRead);
	~UART();

private:
	HANDLE serial;
	COMMTIMEOUTS timeouts;
	DCB serialParams;

	DWORD baud;
	BYTE byteSize, stopBits, parity;

	DWORD bytesWritten;
	DWORD bytesRead;
	OVERLAPPED olWrite;


};

