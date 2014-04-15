task liftArmPID()
{
	int speed;
	writeDebugStreamLine("INFO: \"liftArmPID\" Task Started");
	while(true)
	{
		if(lift.isPIDon)
		{
			if(lift.requestedLocation == 0)
			{
				if(!SensorBoolean[liftDown])
				{
					startLiftArm(-127);
				}
				else
				{
					stopLiftArm();
				}
			}
			else
			{
				lift.error = (lift.requestedLocation + 5) - liftEncoder();
				speed = clamp(lift.error*lift.kp + ((lift.lastError - lift.error)*lift.kd));
				if(speed < 15 && speed > 0)
					speed = 0;
				startLiftArm(speed);
				lift.lastError = lift.error;
			}
		}
		else
		{
			lift.error = 0;
			lift.lastError = 0;
		}
		wait10Msec(10);
	}
}

task robotPID()
{
	int speed;
	writeDebugStreamLine("INFO: \"robotPID\" Task Started");
	while(true)
	{
		if(robot.isPIDon)
		{
			right.error = (right.requestedLocation) - rightEncoder();
			speed = clamp(right.error*robot.kp + ((right.lastError - right.error)*robot.kd));
			if(speed < 15 && speed > 0)
				speed = 0;
			startRight(speed);
			right.lastError = right.error;
			//
			left.error = (left.requestedLocation) - leftEncoder();
			speed = clamp(left.error*robot.kp + ((left.lastError - left.error)*robot.kd));
			if(speed < 15 && speed > 0)
				speed = 0;
			startLeft(speed);
			left.lastError = left.error;
		}
		else
		{
			right.error = 0;
			right.lastError = 0;
			left.error = 0;
			left.lastError = 0;
		}
		wait10Msec(10);
	}
}
