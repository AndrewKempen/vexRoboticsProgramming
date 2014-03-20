void driverControl(bool infiniteLoop = true)
{
	int THRESHOLDD = 15;
	int MOD = 1;
	bool intakeOn = false;
	bool intakeBtnReleased = false;
	do
	{
		if(abs(vexRT[Ch3]) > THRESHOLDD) //Make it so that motors don't whine
		{
			motor[backLeft]  = (vexRT[Ch3]/MOD);
			motor[middleLeft] = (vexRT[Ch3]/MOD);
		}
		else //Stop motors from whineing
		{
			motor[backLeft]  = 0;
			motor[middleLeft] = 0;
		}
		if(abs(vexRT[Ch2]) > THRESHOLDD) //Make it so that motors don't whine
		{
			motor[backRight] = (vexRT[Ch2])/MOD;
			motor[middleRight] = (vexRT[Ch2])/MOD;
		}
		else //Stop motors from whineing
		{
			motor[backRight] = 0;
			motor[middleRight] = 0;
		}
		if(vexRT[Btn5U] == 1 && abs(SensorValue[liftArmEncoder]) <= lift.maxHeight) //liftArm up
		{
			startLiftArm(maxSpeed/MOD);
		}
		else if(vexRT[Btn5D] == 1  && SensorValue[liftArmDown] != 1) //liftArm down
		{
			startLiftArm(minSpeed/MOD);
		}
		else
		{
			stopLiftArm(); //Stop lift arm
		}
		if(SensorValue[liftArmDown] == 1) //If the lift arm is down, reset the encoder
		{
			SensorValue[liftArmEncoder] = 0;
		}
		if(vexRT[Btn8U] == 1 && armIsDown) //ballArm up
		{
			ballArmToggle();
		}
		else if(vexRT[Btn8D] == 1 && !armIsDown) //ballArm down
		{
			ballArmToggle();
		}
		if(vexRT[Btn7L] == 1) //Manual overide for intake funtions
		{
			if(vexRT[Btn6U] == 1) //Intake
			{
				startIntake(maxSpeed);
			}
			else if(vexRT[Btn6D] == 1) //Outake
			{
				startIntake(minSpeed);
			}
			else //Stop intake
			{
				stopIntake();
			}
		}
		else
		{
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
			if(SensorValue[intakeFull] == 1 && intakeBtnReleased) //Intake is full and the button has been released
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
				startIntake(minSpeed);
				intakeOn = false;
				intakeBtnReleased = false;
			}
			else if(!intakeOn) //Stop the intake
			{
				stopIntake();
			}
		}

	}
	while(infiniteLoop); //Infinate loop or not - This makes it possible for there to be a loop outside this funtion that controls it
		                   // i.e. A small program that displays the distance that the encoders are reading
}
