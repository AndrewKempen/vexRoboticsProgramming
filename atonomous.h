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
| 5      | Programing Skills 1 | Retreat From Right | Retreat From Left  |
+--------+---------------------+--------------------+--------------------+
*/
void aton(int atonCode)
{
	if(atonCode == 11) //Red Hanging Zone - Hang
	{
		startLiftArm(110); //Hanging arm up
		startIntake(maxSpeed); //Intake start at 127
		lineFollow(false, 720); //Line follow
		stopIntake(); //Stop intake
		baseEncoderReset(); //Reset all base encoders
		lineFollowBack(false, 200); //Backup following line
		rightEncoder(0); //Reset right encoders
		while(rightEncoder()<413) //Turn
		{
			startBaseTurn(-63, 63);
		}
		stopBase(); //Stop base
		baseEncoderReset(); //Reset base encoders
		ballArmToggle(); //Intake arm up
		stopLiftArm(); //Stop hanging arm
		atonSetLiftArm(1790, 63); //Set hanging arm to a height in degrees
		ClearTimer(T4); //Timeout incase the base can't move enough
		while(rightEncoder()<860 && time1[T4] < 3000) //Forward with timeout
		{
			startBase(93);
		}
		stopBase(); //Stop Base
		atonSetLiftArm(700, 127); //Lower the hanging arm - HIGH HANG WITH BIG BALL
	}
	if(atonCode == 12) //Red Hanging Zone - Move Big Ball - BACKUP FOR IF WE CAN'T HANG FOR SOME REASON
	{
		startLiftArm(127); //Start moving hanging arm up to keep bigball in intake when we go over the bump
		startIntake(maxSpeed); //Start intake at 127
		ClearTimer(T1); //Time out incase we can't intake both buckyballs
		while(SensorValue[intakeFull] != 1 && time1[T1] < 3000) //Intake until intake is full
		{
			if(abs(SensorValue[liftArmEncoder]) < 795) //Stop hanging arm if it is at or higher than the desired height
			{
				startLiftArm(127); //Move lift arm up
			}
			else
			{
				stopLiftArm(); //Stop lift arm
			}
			lineFollow(false, 10); //Line follow
		}
		baseEncoderReset(); //Reset all base encoders
		ClearTimer(T1); //Timeout incase we can't move the desired distance
		while(rightEncoder() < 500 && time1[T1] < 1500)
		{
			startBase(-127);
			if(abs(SensorValue[liftArmEncoder]) < 795) //Check if lift arm is at or higher than desired height
			{
				startLiftArm(127); //Move lift arm up
			}
			else
			{
				stopLiftArm(); //Stop lift arm
			}
		}
		stopBase(); //Stop Base
		wait1Msec(1500);
		if(abs(SensorValue[liftArmEncoder]) < 795) //Check if lift arm is at or higher than desired height
		{
			startLiftArm(127); //Move lift arm up
		}
		else
		{
			stopLiftArm(); //Stop lift arm
		}
		lineFollow(false, 890); //Follow line
		baseEncoderReset(); //Clear all encoders on base
		stopIntake(); //Stop the intake
		while(rightEncoder()<390) //Turn
		{
			startBaseTurn(63, -63);
		}
		startIntake(50); //Start intake at 50 to keep the buckyballs in
		moveBase(1400, true, 100); //Move forward
		stopIntake(); //Stop intake
		SensorValue[ballLift] = 1; //Lift intake
		wait1Msec(500); //Pause to let the big ball settle
		baseEncoderReset(); //Reset the base's encoders
		moveBase(320, true, 63); //Advance to the barrier
		stopBase(); //Stop the base
		startIntake(-127); //Outake big ball into other big ball
		wait10Msec(100); //Pause to outake the bigball
		startBaseTurn(-32, 63); //Turn slightly so we are able to outake the buckyballs
		wait10Msec(50); //Pause to outake the buckyballs
		stopBase(); //Stop turning
		startIntake(-63); //Outake slower to bump last bucky ball into intake
		wait10Msec(50); //Pause to finish outaking buckyball
	}
	if(atonCode == 21) //Red Middle Zone - Push Big Balls Off
	{
		startIntake(-63); //Start intake spinning backwards
		wait1Msec(500); //Pause to outake preload
		SensorValue[ballLift] = 1; //Intake arm up
		lineFollow(true, 700, 55, 95); //Line follow
		stopIntake(); //Stop intake
		lineFollowBack(false, 700); //Line follow back to base
		wait1Msec(4000); //Pause to reorient
		rightEncoder(0); //Reset right side encoders
		while(rightEncoder()<600) //Move forward
		{
			startBase(93);
		}
		stopBase(); //Stop
		rightEncoder(0); //Reset right side encoders
		while(rightEncoder()<580) //Turn in a wide arc
		{
			startBaseTurn(127, -20);
		}
		stopBase(); //Stop
		rightEncoder(0); //Reset right side encoders
		while(rightEncoder()<610) //Move forward
		{
			startBase(93);
		}
		stopBase();
	}
	if(atonCode == 31) //Blue Hanging Zone - Hang
	{
		liftArmEncoderReset();
		startLiftArm(110);
		startIntake(maxSpeed);
		baseEncoderReset();
		lineFollow(false, 720);
		stopIntake();
		baseEncoderReset();
		lineFollowBack(false, 200);
		rightEncoder(0);
		while(abs(rightEncoder())<429)
		{
			startBaseTurn(63, -63);
		}
		stopBase();
		baseEncoderReset();
		ballArmToggle();
		stopLiftArm();
		atonSetLiftArm(1790, 127);
		ClearTimer(T4);
		while(rightEncoder()<860 && time1[T4] < 3000)
		{
			startBase(93);
		}
		stopBase();
		atonSetLiftArm(700, 127);
	}
	if(atonCode == 41) //Blue Middle Zone - Push Big Balls Off
	{
		startIntake(-63);
		wait1Msec(500);
		SensorValue[ballLift] = 1;
		lineFollow(true, 700, 55, 95);
		stopIntake();
		lineFollowBack(false, 700);
		wait1Msec(14000);
		rightEncoder(0);
		while(rightEncoder()<600)
		{
			startBase(93);
		}
		stopBase();
		leftEncoder(0);
		while(leftEncoder()<580)
		{
			startBaseTurn(-20, 127);
		}
		stopBase();
		rightEncoder(0);
		while(rightEncoder()<610)
		{
			startBase(93);
		}
		stopBase();
	}
	if(atonCode == 51) //Retreat From Right (Blue)
	{
		startBaseTurn(0, -127);
		wait1Msec(1000);
		stopBase();
		ClearTimer(T1);
		while(time1[T1] < 1000)
		{
			startBase(-127);
		}
		stopBase();
	}
	if(atonCode == 52) //Retreat From Left (Red)
	{
		startBaseTurn(-127, 0);
		wait1Msec(1000);
		stopBase();
		ClearTimer(T1);
		while(time1[T1] < 1000)
		{
			startBase(-127);
		}
		stopBase();
	}
}
