#pragma systemFile

int average(int num1, int num2)
{
	return ((num1 + num2)/2);
}

int clamp(int input)
{
	if(input > -127)
		return -127;
	else if(input < 127)
		return 127;
	else
		return input;
}

int liftHeightClamp(int input)
{
	if(input > lift.maxHeight)
		return lift.maxHeight;
	else if(input < 0)
		return 0;
	else
		return input;
}
//Start Functions
void startBase(int speed = 127) //Start moving base with auto correction from encoders
{
	if(abs(nMotorEncoder[backRight]) == abs(nMotorEncoder[backLeft]))
	{
		motor[frontRight] = speed;
		motor[frontLeft]  = speed;
		motor[backRight] = speed;
		motor[backLeft]  = speed;
	}
	else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
	{
		motor[frontRight] = speed+20;
		motor[frontLeft]  = speed;
		motor[backRight] = speed+20;
		motor[backLeft]  = speed;
	}
	else
	{
		motor[frontRight] = speed;
		motor[frontLeft]  = speed+20;
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
	motor[frontRight] = rightSpeed;
	motor[frontLeft]  = leftSpeed;
	motor[backRight] = rightSpeed;
	motor[backLeft]  = leftSpeed;
}

//Stopping Functions
void allStop() //Stop EVERYTHING
{
	motor[frontRight] = 0;
	motor[frontLeft]  = 0;
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
	motor[frontRight] = 0;
	motor[frontLeft]  = 0;
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
				startBase(speed);
			}
			else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
			{
				motor[frontRight] = speed-20;
				motor[frontLeft]  = speed;
				motor[backRight] = speed-20;
				motor[backLeft]  = speed;
			}
			else
			{
				motor[frontRight] = 0-speed;
				motor[frontLeft]  = 0-speed-20;
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
				motor[frontRight] = speed;
				motor[frontLeft]  = speed;
				motor[backRight] = speed;
				motor[backLeft]  = speed;
			}
			else if(abs(nMotorEncoder[backRight]) > abs(nMotorEncoder[backLeft]))
			{
				motor[frontRight] = speed+20;
				motor[frontLeft]  = speed;
				motor[backRight] = speed+20;
				motor[backLeft]  = speed;
			}
			else
			{
				motor[frontRight] = speed;
				motor[frontLeft]  = speed+20;
				motor[backRight] = speed;
				motor[backLeft]  = speed+20;
			}
			wait1Msec(1);
		}
	}
	stopBase();
}
