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
	/**
	 * @fn UART()
	 * @brief Default UART constructor
	 */
	UART();

	/**
	 * @fn UART(DWORD baudIn, BYTE byteSizeIn, BYTE stopBitsIn, BYTE parityIn)
	 * @param baudIn Baud rate for UART channel,
	 * @param byteSizeIn Byte size for the UART channel, typically 8 bits
	 * @param stopBitsIn Number of stop bits, typically 1 bit
	 * @param parityIn If parity is used, typically not used
	 * @brief UART constuctor 
	 */
	UART(DWORD baudIn, BYTE byteSizeIn, BYTE stopBitsIn, BYTE parityIn);
	
	/**
	 * @fn setBaudRate(DWORD baudIn)
	 * @param baudIn Baud rate
	 * @brief Sets the baud rate
	 */
	void setBaudRate(DWORD baudIn);
	/**
	 * @fn setByteSize(BYTE byteSizeIn)
	 * @param byteSizeIn Byte size
	 * @brief Sets the byte size
	 */
	void setByteSize(BYTE byteSizeIn);
	/**
	 * @fn setStopBits(BYTE stopBitsIn)
	 * @param stopBitsIn Number of stop bits
	 * @brief Sets the number of stop bits
	 */
	void setStopBits(BYTE stopBitsIn);
	/**
	 * @fn setParity(BYTE parityIn)
	 * @param parityIn Parity
	 * @brief Sets the parity
	 */
	void setParity(BYTE parityIn);

	/**
	 * @fn UARTInit(char* COMport)
	 * @param COMport COM port the UART channel will run on 
	 * @brief Initializes the UART channel at the specified COM port 
	 * with generic read and write access
	 */
	bool UARTInit(char* COMport);
	/**
	 * @fn configUART()
	 * @brief Configures the UART channel with the specified settings
	 */
	bool configUART();
	/**
	 * @fn configTimeouts()
	 * @brief Configures the timeouts for the UART channel
	 */
	bool configTimeouts();

	/**
	 * @fn sendData(char* data, DWORD bytesToWrite)
	 * @param data Char array of the data being sent
	 * @param bytesToWrite Number of bytes to write
	 * @brief Sends the data over the UART channel
	 */
	bool sendData(char* data, DWORD bytesToWrite);
	/**
	 * @fn receiveData(char* data, DWORD bytesToRead)
	 * @param data Char array of where the data will be stored
	 * @param bytesToRead Number of bytes to read
	 * @brief Receives data being sent over the UART channel
	 */
	bool receiveData(char* data, DWORD bytesToRead);

	/**
	 * @fn ~UART()
	 * @brief UART destructor
	 */
	~UART();

private:
	/**
	 * @var HANDLE serial
	 * @brief HANDLE for the serial communication
	 */
	HANDLE serial;
	/**
	 * @var COMMTIMEOUTS timeouts
	 * @brief Stores the timeout settings
	 */
	COMMTIMEOUTS timeouts;
	/**
	 * @var DCB serialParams
	 * @brief Stores the parameters for the serial communication
	 */
	DCB serialParams;

	/**
	 * @var DWORD baud
	 * @brief The baud rate used
	 */
	DWORD baud;
	/**
	 * @var BYTE byteSize
	 * @brief The byte size used
	 */
	BYTE byteSize;
	/**
	 * @var BYTE stopBits
	 * @brief The number of stop bits
	 */
	BYTE stopBits;
	/**
	 * @var BYTE parity
	 * @brief The parity used
	 */
	BYTE parity;

	/**
	 * @var DWORD bytesWritten
	 * @brief Number of bytes written
	 */
	DWORD bytesWritten;
	/**
	 * @var DWORD bytesRead
	 * @brief Number of bytes read
	 */
	DWORD bytesRead;
	/**
	 * @var OVERLAPPED olWrite
	 * @brief If the writing was overlapped from before
	 */
	OVERLAPPED olWrite;


};

