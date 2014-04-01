#pragma systemFile

task liftArmLimiter()
{
	while(true)
	{
		if(SensorBoolean[liftArmDown])
		{
			writeDebugStreamLine("INFO: Lift Arm Stopped at Low at \"liftArmLimiter\"");
			if(motor[liftTopRight] < 0)
			{
				stopLiftArm();
				writeDebugStreamLine("INFO: Lift Arm Still Moving Down, Jamming at \"liftArmLimiter\"");
			}
			liftArmEncoderReset();
			lift.isDown = true;
		}
		else if(SensorValue[liftArmEncoder] > lift.maxHeight)
		{
			writeDebugStreamLine("INFO: Lift Arm Stopped at High at \"liftArmLimiter\"");
			if(motor[liftTopRight] > 0)
			{
				stopLiftArm();
				writeDebugStreamLine("INFO: Lift Arm Still Moving Up, Jamming at \"liftArmLimiter\"");
			}
			startLiftArm(-127);
			lift.isMax = true;
		}
		if(lift.isMax && SensorValue[liftArmEncoder] < lift.maxHeight)
		{
			lift.isMax = false;
		}
		if(lift.isDown && !SensorBoolean[liftArmDown])
		{
			lift.isDown = false;
		}
		wait1Msec(10);
	}
}

task liftArmToHangPos()
{
	if(SensorValue[liftArmEncoder] < lift.maxHeight)
	{
		while(SensorValue[liftArmEncoder] < lift.maxHeight)
		{
			startLiftArm(127);
			wait1Msec(10);
		}
	}
	else if(SensorValue[liftArmEncoder] > lift.maxHeight)
	{
		writeDebugStreamLine("ERROR: Lift Arm Higher Than Expected at \"liftArmToHangPos\"");
	}
}

task liftArmToDown()
{
	writeDebugStreamLine("INFO: \"liftArmToDown\" Task Started");
	liftBtnUpLastState = 1;
	liftBtnDownLastState = 1;
	while(!liftArmButtonEvent() && !SensorBoolean[liftArmDown])
	{
		startLiftArm(-127);
		wait10Msec(10);
	}
	stopLiftArm();
	writeDebugStreamLine("INFO: \"liftArmToDown\" Task Done");
}
