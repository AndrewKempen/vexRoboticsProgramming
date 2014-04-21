void driverControl(bool infiniteLoop = true)
{
	int THRESHOLDD = 15;
	int MOD = 1;
	bool intakeOn = false;
	bool intakeBtnReleased = false;
	do
	{
		if(abs(liftEncoder()) > lift.tipHeight)
		{
			MOD = 3;
		}
		else
		{
			MOD = 1;
		}
		if(abs(vexRT[Ch3]) > THRESHOLDD)
		{
			motor[backLeft]  = (vexRT[Ch3]/MOD);
			motor[frontLeft] = (vexRT[Ch3]/MOD);
		}
		else
		{
			motor[backLeft]  = 0;
			motor[frontLeft] = 0;
		}
		if(abs(vexRT[Ch2]) > THRESHOLDD)
		{
			motor[backRight] = (vexRT[Ch2])/MOD;
			motor[frontRight] = (vexRT[Ch2])/MOD;
		}
		else
		{
			motor[backRight] = 0;
			motor[frontRight] = 0;
		}
		if(vexRT[Btn6U] == 0 && intakeOn)
		{
			intakeBtnReleased = true;
		}
		if(vexRT[Btn6U] == 1 && !intakeBtnReleased && !intakeOn && time1[T3] > 1000)
		{
			startIntake(maxSpeed);
			intakeOn=true;
		}
		if(vexRT[Btn6U] == 1 && intakeBtnReleased)
		{
			intakeOn = false;
			intakeBtnReleased = false;
			stopIntake();
			ClearTimer(T3);
		}
		if(false && intakeBtnReleased)
		{
			intakeOn = false;
			intakeBtnReleased = false;
			stopIntake();
			ClearTimer(T1);
			ClearTimer(T3);
		}
		if(time1[T1] < 500 && time1[T1] != 0)
		{
			startIntake(maxSpeed);
		}
		if(time1[T1] > 500 && !intakeOn && vexRT[Btn6D] != 1)
		{
			stopIntake();
		}
		else if(vexRT[Btn6D] == 1)
		{
			startIntake(minSpeed/MOD);
			intakeOn = false;
			intakeBtnReleased = false;
		}
		else if(!intakeOn)
		{
			stopIntake();
		}
	}
	while(infiniteLoop);
}
