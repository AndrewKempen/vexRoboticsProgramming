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
		if(abs(vexRT[Ch3]) > THRESHOLDD) //Make it so that motors don't whine
		{
			motor[backLeft]  = (vexRT[Ch3]/MOD);
			motor[frontLeft] = (vexRT[Ch3]/MOD);
		}
		else //Stop motors from whineing
		{
			motor[backLeft]  = 0;
			motor[frontLeft] = 0;
		}
		if(abs(vexRT[Ch2]) > THRESHOLDD) //Make it so that motors don't whine
		{
			motor[backRight] = (vexRT[Ch2])/MOD;
			motor[frontRight] = (vexRT[Ch2])/MOD;
		}
		else //Stop motors from whineing
		{
			motor[backRight] = 0;
			motor[frontRight] = 0;
		}
		if(vexRT[Btn6U] == 0 && intakeOn) //If intake is on and intake button is released
		{
			intakeBtnReleased = true;
		}
		if(vexRT[Btn6U] == 1 && !intakeBtnReleased && !intakeOn && time1[T3] > 1000) //Intake
		{
			startIntake(maxSpeed);
			intakeOn=true;
		}
		if(vexRT[Btn6U] == 1 && intakeBtnReleased) //Intake button has been pressed after releaseing it so stop it
		{
			intakeOn = false;
			intakeBtnReleased = false;
			stopIntake();
			ClearTimer(T3);
		}
		if(false && intakeBtnReleased) //Intake is full and the button has been released
		{
			intakeOn = false;
			intakeBtnReleased = false;
			stopIntake();
			ClearTimer(T1);
			ClearTimer(T3);
		}
		if(time1[T1] < 500 && time1[T1] != 0) //Spin for an extra 0.5 sec to make sure bucky ball is in the intake securely
		{
			startIntake(maxSpeed);
		}
		if(time1[T1] > 500 && !intakeOn && vexRT[Btn6D] != 1) //Stop the intake
		{
			stopIntake();
		}
		else if(vexRT[Btn6D] == 1) //Outake
		{
			startIntake(minSpeed/MOD);
			intakeOn = false;
			intakeBtnReleased = false;
		}
		else if(!intakeOn) //Stop the intake
		{
			stopIntake();
		}
	}
	while(infiniteLoop); //Infinite loop or not - This makes it possible for there to be a loop outside this funtion that controls it
}	                 	 	 //i.e. A small program that displays the distance that the encoders are reading
