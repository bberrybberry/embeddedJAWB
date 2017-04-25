/**
 * @file
 * @brief C++ for Kinect 2 Controller
 */

#include "Main.h"
#define USE_KEYBOARD
#define USE_HTTP
//#define USE_MULTIPLAYER

/**
 * @namespace cv
 * @brief OpenCV namespace
 * 
 */
/**
 * @namespace std
 * @brief Standard namespace
 */
using namespace std;

/**
 * @fn main
 * @brief Executes the program
 */
#define BUTTON_ENTRY 2
int main() {
	char data1[64] = "__SL_P_ULD=LED1_ON";
	char data2[64] = "__SL_P_ULD=LED1_OFF";
	//while (1) {
	//	http.Request(POST, "mysimplelink.net", "No_content", "Content-Type: application/x-www-form-urlencoded", data1);
	//	Sleep(500);
	//	http.Request(POST, "mysimplelink.net", "No_content", "Content-Type: application/x-www-form-urlencoded", data2);
	//	Sleep(500);
	//}

#ifndef USE_HTTP
	char data[3] = { 0xFF, 0x00, 0x00 };
	char rxData[1];
	if (!uart.UARTInit("\\\\.\\COM6"))
		return -2;
	if (!uart.configTimeouts())
		return -3;
	if (!uart.configUART())
		return -4;

	while (!receiveHS());
	cout << "Handshake Successful";
#else
	char data[25];
#endif
#ifdef USE_KEYBOARD	
	while (1)
	{
		if (_kbhit()) {
			char press = _getch();

			switch (press) {
			case 'w':
#ifndef USE_HTTP
				data[2] = (0x01);
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_U_PRESS, sizeof(P1_U_PRESS));
#endif
				break;
			case 's':
#ifndef USE_HTTP
				data[2] = (0x01) << 1;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_D_PRESS, sizeof(P1_D_PRESS));
#endif
				break;
			case 'a':
#ifndef USE_HTTP
				data[2] = (0x01) << 2;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_L_PRESS, sizeof(P1_L_PRESS));
#endif
				break;
			case 'd':
#ifndef USE_HTTP
				data[2] = (0x01) << 3;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_R_PRESS, sizeof(P1_R_PRESS));
#endif
				break;
			case 'e':
#ifndef USE_HTTP
				data[2] = (0x01) << 4;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_A_PRESS, sizeof(P1_A_PRESS));
#endif
				break;
			case 'q': 
#ifndef USE_HTTP
				data[2] = (0x01) << 5;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_B_PRESS, sizeof(P1_B_PRESS));
#endif
				break;
			case 'r':
#ifndef USE_HTTP
				data[2] = (0x01) << 6;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_S_PRESS, sizeof(P1_S_PRESS));
#endif
				break;
			case 't':
#ifndef USE_HTTP
				data[2] = (0x01) << 7;
				data[1] = 0x00;
#else
				memcpy_s(data, sizeof(data), P1_E_PRESS, sizeof(P1_E_PRESS));
#endif
				break;
#ifdef USE_MULTIPLAYER
			case 'o':
#ifndef USE_HTTP
				data[2] = (0x01);
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_U_PRESS, sizeof(P2_U_PRESS));
#endif
				break;
			case 'l':
#ifndef USE_HTTP
				data[2] = (0x01) << 1;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_D_PRESS, sizeof(P2_D_PRESS));
#endif
				break;
			case 'k':
#ifndef USE_HTTP
				data[2] = (0x01) << 2;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_L_PRESS, sizeof(P2_L_PRESS));
#endif
				break;
			case ';':
#ifndef USE_HTTP
				data[2] = (0x01) << 3;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_R_PRESS, sizeof(P2_R_PRESS));
#endif
				break;
			case 'p':
#ifndef USE_HTTP
				data[2] = (0x01) << 4;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_A_PRESS, sizeof(P2_A_PRESS));
#endif
				break;
			case 'i':
#ifndef USE_HTTP
				data[2] = (0x01) << 5;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_B_PRESS, sizeof(P2_B_PRESS));
#endif
				break;
			case '[':
#ifndef USE_HTTP
				data[2] = (0x01) << 6;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_S_PRESS, sizeof(P2_S_PRESS));
#endif
				break;
			case ']':
#ifndef USE_HTTP
				data[2] = (0x01) << 7;
				data[1] = 0x01;
#else
				memcpy_s(data, sizeof(data), P2_E_PRESS, sizeof(P2_E_PRESS));
#endif
				break;
#endif
			default:
				data[2] = 0x00;
				break;
			}
#ifndef USE_HTTP
			uart.sendData(data, 3);
			uart.receiveData(rxData, 1);
			cout << rxData[0];
#else
			http.Request(POST, "mysimplelink.net", "No_content", "Content-Type: application/x-www-form-urlencoded", data);
#endif
		}
	}
#endif
#ifdef USE_KINECT
	if (FAILED(GetDefaultKinectSensor(&sensor)))
		return -1;

	if (sensor) {
		sensor->Open();

		if (SUCCEEDED(sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Body | FrameSourceTypes::FrameSourceTypes_Color | FrameSourceTypes::FrameSourceTypes_Depth, &reader))) {

			colorBuffer = new UINT8[width * height * 4];
			cv::Mat skeleton = cv::Mat::zeros(height, width, CV_8UC3);
			cv::Mat color = cv::Mat::zeros(height, width, CV_8UC4);
			
			
			//threshold = 0.2;
			while (1) {
				if (SUCCEEDED(reader->AcquireLatestFrame(&frame))) {
					frame->get_ColorFrameReference(&colorRef);
					colorRef->AcquireFrame(&colorFrame);
					if (colorRef)
						colorRef->Release();
					
					if (!colorFrame) {
						frame->Release();
						continue;
					}

					if (SUCCEEDED(colorFrame->CopyConvertedFrameDataToArray(width * height * 4, colorBuffer, ColorImageFormat_Rgba))) {
						color = cv::Mat(height, width, CV_8UC4, colorBuffer);
						cv::cvtColor(color, color, cv::COLOR_RGBA2BGR);

						//cv::imshow("color", color);
						//cv::waitKey(1);
					}

					colorFrame->Release();
					
					frame->get_BodyFrameReference(&bodyRef);
					bodyRef->AcquireFrame(&bodyFrame);

					if (bodyRef)
						bodyRef->Release();

					if (!bodyFrame) {
						frame->Release();
						continue;
					}

					if (SUCCEEDED(sensor->get_CoordinateMapper(&mapper))) {
						if (SUCCEEDED(bodyFrame->GetAndRefreshBodyData(BODY_COUNT, body))) {
							for (int i = 0; i < BODY_COUNT; i++) {
								body[i]->get_IsTracked(&tracked);
								if (tracked) {
									body[i]->GetJoints(JointType_Count, allJoints[i]);
									body[i]->get_HandLeftState(&leftHand[i]);
									body[i]->get_HandRightState(&rightHand[i]);
									trackedJoints.push_back(true);
								}
								else
									trackedJoints.push_back(false);
							}

							for (int i = 0; i < BODY_COUNT; i++) {
								if (!trackedJoints[i])
									continue;
								
								updatePerson(&people[i], allJoints[i]);

								if (leftHand[i] == HandState_Closed)
									people[i].LHS = true;
								else
									people[i].LHS = false;

								if (rightHand[i] == HandState_Closed)
									people[i].RHS = true;
								else
									people[i].RHS = false;
							}
						}
					}
					
					color = drawJoints(color);
					
					cv::imshow("color", color);
					cv::waitKey(1);

					frame->Release();
					bodyFrame->Release();

					for (int i = 0; i < BODY_COUNT; i++) {
						if (!trackedJoints[i]) {
							buttonPress[i] = NULL;
							continue;
						}
						buttonPress[i] = pollButtons(people[i]);
						printButtons(i);

						sendButtonPress(people[i].addr, &buttonPress[i]);
					}

					memcpy(prevButtonPress, buttonPress, sizeof(buttonPress));
					trackedJoints.clear();
				}
			}
		}
	}

	return 0;
#endif
}
#ifdef USE_KINECT
cv::Point3f jointToPt3f(Joint joint) {
	return cv::Point3f(joint.Position.X, joint.Position.Y, joint.Position.Z);
}

CameraSpacePoint pt3fToCSP(cv::Point3f point)
{
	CameraSpacePoint csp;
	csp.X = point.x;
	csp.Y = point.y;
	csp.Z = point.z;

	return csp;
}

float getDistance(Joint joints[25],  int j1, int j2) {
	return sqrtf(powf(joints[j1].Position.X - joints[j2].Position.X, 2) + powf(joints[j1].Position.Y - joints[j2].Position.Y, 2) + powf(joints[j1].Position.Z - joints[j2].Position.Z, 2));
}


bool pressA(Person player) {
	if ((player.CL.y - player.LH.y) < -player.threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressB(Person player) {
	if ((player.CL.y - player.LH.y) > player.threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressUp(Person player) {
	if ((player.CR.y - player.RH.y) < -player.threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressDown(Person player) {
	if ((player.CR.y - player.RH.y) > player.threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressLeft(Person player)
{
	if ((player.CR.x - player.RH.x) > player.threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressRight(Person player) {
	if ((player.CR.x - player.RH.x) < -player.threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressStart(Person player) {
	if ((player.CL.x - player.LH.x) > player.threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressSelect(Person player) {
	if ((player.CL.x - player.LH.x) < -player.threshold && player.LHS)
		return true;
	else
		return false;
}

void updatePerson(Person* player, Joint joints[25]) {
	player->CL = jointToPt3f(joints[JointType_ElbowLeft]);
	player->CR = jointToPt3f(joints[JointType_ElbowRight]);
	player->RH = jointToPt3f(joints[JointType_HandRight]);
	player->LH = jointToPt3f(joints[JointType_HandLeft]);

	player->threshold = getDistance(joints, JointType_ElbowLeft, JointType_HandLeft) * 0.5;
}

void getAddressofPlayers(Person* players[BODY_COUNT]) {
	float CL[BODY_COUNT];

	for (int i = 0; i < BODY_COUNT; i++) {
		if (!trackedJoints[i]) {
			CL[i] = 10;
			continue;
		}

		CL[i] = players[i]->CL.x;
	}
	
	for (unsigned char i = 0; i < BODY_COUNT; i++) {
		float maxVal = *max_element(CL, CL + BODY_COUNT);
		int minIdx = distance(CL, min_element(CL, CL + BODY_COUNT));
		players[minIdx]->addr = i + 1;
		CL[minIdx] = maxVal + 1.0f;
	}

	
}

unsigned char pollButtons(Person player) {
	unsigned char output = 0x00;
	if (pressUp(player))
		output |= (0x01);
	else
		output &= ~(0x01);

	if (pressDown(player))
		output |= (0x01 << 1);
	else
		output &= ~(0x01 << 1);

	if (pressLeft(player))
		output |= (0x01 << 2);
	else
		output &= ~(0x01 << 2);

	if (pressRight(player))
		output |= (0x01 << 3);
	else
		output &= ~(0x01 << 3);

	if (pressA(player))
		output |= (0x01 << 4);
	else
		output &= ~(0x01 << 4);

	if (pressB(player))
		output |= (0x01 << 5);
	else
		output &= ~(0x01 << 5);

	if (pressStart(player))
		output |= (0x01 << 6);
	else
		output &= ~(0x01 << 6);

	if (pressSelect(player))
		output |= (0x01 << 7);
	else
		output &= ~(0x01 << 7);

	return output;
}

cv::Mat drawJoints(cv:: Mat color) {
	
	CameraSpacePoint csp;
	ColorSpacePoint cop;
	for (int i = 0; i < BODY_COUNT; i++) {
		if (!trackedJoints[i]) {
			continue;
		}

		csp = pt3fToCSP(people[i].CL);
		mapper->MapCameraPointToColorSpace(csp, &cop);
		cv::circle(color, cv::Point((int)cop.X, (int)cop.Y) , 10, cv::Scalar(255, 255, 255));

		csp = pt3fToCSP(people[i].CR);
		mapper->MapCameraPointToColorSpace(csp, &cop);
		cv::circle(color, cv::Point((int)cop.X, (int)cop.Y), 10, cv::Scalar(255, 255, 255));

		csp = pt3fToCSP(people[i].LH);
		mapper->MapCameraPointToColorSpace(csp, &cop);

		if (people[i].LHS) {
			cv::circle(color, cv::Point((int)cop.X, (int)cop.Y), 10, cv::Scalar(0, 255, 0));
		}
		else {
			cv::circle(color, cv::Point((int)cop.X, (int)cop.Y), 10, cv::Scalar(0, 0, 255));
		}

		csp = pt3fToCSP(people[i].RH);
		mapper->MapCameraPointToColorSpace(csp, &cop);

		if (people[i].RHS) {
			cv::circle(color, cv::Point((int)cop.X, (int)cop.Y), 10, cv::Scalar(0, 255, 0));
		}
		else {
			cv::circle(color, cv::Point((int)cop.X, (int)cop.Y), 10, cv::Scalar(0, 0, 255));
		}
	}

	return color;
}

void printButtons(int i) {
	string command = "";
	
	if ((buttonPress[i] - prevButtonPress[i])) {
		if (buttonPress[i] & (0x01))
			command.append(" up");
		if (buttonPress[i] & (0x01 << 1))
			command.append(" down");
		if (buttonPress[i] & (0x01 << 2))
			command.append(" left");
		if (buttonPress[i] & (0x01 << 3))
			command.append(" right");
		if (buttonPress[i] & (0x01 << 4))
			command.append(" A");
		if (buttonPress[i] & (0x01 << 5))
			command.append(" B");
		if (buttonPress[i] & (0x01 << 6))
			command.append(" start");
		if (buttonPress[i] & (0x01 << 7))
			command.append(" select");
		cout << command << "\r\n";
	}
}
#endif
bool sendInit() {
	char data[4] = { 'i', 'n' , 'i', 't'};

	return uart.sendData(data, sizeof(data));
}

bool sendButtonPress(char address, char* presses) {
	char start = 0xFF;

	if (uart.sendData(&start, 1)) {
		if (uart.sendData(&address, 1)) {
			if (uart.sendData(presses, 1)) {
				return true;
			}
		}
	}

	return false;
}

bool receiveHS()
{
	char data[4];
	char init[4] = { 'i', 'n', 'i', 't' };
	char rx[1] = { 'z' };
	sendInit();
	uart.receiveData(data, 4);
	
	if (data[0] == 'i' && data[1] == 'n' && data[2] == 'i' && data[3] == 't') {
		uart.sendData(rx, 1);
		return true;
	}
	
	return false;
}
