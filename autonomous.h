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
| 2      | Red Middle Zone     | Big Ball Move      | Stash              |
+--------+---------------------+--------------------+--------------------+
| 3      | Blue Hanging Zone   |                    |                    |
+--------+---------------------+--------------------+--------------------+
| 4      | Blue Middle Zone    |                    |                    |
+--------+---------------------+--------------------+--------------------+
*/

void hangingZoneHang(bool red)
{
	startIntake(-127);
	wait(1);
	startIntake(127);
	wait(0.5);
	lift.requestedLocation = lift.maxHeight + 100;
	lift.isPIDon = true;
	lineFollow(720);
	stopIntake();
	lineFollowBack(100);
	wait(1);
	if(red)
	{
		rightEncoder(0);
		while(rightEncoder()<230)
		{
			startBaseTurn(63, -63);
		}
	}
	else
	{
		leftEncoder(0);
		while(leftEncoder()<230)
		{
			startBaseTurn(-63, 63);
		}
	}
	stopBase();
	ClearTimer(T4);
	rightEncoder(0);
	while(rightEncoder() < 860 && time1[T4] < 6000)
	{
		startBase(-127);
	}
	stopBase();
	lift.requestedLocation = 400;
}
void hangingZoneMoveBigBall(bool red)
{
	startIntake(-127);
	wait(0.5);
	startIntake(127);
	lineFollow(890);
	wait(1.5);
	lift.requestedLocation = 250;
	lift.isPIDon = true;
	baseEncoderReset();
	stopIntake();
	if(red)
	{
		while(rightEncoder()<390)
		{
			startBaseTurn(63, -63);
		}
	}
	else
	{
		while(leftEncoder()<390)
		{
			startBaseTurn(-63, 63);
		}
	}
	moveBase(1400, true, 127);
	stopIntake();
	wait(0.5);
	baseEncoderReset();
	lift.requestedLocation = 900;
	wait(2);
	moveBase(320, true, 63);
	stopBase();
	startIntake(-127);
	wait10Msec(100);
}
void middleZonePushBigBalls(bool red)
{
	startIntake(-127);
	wait(0.5);
	lift.isPIDon = true;
	lift.requestedLocation = 900;
	wait(3.5);
	lineFollow(850);
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
	if(!red)
	{
		leftEncoder(0);
		while(leftEncoder() < 950)
		{
			startLeft(127);
		}
	}
	else
	{
		rightEncoder(0);
		while(rightEncoder() < 950)
		{
			startRight(127);
		}
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
	startIntake(-127);
	wait(0.5);
	stopIntake();
	lineFollow(2200);
	startIntake(23);
	lift.isPIDon = true;
	lift.requestedLocation = lift.stashHeight + 100;
	wait(1);
	if(!red)
	{
		rightEncoder(0);
		while(rightEncoder() < 743)
		{
			startRight(63);
		}
	}
	else
	{
		leftEncoder(0);
		while(leftEncoder() < 743)
		{
			startLeft(63);
		}
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
	if(autonomusCode == 11) //Red Hang
	{
		hangingZoneHang(true);
	}
	else if(autonomusCode == 31) //Blue Hang
	{
		hangingZoneHang(false);
	}
	else if(autonomusCode == 12) //Red Move Big Balls
	{
		hangingZoneMoveBigBall(true);
	}
	else if(autonomusCode == 32) //Blue Move Big Balls
	{
		hangingZoneMoveBigBall(false);
	}
	else if(autonomusCode == 21) //Red Push Big Balls
	{
		middleZonePushBigBalls(true);
	}
	else if(autonomusCode == 41) //Blue Push Big Balls
	{
		middleZonePushBigBalls(false);
	}
	else if(autonomusCode == 22) //Red Push Big Balls
	{
		middleZoneStash(true);
	}
	else if(autonomusCode == 42) //Blue Push Big Balls
	{
		middleZoneStash(false);
	}
}
