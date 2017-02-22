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
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

/**
* @def width
* @brief Width of the image from the color camera
*/
/**
* @def height
* @brief Height of the image from the color camera
*/
/**
* @def COMport
* @brief COM port that the UART will be sent to
*/


#define width		1920
#define height		1080
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
/** @var HandState rightHand[BODY_COUNT]
* @brief Contains the state of the right hand for all people
*/
/** @var HandState leftHand[BODY_COUNT]
* @brief Contains the state of the left hand for all people
*/
/** @var std::vector<BOOLEAN> trackedJoints
* @brief Vector of booleans to determine which is being tracked
*/

Joint allJoints[BODY_COUNT][JointType_Count];
HandState rightHand[BODY_COUNT];
HandState leftHand[BODY_COUNT];
std::vector<BOOLEAN> trackedJoints;


/** @var unsigned char buttonPress[BODY_COUNT]
* @brief Array of what buttons are pressed for each player
*/
unsigned char buttonPress[BODY_COUNT];

/**
 * @var IKinectSensor* sensor
 * @brief Pointer to kinect sensor
 */
/**
 * @var IMultiSourceFrameReader* reader
 * @brief Pointer to the frame reader that can take in multiple sources
 */
/**
 * @var ICoordinateMapper* mapper
 * @brief Pointer to coordinate mapper to map between sources
 */
IKinectSensor* sensor;
IMultiSourceFrameReader* reader = NULL;
ICoordinateMapper* mapper;

/**
 * @var BOOLEAN tracked
 * @brief Boolean to tell if a person is being tracked or not
 */
 /**
 * @var UINT8* colorBuffer
 * @brief Pointer to array of UINT8 data 
 */
BOOLEAN tracked = false;
UINT8* colorBuffer;


/**
* @var IColorFrame* colorFrame
* @brief Pointer to the color frame
*/
/**
* @var IColorFrameReference* colorRef
* @brief Pointer to the color frame reference
*/
/**
* @var IDepthFrame* depthFrame
* @brief Pointer to the depth frame
*/
/**
* @var IDepthFrameReference* depthRef
* @brief Pointer to the depth frame reference
*/
/**
* @var IMultSourceFrame* frame
* @brief Pointer to the multi-source frame
*/
/**
* @var IBodyFrame* bodyFrame
* @brief Pointer to the body frame
*/
/**
* @var IBodyFrameReference* bodyRef
* @brief Pointer to the body frame reference
*/
/**
* @var IBody* body
* @brief Pointer to the array of bodies
*/
IColorFrame* colorFrame = NULL;
IColorFrameReference* colorRef;
IDepthFrame* depthFrame = NULL;
IDepthFrameReference* depthRef;
IMultiSourceFrame* frame = NULL;
IBodyFrame* bodyFrame = NULL;
IBodyFrameReference* bodyRef;
IBody* body[BODY_COUNT] = { 0 };

/**
* @var Person people
* @brief Array of persons
*/
/**
* @var DCB serialParams
* @brief Settings for the serial connection
*/
Person people[BODY_COUNT];

DCB serialParams;

/**
* @fn jointToPt3f(Joint joint)
* @param joint Joint structure that contains the relative X, Y, and Z coordinates
* @brief Converts a joint position into a cv::Point3f
*/
/**
* @fn initSerial
* @brief returns HANDLE for serial communication
*/
/**
 * @fn configSerial(HANDLE* handle)
 * @param handle Pointer to the file handle for the serial port
 * @brief Congigures the serial parameters for the connection
 */
 /**
 * @fn configTimeouts(HANDLE* handle, COMMTIMEOUTS* timeouts)
 * @param handle Pointer to the file handle for the serial port
 * @param timeouts Pointer to the timeout handle corresponding with the serial port
 * @brief Congigures the timeout parameters for the connection
 */
cv::Point3f jointToPt3f(Joint joint);
HANDLE initSerial();
bool configSerial(HANDLE* handle);
bool configTimeouts(HANDLE* handle, COMMTIMEOUTS* timeouts);

/**
 * @fn pressA(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the A button has been pressed
 */
 /**
 * @fn pressB(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the B button has been pressed
 */
 /**
 * @fn pressUp(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the up button has been pressed
 */
 /**
 * @fn pressDown(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the down button has been pressed
 */
 /**
 * @fn pressLeft(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the left button has been pressed
 */
 /**
 * @fn pressRight(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the right button has been pressed
 */
 /**
 * @fn pressStart(Person player)
 * @param player Person struct that contains coordinate info
 * @brief Determines if the start button has been pressed
 */
 /**
 * @fn pressSelect(Person player)
 * @param player Person structure that contains coordinate info
 * @brief Determines if the select button has been pressed
 */
bool pressA(Person player);
bool pressB(Person player);
bool pressUp(Person player);
bool pressDown(Person player);
bool pressLeft(Person player);
bool pressRight(Person player);
bool pressStart(Person player);
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