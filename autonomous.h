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

}

void hangingZoneMoveBigBall(bool red)
{

}
void middleZoneStash(bool red)
{
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
	lift.requestedLocation = 200;
	lift.isPIDon = true;
	startBase(-23);
	wait(1);
	rightEncoder(0);
	while(rightEncoder() < 600)
	{
		startBase(-127);
	}
	stopBase();
	startIntake(63);
	if(!red)
	{
		rightEncoder(0);
		while(rightEncoder() < 580)
		{
			startBaseTurn(-127, 127);
		}
	}
	else
	{
		leftEncoder(0);
		while(leftEncoder() < 580)
		{
			startBaseTurn(127, -127);
		}
	}
	stopBase();
	stopIntake();
	lift.isPIDon = false;
	autonSetLiftArmDown();
	lift.requestedLocation = 0;
	startBase(-63);
	wait(1);
	middleZoneStash(red);
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
		case hangingZoneStashAuton:
			hangingZoneStash(red);
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
			middleZoneStash(red);
			return;
		case getBigBallAuton:
			middleZoneGetBigBall(red);
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
