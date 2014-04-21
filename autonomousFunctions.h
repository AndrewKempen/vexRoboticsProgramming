#pragma systemFile

void wait(float seconds)
{
	wait1Msec((int)1000*seconds);
}
void autonSetLiftArmDown(int speed = -127) //Put the hanging arm all the way down
{
	speed = -abs(speed);
	while(SensorValue[liftDown] != 1)
	{
		startLiftArm(speed);
	}
	stopLiftArm();
}

//Reset Functions
int rightEncoder(int reset = 1) //Read average of right wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(SensorBoolean[isIMEFailure])
		{
			SensorValue[middleRightBackup] = 0;
		}
		else
		{
			nMotorEncoder[backRight] = 0;
			nMotorEncoder[frontRight] = 0;
		}
		distance = 0;
	}
	else
	{
		if(SensorBoolean[isIMEFailure])
		{
			distance = abs((int)(SensorValue[middleRightBackup] * 1.0888));
		}
		else
		{
			distance = (abs(nMotorEncoder[backRight]) + (abs(nMotorEncoder[frontRight])) / 2); //Average
		}
	}
	return distance;
}

int leftEncoder(int reset = 1) //Read average of left wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(SensorBoolean[isIMEFailure])
		{
			SensorValue[middleLeftBackup] = 0;
		}
		else
		{
			nMotorEncoder[backLeft] = 0;
			nMotorEncoder[frontLeft] = 0;
		}
		distance = 0;
	}
	else
	{
		if(SensorBoolean[isIMEFailure])
		{
			distance = abs((int)(SensorValue[middleLeftBackup] * 1.0888));
		}
		else
		{
			distance = (abs(nMotorEncoder[backLeft]) + (abs(nMotorEncoder[frontLeft])) / 2); //Average
		}
	}
	return distance;
}

int liftEncoder(int clear = 1)
{
	if(clear == 0)
	{
		SensorValue[liftArmEncoder] = 0;
		return 0;
	}
	else
	{
		return (-SensorValue[liftArmEncoder]);
	}

}

void baseEncoderReset() //Reset all base encoders
{
	rightEncoder(0);
	leftEncoder(0);
}

void liftArmEncoderReset() //Reset hanging arm encoder
{
	autonSetLiftArmDown();
	liftEncoder(0);
}

void fullClear() //Clear EVERYTHING
{
	clearLCD();
	baseEncoderReset();
	liftArmEncoderReset();
}
int autonEncode(bool red, bool blue, bool hangingZone, bool middleZone, int routine = 1) //Turn true's and falses into the autonomous code
{
	int returnAton;
	if((red && blue) || (!red && !blue) || (hangingZone && middleZone) || (!hangingZone && !middleZone))
	{
		returnAton = 5;
		writeDebugStreamLine("ERROR: Unexpected Inputs at \"autonEncode\"");
	}
	else
	{
		if(red && hangingZone)
		{
			returnAton = redHangingZone;
		}
		else if(red && middleZone)
		{
			returnAton = redMiddleZone;
		}
		else if(blue && hangingZone)
		{
			returnAton = blueHangingZone;
		}
		else if(blue && middleZone)
		{
			returnAton = blueMiddleZone;
		}
		returnAton = returnAton + routine;
	}
	return returnAton;
}

void autonSetLiftArm(int locationInDegrees, int speed = 127) //Set the lift arm to a height in degrees
{
	if(locationInDegrees > liftEncoder())
	{
		while(liftEncoder() < locationInDegrees)
		{
			startLiftArm(maxSpeed);
		}
	}
	else if(locationInDegrees < liftEncoder())
	{
		while(liftEncoder() > locationInDegrees)
		{
			startLiftArm(minSpeed);
		}
	}
	stopLiftArm();
}
void resetEveryThing()
{
	autonSetLiftArmDown();
	liftArmEncoderReset();
	baseEncoderReset();
	clearLCD();
}
void batteryCheck()
{
	if(nImmediateBatteryLevel/1000.0 < MAINBATTERYTHRESHOLD)
	{
		bLCDBacklight = true;
		parameter = "Main Battery Low";
		lcdPrint(0);
		bLCDBacklight = false;
		for(int i;i<4;i++)
		{
			clearLCDLine(0);
			bLCDBacklight = true;
			displayLCDCenteredString(0, "Main Battery Low");
			wait1Msec(1000);
			bLCDBacklight = false;
			clearLCDLine(0);
			wait1Msec(500);
		}
	}
	if(BackupBatteryLevel/1000.0 < BACKUPBATTERYTHRESHOLD)
	{
		bLCDBacklight = true;
		parameter = "Back Battery Low";
		lcdPrint(0);
		bLCDBacklight = false;
		for(int i;i<2;i++)
		{
			clearLCDLine(0);
			bLCDBacklight = true;
			displayLCDCenteredString(0, "Back Battery Low");
			wait1Msec(1000);
			bLCDBacklight = false;
			clearLCDLine(0);
			wait1Msec(500);
		}
	}
}
bool liftArmButtonEvent()
{
	if(liftBtnUpLastState == 1 && vexRT[Btn6U] == 1)
	{
		return false;
	}
	else if(liftBtnDownLastState == 1 && vexRT[Btn6D] == 1)
	{
		return false;
	}
	else if(liftBtnUpLastState == 0 && vexRT[Btn6U] == 1)
	{
		writeDebugStreamLine("INFO: Button Event at \"liftArmButtonEvent\"");
		return true;
	}
	else if(liftBtnDownLastState == 0 && vexRT[Btn6D] == 1)
	{
		writeDebugStreamLine("INFO: Button Event at \"liftArmButtonEvent\"");
		return true;
	}
	else
	{
		liftBtnUpLastState = vexRT[Btn6U];
		liftBtnDownLastState = vexRT[Btn6D];
		return false;
	}
}
void lineFollow(int degrees, int low = 83, int high = 97, int tthreshold = threshold)
{
	rightEncoder(0);
	while(rightEncoder() < degrees)
	{
		if(SensorValue(lineMiddle) < tthreshold)
		{
			startBaseTurn(high, high);
		}
		if(SensorValue(lineRight) < tthreshold)
		{
			startBaseTurn(low, high);
		}
		if(SensorValue(lineLeft) < tthreshold)
		{
			startBaseTurn(high, low);
		}
	}
	stopBase();
}
void lineFollowLine(int low = 83, int high = 97)
{
	rightEncoder(0);
	while(SensorValue[lineFarRight] > farThreshold && SensorValue[lineFarLeft] > farThreshold)
	{
		if(SensorValue(lineMiddle) < threshold)
		{
			startBaseTurn(high, high);
		}
		else if(SensorValue(lineRight) < threshold)
		{
			startBaseTurn(high, low);
		}
		else if(SensorValue(lineLeft) < threshold)
		{
			startBaseTurn(low, high);
		}
	}
	stopBase();
}

void lineFollowBack(int degrees, int low = -83, int high = -97)
{
	rightEncoder(0);
	while(rightEncoder() < degrees)
	{
		if(SensorValue(lineMiddle) < threshold)
		{
			startBaseTurn(high, high);
		}
		if(SensorValue(lineRight) < threshold)
		{
			startBaseTurn(low, high);
		}
		if(SensorValue(lineLeft) < threshold)
		{
			startBaseTurn(high, low);
		}
	}
	stopBase();
}

void rightTurn(bool red, int rightDistance, int rightSpeed = -127, int leftSpeed = 127)
{
	baseEncoderReset();
	if(red)
	{
	}
}
