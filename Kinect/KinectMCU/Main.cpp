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

	if (FAILED(GetDefaultKinectSensor(&sensor)))
		return -1;

	if (sensor) {
		sensor->Open();

		if (SUCCEEDED(sensor->OpenMultiSourceFrameReader(FrameSourceTypes::FrameSourceTypes_Body | FrameSourceTypes::FrameSourceTypes_Color | FrameSourceTypes::FrameSourceTypes_Depth, &reader))) {

			colorBuffer = new UINT8[width * height * 4];
			cv::Mat skeleton = cv::Mat::zeros(height, width, CV_8UC3);
			cv::Mat color = cv::Mat::zeros(height, width, CV_8UC4);

			HANDLE serial = initSerial();
			COMMTIMEOUTS timeouts;

			if (serial == INVALID_HANDLE_VALUE)
				return -2;
			
			serialParams.DCBlength = sizeof(serialParams);

			if (!GetCommState(serial, &serialParams)) {
				CloseHandle(serial);
				return -3;
			}

			if (!configSerial(&serial)) {
				CloseHandle(serial);
				return -4;
			}

			if (!configTimeouts(&serial, &timeouts)) {
				CloseHandle(serial);
				return -5;
			}

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

					for (int i = 0; i < BODY_COUNT; i++) {
						if (!trackedJoints[i]) {
							buttonPress[i] = NULL;
							continue;
						}
						buttonPress[i] = pollButtons(people[i]);
					}
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
	if ((player.CL.y - player.LH.y) < -0.2 && player.LHS)
		return true;
	else
		return false;
}

bool pressB(Person player)
{
	if ((player.CL.y - player.LH.y) > 0.2 && player.LHS)
		return true;
	else
		return false;
}

bool pressUp(Person player)
{
	if ((player.CR.y - player.RH.y) < -0.2 && player.RHS)
		return true;
	else
		return false;
}

bool pressDown(Person player)
{
	if ((player.CR.y - player.RH.y) > 0.2 && player.RHS)
		return true;
	else
		return false;
}

bool pressLeft(Person player)
{
	if ((player.CR.x - player.RH.x) > 0.2 && player.RHS)
		return true;
	else
		return false;
}

bool pressRight(Person player)
{
	if ((player.CR.x - player.RH.x) < -0.2 && player.RHS)
		return true;
	else
		return false;
}

bool pressStart(Person player)
{
	if ((player.CL.x - player.LH.x) > 0.2 && player.LHS)
		return true;
	else
		return false;
}

bool pressSelect(Person player)
{
	if ((player.CL.x - player.LH.x) < -0.2 && player.LHS)
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


