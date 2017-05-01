/**
 *  @file
 *  
 *  @brief This code was taken from https://securityblog.gr/1823/http-post-and-get-requests-with-wininet-and-c/
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinInet.h>
#include <cstdlib>

#pragma comment (lib, "WinInet.lib")
#pragma comment (lib, "urlmon.lib")

/**
 * @def POST
 * @brief Passed into Request funtion as POST method
 */
#define POST	1

/**
 * @def GET
 * @brief Passed into Request function as GET method
 */
#define GET		0

/**
 *  HTTP Class in order to communicate with the CC3200 wirelessly
 */
class HTTP
{
public:
	/**
	 *  @fn HTTP()
	 *  @brief HTTP class constructor
	 */
	HTTP();

	/**
	 *  @fn Request(int method, LPCSTR host, LPCSTR url, LPCSTR header, LPSTR data)
	 *  @param method Either a POST or GET request
	 *  @param host URL of the host 
	 *  @param url URL being accessed
	 *  @param header Header of the HTTP request
	 *  @param data Data being sent to the server
	 *  @brief Sends an HTTP request 
	 */
	void Request(int method, LPCSTR host, LPCSTR url, LPCSTR header, LPSTR data);
	
	/**
	 *  @fn ~HTTP()
	 *  @brief HTTP class deconstructor
	 */
	~HTTP();
};

