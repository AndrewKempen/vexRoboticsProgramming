#pragma systemFile
task liftArmLimiter()
{
	while(true)
	{
		lift.lastLocation = lift.location;
		lift.location = liftEncoder();
		if(SensorBoolean[liftDown])
		{
			if(motor[liftTopRight] < 0)
			{
				stopLiftArm();
				writeDebugStreamLine("INFO: Lift Arm Still Moving Down, Jamming at \"liftArmLimiter\"");
			}
			liftArmEncoderReset();
			lift.isDown = true;
		}
		else if(lift.location > lift.maxHeight)
		{
			if(motor[liftTopRight] > 0)
			{
				stopLiftArm();
				writeDebugStreamLine("INFO: Lift Arm Still Moving Up, Jamming at \"liftArmLimiter\"");
			}
			startLiftArm(-127);
			lift.isMax = true;
		}
		if(lift.isMax && liftEncoder() < lift.maxHeight)
		{
			lift.isMax = false;
		}
		if(lift.isDown && !SensorBoolean[liftDown])
		{
			lift.isDown = false;
		}
		if(motor[liftTopRight] == 127 && lift.location - lift.lastLocation < 5)
		{
			writeDebugStreamLine("ERROR: Lift Arm Jammed!");
			lift.isJammed = true;
		}
		wait1Msec(10);
	}
}

task liftArmToDown()
{
	writeDebugStreamLine("INFO: \"liftArmToDown\" Task Started");
	liftBtnUpLastState = 1;
	liftBtnDownLastState = 1;
	while(!liftArmButtonEvent() && !SensorBoolean[liftDown])
	{
		startLiftArm(-127);
		wait10Msec(10);
	}
	stopLiftArm();
	writeDebugStreamLine("INFO: \"liftArmToDown\" Task Done");
}

task liftControl()
{
	bool liftOn = false;
	bool liftBtnReleased = false;
	while(true)
	{
		if(vexRT[Btn5U] == 0 && liftOn)
		{
			liftBtnReleased = true;
		}
		if(vexRT[Btn5U] == 1 && !liftBtnReleased && !liftOn && time1[T2] > 1000)
		{
			lift.isPIDon = false;
			lift.isManualPos = true;
			lift.requestedLocation = 250;
			liftOn = true;
		}
		if(vexRT[Btn5U] == 1 && liftBtnReleased)
		{
			liftOn = false;
			liftBtnReleased = false;
			lift.isPIDon = false;
			lift.isManualPos = true;
			lift.requestedLocation = lift.stashHeight;
			ClearTimer(T2);
		}
		else if(vexRT[Btn8D] == 1)
		{
			liftOn = false;
			liftBtnReleased = false;
			lift.isPIDon = false;
			lift.isManualPos = false;
			startLiftArm(-127);
			liftOn = false;
			liftBtnReleased = false;
		}
		if(vexRT[Btn8U] == 1)
		{
			liftOn = false;
			liftBtnReleased = false;
			lift.isPIDon = false;
			lift.isManualPos = false;
			startLiftArm(maxSpeed);
		}
		else if(vexRT[Btn5D] == 1)
		{
			liftOn = false;
			liftBtnReleased = false;
			lift.isPIDon = false;
			lift.isManualPos = true;
			lift.requestedLocation = 0;
		}
		if(vexRT[Btn5UXmtr2] == 1)
		{
			if(abs(vexRT[Ch3Xmtr2]) > 15)
			{
				lift.isPIDon = false;
				liftSpeed = vexRT[Ch3Xmtr2];
			}
		}
		else if(!lift.isPIDon && !lift.isManualPos)
		{
			wait10Msec(5);
			lift.requestedLocation = liftEncoder();
			lift.isPIDon = true;
		}
		else if(!lift.isPIDon && lift.isManualPos)
		{
			lift.isPIDon = true;
		}
		wait10Msec(1);
	}
}
