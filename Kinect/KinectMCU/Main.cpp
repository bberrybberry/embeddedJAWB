/**
 * @file
 * @brief C++ for Kinect 2 Controller
 */

#include "Main.h"


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

int main() {
	UART uart(CBR_115200, 8, ONESTOPBIT, NOPARITY);
	if (!uart.UARTInit("\\\\.\\COM6"))
		return -2;
	if (!uart.configTimeouts())
		return -3;
	if (!uart.configUART())
		return -4;
	if (!uart.sendData("a", 1))
		return -5;
	
	if (FAILED(GetDefaultKinectSensor(&sensor)))
		return -1;

	if (sensor) {
		sensor->Open();

		if (SUCCEEDED(sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Body | FrameSourceTypes::FrameSourceTypes_Color | FrameSourceTypes::FrameSourceTypes_Depth, &reader))) {

			colorBuffer = new UINT8[width * height * 4];
			cv::Mat skeleton = cv::Mat::zeros(height, width, CV_8UC3);
			cv::Mat color = cv::Mat::zeros(height, width, CV_8UC4);
			
			
			threshold = 0.2;
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

						cv::imshow("color", color);
						cv::waitKey(1);
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

					frame->Release();
					bodyFrame->Release();
					string command = "";
					for (int i = 0; i < BODY_COUNT; i++) {
						if (!trackedJoints[i]) {
							buttonPress[i] = NULL;
							continue;
						}
						buttonPress[i] = pollButtons(people[i]);

						if (!(buttonPress[i] - prevButtonPress[i])) {
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
					memcpy(prevButtonPress, buttonPress, sizeof(buttonPress));
					trackedJoints.clear();
				}
			}
		}
	}

	return 0;
}

cv::Point3f jointToPt3f(Joint joint) {
	return cv::Point3f(joint.Position.X, joint.Position.Y, joint.Position.Z);
}

HANDLE initSerial() {
	return CreateFileA(COMport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
}

bool configSerial(HANDLE* handle) {
	serialParams.BaudRate = CBR_115200;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;

	if (!SetCommState(handle, &serialParams)) {
		CloseHandle(handle);
		return false;
	}

	return true;
}

bool configTimeouts(HANDLE* handle, COMMTIMEOUTS* timeouts) {
	timeouts->ReadIntervalTimeout = 50;
	timeouts->ReadTotalTimeoutConstant = 50;
	timeouts->ReadTotalTimeoutMultiplier = 10;
	timeouts->WriteTotalTimeoutConstant = 50;
	timeouts->WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(handle, timeouts)) {
		CloseHandle(handle);
		return false;
	}

	return true;
}

bool pressA(Person player)
{
	if ((player.CL.y - player.LH.y) < -threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressB(Person player)
{
	if ((player.CL.y - player.LH.y) > threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressUp(Person player)
{
	if ((player.CR.y - player.RH.y) < -threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressDown(Person player)
{
	if ((player.CR.y - player.RH.y) > threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressLeft(Person player)
{
	if ((player.CR.x - player.RH.x) > threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressRight(Person player)
{
	if ((player.CR.x - player.RH.x) < -threshold && player.RHS)
		return true;
	else
		return false;
}

bool pressStart(Person player)
{
	if ((player.CL.x - player.LH.x) > threshold && player.LHS)
		return true;
	else
		return false;
}

bool pressSelect(Person player)
{
	if ((player.CL.x - player.LH.x) < -threshold && player.LHS)
		return true;
	else
		return false;
}

void updatePerson(Person* player, Joint joints[25]) {
	player->CL = jointToPt3f(joints[JointType_ElbowLeft]);
	player->CR = jointToPt3f(joints[JointType_ElbowRight]);
	player->RH = jointToPt3f(joints[JointType_HandRight]);
	player->LH = jointToPt3f(joints[JointType_HandLeft]);
}

unsigned char pollButtons(Person player)
{
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

bool sendInit(HANDLE serial)
{
	return false;
}

bool sendButtonPress(HANDLE serial, int address, unsigned char * presses)
{
	return false;
}