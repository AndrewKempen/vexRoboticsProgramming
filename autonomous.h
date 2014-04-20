#pragma systemFile
/*
+--------+---------------------+-----------------------------------------+
| Number | First Number (#0)   | Second Number (0#)                      |
+        +                     +-----------------------------------------+
|        |                     | Hanging Zone - 1   | Middle Zone - 2    |
+--------+---------------------+--------------------+--------------------+
| 0      | No Aton             | No Aton            | No Aton            |
+--------+---------------------+--------------------+--------------------+
| 1      | Red Hanging Zone    | Hang               | Push Big Balls Off |
+--------+---------------------+--------------------+--------------------+
| 2      | Red Middle Zone     | Big Ball Move      |                    |
+--------+---------------------+--------------------+--------------------+
| 3      | Blue Hanging Zone   |                    |                    |
+--------+---------------------+--------------------+--------------------+
| 4      | Blue Middle Zone    |                    |                    |
+--------+---------------------+--------------------+--------------------+
| 5      | Programing Skills   | Retreat From Right | Retreat From Left  |
+--------+---------------------+--------------------+--------------------+
*/

void hangingZoneHang(bool red)
{
	startIntake(127); //Intake start at 127
	lineFollow(720); //Line follow
	wait(1.5);
	stopIntake(); //Stop intake
	lineFollowBack(100);
	lift.requestedLocation = lift.maxHeight;
	lift.isPIDon = true;
	wait(1);
	rightEncoder(0); //Reset right encoders
	while(rightEncoder()<230) //Turn
	{
		startBaseTurn(63, -63);
	}
	stopBase(); //Stop base
	wait(5);
	ClearTimer(T4);
	rightEncoder(0);
	while(rightEncoder() < 860 && time1[T4] < 3500) //Forward with timeout
	{
		startBase(-127);
	}
	stopBase(); //Stop Base
	lift.requestedLocation = 400;
}
void hangingZoneMoveBigBall(bool red)
{
		startIntake(127); //Start intake at 127
		lineFollow(false, 890); //Follow line
		lift.requestedLocation = 250;
		lift.isPIDon = true;
		baseEncoderReset(); //Clear all encoders on base
		stopIntake(); //Stop the intake
		while(rightEncoder()<390) //Turn
		{
			startBaseTurn(63, -63);
		}
		startIntake(50); //Start intake at 50 to keep the buckyballs in
		moveBase(1400, true, 100); //Move forward
		stopIntake(); //Stop intake
		wait1Msec(500); //Pause to let the big ball settle
		baseEncoderReset(); //Reset the base's encoders
		lift.requestedLocation = 900;
		moveBase(320, true, 63); //Advance to the barrier
		stopBase(); //Stop the base
		startIntake(-127); //Outake big ball into other big ball
		wait10Msec(100); //Pause to outake the bigball
}
void middleZonePushBigBalls(bool red)
{
	lift.isPIDon = true;
	lift.requestedLocation = 900;
	wait(3.5);
	lineFollow(850);
	startIntake(-63);
	wait(1.3);
	lineFollowBack(850);
	wait(4);
	rightEncoder(0);
	while(rightEncoder() < 600)
	{
		startBase(127);
	}
	stopBase();
	wait(1);
	leftEncoder(0);
	while(leftEncoder() < 950)
	{
		startLeft(127);
	}
	stopBase();
	rightEncoder(0);
	while(rightEncoder() < 400)
	{
		startBase(127);
	}
	stopBase();
}
void middleZoneStash(bool red)
{
	lineFollow(2200);
	startIntake(23);
	lift.isPIDon = true;
	lift.requestedLocation = lift.stashHeight + 100;
	wait(1);
	rightEncoder(0);
	while(rightEncoder() < 743)
	{
		startRight(63);
	}
	stopBase();
	rightEncoder(0);
	while(rightEncoder() < 150)
	{
		startBase(63);
	}
	stopBase();
	wait(5);
	rightEncoder(0);
	while(rightEncoder() < 110)
	{
		startBase(63);
	}
	stopBase();
	startIntake(-42);
	wait(1);
	startIntake(127);
	wait(1);
	startIntake(-42);
	wait(1);
	startIntake(127);
	rightEncoder(0);
	while(rightEncoder() < 200)
	{
		startBase(-63);
	}
	stopBase();
	lift.requestedLocation = lift.stashHeight - 100;
	wait(2);
	startIntake(-35);
}
void middleZoneGetBigBall(bool red)
{

}
void hangingZoneStash(bool red)
{
	startIntake(127);
	lineFollow(620);
	wait(1);
	lineFollowBack(620);
	startIntake(25);
	lift.requestedLocation = 250;
	lift.isPIDon = true;
	startBase(-23);
	wait(1);
	stopBase();
	rightEncoder(0);
	while(rightEncoder() < 600)
	{
		startBase(-127);
	}
	stopBase();
	wait(1);
	startIntake(63);
	if(!red)
	{
		rightEncoder(0);
		while(rightEncoder() < 800)
		{
			startBaseTurn(-127, 127);
		}
		stopIntake();
	}
	else
	{
		leftEncoder(0);
		while(leftEncoder() < 800)
		{
			startBaseTurn(63, -63);
		}
		stopIntake();
	}
	stopBase();
	lift.requestedLocation = 0;
	startBase(-63);
	wait(1);
	stopBase();
	startBaseTurn(120, 127);
	wait(1);
	stopBase();
	/*
	wait(1);
	rightEncoder(0);
	while(rightEncoder() < 320)
	{
	startBase(63);
	}
	stopBase();
	wait(1);
	leftEncoder(0);
	while(SensorValue[lineMiddle] > threshold)
	{
	startLeft(63);
	}
	stopBase();
	*/
}
void auton(int autonomusCode)
{
	bool red;
	int zone = (autonomusCode/10);
	if(zone == 1 || zone == 2)
	{
		red = true;
	}
	else
	{
		red = false;
	}
	if(zone == 1 || zone == 3)
	{
		switch(autonomusCode - (zone*10))
		{
		case hangAuton:
			hangingZoneHang(red);
			return;
		case moveBigBallAuton:
			hangingZoneMoveBigBall(red);
			return;
		default:
			writeDebugStreamLine("ERROR: Unexpected auton number at \"auton\"");
			return;
		}
	}
	else if(zone == 2 || zone == 4)
	{
		switch(autonomusCode - (zone*10))
		{
		case stashAuton:
			middleZonePushBigBalls(red);
			return;
		case getBigBallAuton:
			middleZoneStash(red);
			return;
		default:
			writeDebugStreamLine("ERROR: Unexpected auton number at \"auton\"");
			return;
		}
	}
	else
	{
		writeDebugStreamLine("ERROR: Unexpected zone number at \"auton\"");
	}
}
