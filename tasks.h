task liftArmLimiter()
{
	while(true)
	{
		if(SensorBoolean[liftArmDown])
		{
			if(motor[liftTopRight] < 0)
			{
				stopLiftArm();
			}
			liftArmEncoderReset();
			lift.isDown = true;
		}
		else if(SensorValue[liftArmEncoder] > lift.maxHeight)
		{
			if(motor[liftTopRight] > 0)
			{
				stopLiftArm();
			}
			startLiftArm(-127);
			lift.isMax = true;
		}
		else if(lift.isMax && SensorValue[liftArmEncoder] < lift.maxHeight)
		{
			stopLiftArm();
			lift.isMax = true;
		}
		else
		{
			lift.isMax = false;
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
	}
}
