#pragma systemFile

void atonSetLiftArmDown(int speed = -127) //Put the hanging arm all the way down
{
	speed = 0 - abs(speed);
	while(SensorValue(liftDown) != 1)
	{
		startLiftArm(-abs(speed));
	}
	stopLiftArm();
}

//Reset Functions
int rightEncoder(int reset = 1) //Read average of right wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(SensorBoolean[IMEFailure])
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
		if(SensorBoolean[IMEFailure])
		{
			distance = SensorValue[middleRightBackup];
		}
		else
		{
			distance = (abs(nMotorEncoder[backRight]) + abs(nMotorEncoder[frontRight])) / 2; //Average
		}
	}
	return distance;
}

int leftEncoder(int reset = 1) //Read average of right wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(SensorBoolean[IMEFailure])
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
		if(SensorBoolean[IMEFailure])
		{
			distance = SensorValue[middleLeftBackup];
		}
		else
		{
			distance = (nMotorEncoder[backLeft] + nMotorEncoder[frontLeft]) / 2; //Average
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
		return abs(SensorValue[liftArmEncoder]);
	}

}

void baseEncoderReset() //Reset all base encoders
{
	rightEncoder(0);
	leftEncoder(0);
}

void liftArmEncoderReset() //Reset hanging arm encoder
{
	atonSetLiftArmDown(-127);
	liftEncoder(0);
}

void fullClear() //Clear EVERYTHING
{
	clearLCD();
	baseEncoderReset();
	liftArmEncoderReset();
}
int autonEncode(bool red, bool blue, bool hangingZone, bool middleZone, int rotine = 1) //Turn true's and falses into the automous
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
			returnAton = 10;
		}
		else if(red && middleZone)
		{
			returnAton = 20;
		}
		else if(blue && hangingZone)
		{
			returnAton = 30;
		}
		else if(blue && middleZone)
		{
			returnAton = 40;
		}
		returnAton = returnAton + rotine;
	}
	return returnAton;
}

void atonSetLiftArm(int locationInDegrees, int speed = 127) //Set the lift arm to a height in degrees
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
	atonSetLiftArmDown();
	liftArmEncoderReset();
	baseEncoderReset();
	clearLCD();
}
void batteryCheck()
{
	if(nImmediateBatteryLevel/1000.0 < MAINBATTERYTHRESHOLD)
	{
		for(int i;i<4;i++)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "Main Battery Low");
			wait1Msec(250);
			clearLCDLine(0);
			wait1Msec(500);
		}
	}
	powerExpanderLevel = (int)((float)SensorValue[powerExpander] * 5.46);
	if(powerExpanderLevel > 9000)
	{
		powerExpanderLevel = (int)((float)SensorValue[powerExpander] * 3.57);
	}
	if(powerExpanderLevel < SECONDBATTERYTHRESHOLD)
	{
		for(int i;i<4;i++)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "2nd Battery Low");
			wait1Msec(250);
			clearLCDLine(0);
			wait1Msec(500);
		}
	}
	if(BackupBatteryLevel/1000.0 < BACKUPBATTERYTHRESHOLD)
	{
		for(int i;i<4;i++)
		{
			clearLCDLine(0);
			displayLCDCenteredString(0, "Back Battery Low");
			wait1Msec(250);
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
