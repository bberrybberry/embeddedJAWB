#include "UART.h"



UART::UART(int baudIn, int byteSizeIn, int stopBitsIn, int parityIn) {
	baud = baudIn;
	byteSize = byteSizeIn;
	stopBits = stopBitsIn;
	parity = parityIn;
}

bool UART::UARTInit(char* COMport) {
	serial = CreateFileA(COMport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (serial == INVALID_HANDLE_VALUE) {
		CloseHandle(serial);
		return false;
	}
	return true;
}

bool UART::configUART()
{
	serialParams.DCBlength = sizeof(serialParams);
	if (!GetCommState(serial, &serialParams)) {
		CloseHandle(serial);
		return false;
	}

	serialParams.BaudRate = baud;
	serialParams.ByteSize = byteSize;
	serialParams.StopBits = stopBits;
	serialParams.Parity = parity;

	if (!SetCommState(serial, &serialParams)) {
		CloseHandle(serial);
		return false;
	}

	return true;
}

bool UART::configTimeouts()
{
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(serial, &timeouts)) {
		CloseHandle(serial);
		return false;
	}

	return true;
}

bool UART::sendData(char* data, DWORD bytesToWrite) {

	if (!WriteFile(serial, data, bytesToWrite, &bytesWritten, &olWrite)) {
		return false;
	}

	return true;
}

UART::~UART() {}

