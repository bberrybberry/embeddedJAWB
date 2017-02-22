/**
* @file
* @brief Kinect code.
* Will be improved and made more modular soon.
*
*/
/**
* @mainpage Kinect 2 Controller
*/

#include <Kinect.h>
#include <Windows.h>
#include <Ole2.h>
#include <stdio.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "UART.h"

/**
* @def width
* @brief Width of the image from the color camera
*/
#define width		1920
/**
* @def height
* @brief Height of the image from the color camera
*/
#define height		1080
/**
* @def COMport
* @brief COM port that the UART will be sent to
*/
#define COMport		"\\\\.\\COM6"

/**
* @struct Person
* @brief Contains coordinates of the joints of all tracked people
*/
typedef struct Person {
	cv::Point3f CR; /**< Coordinate for the right elbow*/
	cv::Point3f CL; /**< Coordinate for the left elbow*/
	cv::Point3f RH; /**< Coordinate for the right hand*/
	cv::Point3f LH; /**< Coordinate for the left hand*/
	BOOLEAN RHS;/**< State of the right hand*/
	BOOLEAN LHS;/**< State of the left hand*/
};


/** @var Joint allJoints[BODY_COUNT][JointType_Count]
* @brief Multi-dimensional array that can hold up to 6 people at once
*/
Joint allJoints[BODY_COUNT][JointType_Count];
/** @var HandState rightHand[BODY_COUNT]
* @brief Contains the state of the right hand for all people
*/
HandState rightHand[BODY_COUNT];
/** @var HandState leftHand[BODY_COUNT]
* @brief Contains the state of the left hand for all people
*/
HandState leftHand[BODY_COUNT];
/** @var std::vector<BOOLEAN> trackedJoints
* @brief Vector of booleans to determine which is being tracked
*/
std::vector<BOOLEAN> trackedJoints;


/** @var unsigned char buttonPress[BODY_COUNT]
* @brief Array of what buttons are pressed for each player
* compared to prevButtonPress to get events
*/
unsigned char buttonPress[BODY_COUNT];
/**
 * @var unsigned char prevButtonPress[BODY_COUNT]
 * @brief Array of the previous button presses
 */
unsigned char prevButtonPress[BODY_COUNT] = { 0 };



/**
 * @var IKinectSensor* sensor
 * @brief Pointer to kinect sensor
 */
IKinectSensor* sensor;
/**
 * @var IMultiSourceFrameReader* reader
 * @brief Pointer to the frame reader that can take in multiple sources
 */
IMultiSourceFrameReader* reader = NULL;
/**
 * @var ICoordinateMapper* mapper
 * @brief Pointer to coordinate mapper to map between sources
 */
ICoordinateMapper* mapper;



/**
* @var float threshold
* @brief Threshold to determine if a button is being "pressed"
*/
float threshold;
/**
 * @var BOOLEAN tracked
 * @brief Boolean to tell if a person is being tracked or not
 */
BOOLEAN tracked = false;
 /**
 * @var UINT8* colorBuffer
 * @brief Pointer to array of UINT8 data 
 */
UINT8* colorBuffer;


/**
* @var IColorFrame* colorFrame
* @brief Pointer to the color frame
*/
IColorFrame* colorFrame = NULL;
/**
* @var IColorFrameReference* colorRef
* @brief Pointer to the color frame reference
*/
IColorFrameReference* colorRef;
/**
* @var IDepthFrame* depthFrame
* @brief Pointer to the depth frame
*/
IDepthFrame* depthFrame = NULL;
/**
* @var IDepthFrameReference* depthRef
* @brief Pointer to the depth frame reference
*/
IDepthFrameReference* depthRef;
/**
* @var IMultSourceFrame* frame
* @brief Pointer to the multi-source frame
*/
IMultiSourceFrame* frame = NULL;
/**
* @var IBodyFrame* bodyFrame
* @brief Pointer to the body frame
*/
IBodyFrame* bodyFrame = NULL;
/**
* @var IBodyFrameReference* bodyRef
* @brief Pointer to the body frame reference
*/
IBodyFrameReference* bodyRef;
/**
* @var IBody* body
* @brief Pointer to the array of bodies
*/
IBody* body[BODY_COUNT] = { 0 };




/**
* @var Person people
* @brief Array of persons
*/
Person people[BODY_COUNT];
/**
* @var DCB serialParams
* @brief Settings for the serial connection
*/
DCB serialParams;




/**
* @fn jointToPt3f(Joint joint)
* @param joint Joint structure that contains the relative X, Y, and Z coordinates
* @brief Converts a joint position into a cv::Point3f
*/
cv::Point3f jointToPt3f(Joint joint);
/**
* @fn initSerial
* @brief returns HANDLE for serial communication
*/
HANDLE initSerial();
/**
 * @fn configSerial(HANDLE* handle)
 * @param handle Pointer to the file handle for the serial port
 * @brief Congigures the serial parameters for the connection
 */
bool configSerial(HANDLE* handle);
 /**
 * @fn configTimeouts(HANDLE* handle, COMMTIMEOUTS* timeouts)
 * @param handle Pointer to the file handle for the serial port
 * @param timeouts Pointer to the timeout handle corresponding with the serial port
 * @brief Congigures the timeout parameters for the connection
 */
bool configTimeouts(HANDLE* handle, COMMTIMEOUTS* timeouts);





/**
 * @fn pressA(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the A button has been pressed
 */
bool pressA(Person player);
 /**
 * @fn pressB(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the B button has been pressed
 */
bool pressB(Person player);
 /**
 * @fn pressUp(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the up button has been pressed
 */
bool pressUp(Person player);
 /**
 * @fn pressDown(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the down button has been pressed
 */
bool pressDown(Person player);
 /**
 * @fn pressLeft(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the left button has been pressed
 */
bool pressLeft(Person player);
 /**
 * @fn pressRight(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the right button has been pressed
 */
bool pressRight(Person player);
 /**
 * @fn pressStart(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the start button has been pressed
 */
bool pressStart(Person player);
 /**
 * @fn pressSelect(Person player)
 * @param player Person structure that contains coordinate info
 * @brief Determines if the select button has been pressed
 */
bool pressSelect(Person player);



/**
* @fn updatePerson(Person* player, Joint joints[25])
* @param player Person struct that contains coordinate info
* @param joints Array of joints, contains coordinates
* @brief Inserts the coordinates from the joints to the player info
*/
void updatePerson(Person* player, Joint joints[25]);



/**
* @fn pollButtons(Person player)
* @param player Person struct that contains coordinate info
* @brief Returns 8-bit button field of buttons that have been pressed
*/
unsigned char pollButtons(Person player);
/**
 * @fn sendInit(HANDLE serial)
 * @param serial Configured HANDLE that carries the serial port for communication
 * @brief Sends an initial message to the Controller Client Module
 */
bool sendInit(HANDLE serial);
/**
 * @fn sendButtonPress(HANDLE serial, int address, unsigned char* presses)
 * @param serial Configured HANDLE that carries the serial port for communication
 * @param address Address of the player with these button presses
 * @param presses Unsigned char that contains the button presses in the packet order
 * @brief Sends the button update and events to the Controller Client Module for 
 * the player at that address
 */
bool sendButtonPress(HANDLE serial, int address, unsigned char* presses);