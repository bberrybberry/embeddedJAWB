/**
* @file
* @brief Kinect code.
* Will be improved and made more modular soon.
*
*/
/**
* 
*/
#define USE_KINECT
//#define USE_KEYBOARD
 //#define USE_HTTP
//#define USE_MULTIPLAYER

#ifdef USE_KINECT
#include <Kinect.h>
#include <Windows.h>
#include <Ole2.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#endif

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <conio.h>
#include "UART.h"
#include "HTTP.h"

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
 * @def P1_U_PRESS
 * @brief String to send for player 1 pressing up
 */
#define P1_U_PRESS	"__SL_P_UKC=P1_UBTN_PRESS"
 /**
  * @def P1_D_PRESS
  * @brief String to send for player 1 pressing down
  */
#define P1_D_PRESS	"__SL_P_UKC=P1_DBTN_PRESS"
 /**
  * @def P1_L_PRESS
  * @brief String to send for player 1 pressing left
  */
#define P1_L_PRESS	"__SL_P_UKC=P1_LBTN_PRESS"
 /**
  * @def P1_R_PRESS
  * @brief String to send for player 1 pressing right
  */
#define P1_R_PRESS	"__SL_P_UKC=P1_RBTN_PRESS"
 /**
  * @def P1_A_PRESS
  * @brief String to send for player 1 pressing A
  */
#define P1_A_PRESS	"__SL_P_UKC=P1_ABTN_PRESS"
 /**
  * @def P1_B_PRESS
  * @brief String to send for player 1 pressing B
  */
#define P1_B_PRESS	"__SL_P_UKC=P1_BBTN_PRESS"
 /**
  * @def P1_S_PRESS
  * @brief String to send for player 1 pressing start
  */
#define P1_S_PRESS	"__SL_P_UKC=P1_SBTN_PRESS"
 /**
  * @def P1_E_PRESS
  * @brief String to send for player 1 pressing select
  */
#define P1_E_PRESS	"__SL_P_UKC=P1_EBTN_PRESS"

/**
 * @def P2_U_PRESS
 * @brief String to send for player 2 pressing up
 */
#define P2_U_PRESS	"__SL_P_UKC=P2_UBTN_PRESS"
 /**
  * @def P2_D_PRESS
  * @brief String to send for player 2 pressing down
  */
#define P2_D_PRESS	"__SL_P_UKC=P2_DBTN_PRESS"
 /**
  * @def P2_L_PRESS
  * @brief String to send for player 2 pressing left
  */
#define P2_L_PRESS	"__SL_P_UKC=P2_LBTN_PRESS"
 /**
  * @def P2_R_PRESS
  * @brief String to send for player 2 pressing right
  */
#define P2_R_PRESS	"__SL_P_UKC=P2_RBTN_PRESS"
 /**
  * @def P2_A_PRESS
  * @brief String to send for player 2 pressing A
  */
#define P2_A_PRESS	"__SL_P_UKC=P2_ABTN_PRESS"
 /**
  * @def P2_B_PRESS
  * @brief String to send for player 2 pressing B
  */
#define P2_B_PRESS	"__SL_P_UKC=P2_BBTN_PRESS"
 /**
  * @def P2_S_PRESS
  * @brief String to send for player 2 pressing start
  */
#define P2_S_PRESS	"__SL_P_UKC=P2_SBTN_PRESS"
 /**
  * @def P2_E_PRESS
  * @brief String to send for player 2 pressing select
  */
#define P2_E_PRESS	"__SL_P_UKC=P2_EBTN_PRESS"

/**
 * @def P3_U_PRESS
 * @brief String to send for player 3 pressing up
 */
#define P3_U_PRESS	"__SL_P_UKC=P3_UBTN_PRESS"
 /**
 * @def P3_D_PRESS
 * @brief String to send for player 3 pressing down
 */
#define P3_D_PRESS	"__SL_P_UKC=P3_DBTN_PRESS"
 /**
 * @def P3_L_PRESS
 * @brief String to send for player 3 pressing left
 */
#define P3_L_PRESS	"__SL_P_UKC=P3_LBTN_PRESS"
 /**
 * @def P3_R_PRESS
 * @brief String to send for player 3 pressing right
 */
#define P3_R_PRESS	"__SL_P_UKC=P3_RBTN_PRESS"
 /**
 * @def P3_A_PRESS
 * @brief String to send for player 3 pressing A
 */
#define P3_A_PRESS	"__SL_P_UKC=P3_ABTN_PRESS"
 /**
 * @def P3_B_PRESS
 * @brief String to send for player 3 pressing B
 */
#define P3_B_PRESS	"__SL_P_UKC=P3_BBTN_PRESS"
 /**
 * @def P3_S_PRESS
 * @brief String to send for player 3 pressing start
 */
#define P3_S_PRESS	"__SL_P_UKC=P3_SBTN_PRESS"
 /**
 * @def P3_E_PRESS
 * @brief String to send for player 3 pressing select
 */
#define P3_E_PRESS	"__SL_P_UKC=P3_EBTN_PRESS"

/**
 * @def P4_U_PRESS 
 * @brief String to send for player 4 pressing up
 */
#define P4_U_PRESS	"__SL_P_UKC=P4_UBTN_PRESS"
 /**
 * @def P4_D_PRESS
 * @brief String to send for player 4 pressing down
 */
#define P4_D_PRESS	"__SL_P_UKC=P4_DBTN_PRESS"
 /**
 * @def P4_L_PRESS
 * @brief String to send for player 4 pressing left
 */
#define P4_L_PRESS	"__SL_P_UKC=P4_LBTN_PRESS"
 /**
 * @def P4_R_PRESS
 * @brief String to send for player 4 pressing right
 */
#define P4_R_PRESS	"__SL_P_UKC=P4_RBTN_PRESS"
 /**
 * @def P4_A_PRESS
 * @brief String to send for player 4 pressing A
 */
#define P4_A_PRESS	"__SL_P_UKC=P4_ABTN_PRESS"
 /**
 * @def P4_B_PRESS
 * @brief String to send for player 4 pressing B
 */
#define P4_B_PRESS	"__SL_P_UKC=P4_BBTN_PRESS"
 /**
 * @def P4_S_PRESS
 * @brief String to send for player 4 pressing start
 */
#define P4_S_PRESS	"__SL_P_UKC=P4_SBTN_PRESS"
 /**
 * @def P4_E_PRESS
 * @brief String to send for player 4 pressing select
 */
#define P4_E_PRESS	"__SL_P_UKC=P4_EBTN_PRESS"


#ifdef USE_KINECT
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
	float threshold; /**< Threshold for what determines a button press*/
	char addr;
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
char buttonPress[BODY_COUNT];
/**
 * @var unsigned char prevButtonPress[BODY_COUNT]
 * @brief Array of the previous button presses
 */
char prevButtonPress[BODY_COUNT] = { 0 };



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

#endif
/**
* @var DCB serialParams
* @brief Settings for the serial connection
*/
DCB serialParams;
/**
 * @var UART uart(CBR_115200, 8, ONESTOPBIT, NOPARITY)
 * @brief Creates the uart object that sends and receives data.
 * Uses a baud rate of 115200, byte size of 8, one stop bit, and no parity
 */
UART uart(CBR_115200, 8, ONESTOPBIT, NOPARITY);

/**
 * @var http
 * @brief Instantiation of HTTP class
 */
HTTP http;

#ifdef USE_KINECT

/**
* @fn jointToPt3f(Joint joint)
* @param joint Joint structure that contains the relative X, Y, and Z coordinates
* @brief Converts a joint position into a cv::Point3f
*/
cv::Point3f jointToPt3f(Joint joint);

/**
 * @fn pt3fToCSP(cv::Point3f point)
 * @param point OpenCV Point3f point
 * @brief Converts an OpenCV Point3f point to a Microsoft CamerSpacePoint
 */
CameraSpacePoint pt3fToCSP(cv::Point3f point);
/**
 * @fn getDistance(Joint joints[25], int j1, int j2)
 * @param joints All joints for a person
 * @param j1 First joint
 * @param j2 Second joint
 * @brief Gets the distance between two joints, used for the threshold of a button press
 */
float getDistance(Joint joints[25], int j1, int j2);


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
 * @fn getAddressofPlayers(Person* players[BODY_COUNT])
 * @param player All players in view
 * @brief Finds who is player 1, 2, 3, etc. based on the position
 * from left to right facing the Kinect
 */
void getAddressofPlayers(Person* players);

/**
* @fn pollButtons(Person player)
* @param player Person struct that contains coordinate info
* @brief Returns 8-bit button field of buttons that have been pressed
*/
unsigned char pollButtons(Person player);

/**
 * @fn drawJoints()
 * @brief Draws the tracked joints of all players
 */

cv::Mat drawJoints(cv::Mat color);

/**
 * @fn printButtons(int i)
 * @param i Index of the current player
 * @brief Simply prints when a button is pressed 
 */
void printButtons(int i);
#endif
/**
 * @fn sendInit()
 * @brief Sends an initial message to the Controller Client Module for a handshake
 */
bool sendInit();
/**
 * @fn sendButtonPress(char address, char* presses)
 * @param address Address of the player with these button presses
 * @param presses Unsigned char that contains the button presses in the packet order
 * @brief Sends the button update and events to the Controller Client Module for 
 * the player at that address
 */
bool sendButtonPress(char address, char* presses);
/**
 ** 
 * @fn receiveHS()
 * @brief Returns true if the microcontroller responds to initialization
 */
bool receiveHS();