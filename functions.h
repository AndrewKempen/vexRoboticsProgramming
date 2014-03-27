int average(int num1, int num2)
{
	return ((num1 + num2)/2);
}
//Reset Functions
int rightEncoder(int reset = 1) //Read average of right wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(IMEFAILURE)
		{
			SensorValue[middleRightBackup] = 0;
			SensorValue[middleLeftBackup] = 0;
		}
		else
		{
			nMotorEncoder[backRight] = 0;
			nMotorEncoder[middleRight] = 0;
		}
		distance = 0;
	}
	else
	{
		if(IMEFAILURE)
		{
			distance = SensorValue[middleRightBackup];
		}
		else
		{
			distance = (abs(nMotorEncoder[backRight]) + abs(nMotorEncoder[middleRight])) / 2; //Average
		}
	}
	return distance;
}
int leftEncoder(int reset = 1) //Read average of right wheel encoders
{
	int distance;
	if(reset == 0) //Reset the motor encoders
	{
		if(IMEFAILURE)
		{
			SensorValue[middleRightBackup] = 0;
			SensorValue[middleLeftBackup] = 0;
		}
		else
		{
			nMotorEncoder[backRight] = 0;
			nMotorEncoder[middleRight] = 0;
		}
		distance = 0;
	}
	else
	{
		if(IMEFAILURE)
		{
			distance = SensorValue[middleLeftBackup];
		}
		else
		{
			distance = (nMotorEncoder[backLeft] + nMotorEncoder[middleLeft]) / 2; //Average
		}
	}
	return distance;
}
void baseEncoderReset() //Reset all base encoders
{
	rightEncoder(0);
	leftEncoder(0);
}
void liftArmEncoderReset() //Reset hanging arm encoder
{
	SensorValue[liftArmEncoder] = 0;
}
void fullClear() //Clear EVERYTHING
{
	clearLCD();
	baseEncoderReset();
	liftArmEncoderReset();
}


//Start Functions
void startBase(int speed = 127) //Start moving base with auto correction from encoders
{
	if(abs(nMotorEncoder[backRight]) == abs(nMotorEncoder[backLeft]))
	{
		motor[middleRight] = speed;
		motor[middleLeft]  = speed;
		motor[backRight] = speed;
		motor[backLeft]  = speed;
	}
	else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
	{
		motor[middleRight] = speed+20;
		motor[middleLeft]  = speed;
		motor[backRight] = speed+20;
		motor[backLeft]  = speed;
	}
	else
	{
		motor[middleRight] = speed;
		motor[middleLeft]  = speed+20;
		motor[backRight] = speed;
		motor[backLeft]  = speed+20;
	}
	wait1Msec(1);
}
void startLiftArm(int speed = 127) //Start moving hanging arm
{
	motor[liftTopRight] = speed;
	motor[liftTopLeft]  = speed;
	motor[liftBottomRight] = speed;
	motor[liftBottomLeft]  = speed;
}
void startIntake(int speed = 127) //Start moving intake
{
	motor[intakeRight] = speed;
	motor[intakeLeft] = speed;
}
void startBaseTurn(int rightSpeed = 127, int leftSpeed = 127) //Start turning
{
	motor[middleRight] = rightSpeed;
	motor[middleLeft]  = leftSpeed;
	motor[backRight] = rightSpeed;
	motor[backLeft]  = leftSpeed;
}

//Stopping Functions
void allStop() //Stop EVERYTHING
{
	motor[middleRight] = 0;
	motor[middleLeft]  = 0;
	motor[backRight] = 0;
	motor[backLeft]  = 0;
	motor[liftTopRight] = 0;
	motor[liftTopLeft]  = 0;
	motor[liftBottomRight] = 0;
	motor[liftBottomLeft]  = 0;
	motor[intakeRight] = 0;
	motor[intakeLeft] = 0;
}
void stopBase() //Stop Base
{
	motor[middleRight] = 0;
	motor[middleLeft]  = 0;
	motor[backRight] = 0;
	motor[backLeft]  = 0;
}
void stopLiftArm() //Stop hanging arm
{
	motor[liftTopRight] = 0;
	motor[liftTopLeft]  = 0;
	motor[liftBottomRight] = 0;
	motor[liftBottomLeft]  = 0;
}
void stopIntake() //Stop intake
{
	motor[intakeRight] = 0;
	motor[intakeLeft] = 0;
}

//Move Functions
void moveBase(int totalDegrees, bool forward, int speed = 127) //Move forward for degrees with auto correct from encoders
{
	speed=speed-20;
	if(!forward)
	{
		while(abs(nMotorEncoder[backRight]) < (abs(totalDegrees)))
		{
			if(abs(nMotorEncoder[backRight]) == abs(nMotorEncoder[backLeft]))
			{
				motor[middleRight] = speed;
				motor[middleLeft]  = speed;
				motor[backRight] = speed;
				motor[backLeft]  = speed;
			}
			else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
			{
				motor[middleRight] = speed-20;
				motor[middleLeft]  = speed;
				motor[backRight] = speed-20;
				motor[backLeft]  = speed;
			}
			else
			{
				motor[middleRight] = 0-speed;
				motor[middleLeft]  = 0-speed-20;
				motor[backRight] = 0-speed;
				motor[backLeft]  = 0-speed-20;
			}
			wait1Msec(1);
		}
	}
	else if(forward)
	{
		while(abs(nMotorEncoder[backRight]) < (abs(totalDegrees)))
		{
			if(abs(nMotorEncoder[backRight]) == abs(nMotorEncoder[backLeft]))
			{
				motor[middleRight] = speed;
				motor[middleLeft]  = speed;
				motor[backRight] = speed;
				motor[backLeft]  = speed;
			}
			else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
			{
				motor[middleRight] = speed+20;
				motor[middleLeft]  = speed;
				motor[backRight] = speed+20;
				motor[backLeft]  = speed;
			}
			else
			{
				motor[middleRight] = speed;
				motor[middleLeft]  = speed+20;
				motor[backRight] = speed;
				motor[backLeft]  = speed+20;
			}
			wait1Msec(1);
		}
	}
	stopBase();
}
void ballArmToggle() //Intake arm position toggle
{
	if(!armIsDown)
	{
		SensorValue[ballLift] = 0;
		armIsDown = true;
	}
	else
	{
		SensorValue[ballLift] = 1;
		armIsDown = false;
	}
}
//Atonomus Functions
void lineFollow1(int low = 15, int high = 55) //Line follow (For use in an outside loop)
{
	// CENTER sensor sees dark:
	if(SensorValue(lineMiddle) < threshold)
	{
		// go straight
		motor[backLeft]  = high;
		motor[middleLeft]  = high;
		motor[backRight] = high;
		motor[middleRight] = high;
	}
	// RIGHT sensor sees dark:
	if(SensorValue(lineRight) > threshold)
	{
		// counter-steer right:
		motor[backLeft]  = high;
		motor[middleLeft]  = high;
		motor[backRight] = low;
		motor[middleRight] = low;
	}

	// LEFT sensor sees dark:
	if(SensorValue(lineLeft) > threshold)
	{
		// counter-steer left:
		motor[backLeft]  = low;
		motor[middleLeft]  = low;
		motor[backRight] = high;
		motor[middleRight] = high;
	}
}
void lineFollow(bool reset = false, int degrees, int low = 15, int high = 55) //Linefollow for degrees
{
	if(reset) //Recalibrate linefollowers?
	{
		int right = SensorValue(lineRight);
		int middle = SensorValue(lineMiddle);
		int left = SensorValue(lineLeft);
		if((right>middle) && (left>middle))
		{
			threshold = (((right+left)/2)+middle)/2;
		}
	}
	rightEncoder(0);
	while(rightEncoder()<degrees)
	{
		// RIGHT sensor sees dark:
		if(SensorValue(lineRight) > threshold)
		{
			// counter-steer right:
			motor[backLeft]  = high;
			motor[middleLeft]  = high;
			motor[backRight] = low;
			motor[middleRight] = low;
		}
		// CENTER sensor sees dark:
		if(SensorValue(lineMiddle) < threshold)
		{
			// go straight
			motor[backLeft]  = high;
			motor[middleLeft]  = high;
			motor[backRight] = high;
			motor[middleRight] = high;
		}

		// LEFT sensor sees dark:
		if(SensorValue(lineLeft) > threshold)
		{
			// counter-steer left:
			motor[backLeft]  = low;
			motor[middleLeft]  = low;
			motor[backRight] = high;
			motor[middleRight] = high;
		}
	}
	stopBase();
}
void lineFollowBack(bool reset = false, int degrees) //Line follow backwards
{
	int low = -15;
	int high = -55;
	if(reset)
	{
		int right = SensorValue(lineRight);
		int middle = SensorValue(lineMiddle);
		int left = SensorValue(lineLeft);
		if((right>middle) && (left>middle))
		{
			threshold = (((right+left)/2)+middle)/2;
		}
	}
	rightEncoder(0);
	while(rightEncoder()<degrees)
	{
		// CENTER sensor sees dark:
		if(SensorValue(lineMiddle) < threshold)
		{
			// go straight
			motor[backLeft]  = high;
			motor[middleLeft]  = high;
			motor[backRight] = high;
			motor[middleRight] = high;
		}
		// RIGHT sensor sees dark:
		if(SensorValue(lineRight) > threshold)
		{
			// counter-steer right:
			motor[backLeft]  = high;
			motor[middleLeft]  = high;
			motor[backRight] = low;
			motor[middleRight] = low;
		}

		// LEFT sensor sees dark:
		if(SensorValue(lineLeft) > threshold)
		{
			// counter-steer left:
			motor[backLeft]  = low;
			motor[middleLeft]  = low;
			motor[backRight] = high;
			motor[middleRight] = high;
		}
	}
	stopBase();
}
int atonEncode(bool red, bool blue, bool hangingZone, bool middleZone, int rotine = 1) //Turn true's and falses into the automous
{
	int returnAton;
	if((red && blue) || (!red && !blue) || (hangingZone && middleZone) || (!hangingZone && !middleZone))
	{
		returnAton = 5;
		displayLCDCenteredString(0, "E@ AtonSelector");
		wait10Msec(500);
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
void atonSetLiftArmDown(int speed = -127) //Put the hanging arm all the way down
{
	speed = 0 - abs(speed);
	while(SensorValue(liftArmDown) != 1)
	{
		startLiftArm(speed);
	}
	stopLiftArm();
}
void atonSetLiftArm(int locationInDegrees, int speed = 127) //Set the lift arm to a height in degrees
{
	if(locationInDegrees > abs(SensorValue[liftArmEncoder]))
	{
		while(abs(SensorValue[liftArmEncoder]) < locationInDegrees)
		{
			startLiftArm(maxSpeed);
		}
	}
	else if(locationInDegrees < abs(SensorValue[liftArmEncoder]))
	{
		while(abs(SensorValue[liftArmEncoder]) > locationInDegrees)
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
}
