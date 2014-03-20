void progSkills()
{
	aton(12);
	aton(52);
	atonSetLiftArmDown();
	startIntake(-63);
	wait1Msec(500);
	SensorValue[ballLift] = 1;
	baseEncoderReset();
	lineFollow(true, 700, 55, 95);
	stopIntake();
	baseEncoderReset();
	lineFollowBack(false, 700);
	wait1Msec(2500);
	atonSetLiftArmDown();
	liftArmEncoderReset();
	startIntake(127);
	SensorValue[ballLift] = 1;
	rightEncoder(0);
	wait1Msec(4000);
	liftArmEncoderReset();
	startIntake(127);
	SensorValue[ballLift] = 0;
	rightEncoder(0);
	ClearTimer(T1);
	while(rightEncoder() < 1400 && time1[T1] < 6000)
	{
		if(abs(SensorValue[liftArmEncoder]) < 700)
		{
			startLiftArm(127);
		}
		else
		{
			stopLiftArm();
		}
		lineFollow1(63, 93);
	}
	stopBase();
	rightEncoder(0);
	ClearTimer(T1);
	while(abs(rightEncoder()) < 1400 && time1[T1] < 6000)
	{
		if(abs(SensorValue[liftArmEncoder]) < 700)
		{
			startLiftArm(127);
		}
		else
		{
			stopLiftArm();
		}
		lineFollow1(-63, -93);
	}
	stopBase();
	wait1Msec(3000);
	startLiftArm(110); //Hanging arm up
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

	/////////////////////////////
	//wait1Msec(500);
	//baseEncoderReset();
	//ClearTimer(T1);
	//while(rightEncoder() < 400 && time1[T1] < 4000)
	//{
	//	if(abs(SensorValue[liftArmEncoder]) < 700)
	//	{
	//		startLiftArm(127);
	//	}
	//	else
	//	{
	//		stopLiftArm();
	//	}
	//	lineFollow1(-63, -93);
	//}

	//stopIntake();
	//SensorValue[ballLift] = 1;
	//rightEncoder(0);
	//while(rightEncoder() <300)
	//{
	//	startBaseTurn(63, -63);
	//}
	//startIntake(-127);
	//stopBase();
	//wait1Msec(1500);
	//rightEncoder(0);
	//while(rightEncoder() < 330)
	//{
	//	startBaseTurn(-63, 63);
	//}
	//stopBase();
	//SensorValue[ballLift] = 0;
	//startIntake(127);
	//baseEncoderReset();
	//lineFollow(false, 1000, 63, 93);
	//stopBase();
	//wait10Msec(50);
	//baseEncoderReset();
	//stopIntake();
	//rightEncoder(0);
	//while(rightEncoder()<390)
	//{
	//	startBaseTurn(63, -63);
	//}
	//startIntake(50);
	//baseEncoderReset();
	//moveBase(1100, true, 100);
	//stopIntake();
	//SensorValue[ballLift] = 1;
	//wait1Msec(500);
	//baseEncoderReset();
	//moveBase(220, true, 63);
	//stopBase();
	//startIntake(-127);
	//wait10Msec(50);
	//startBaseTurn(-32, 63);
	//wait10Msec(50);
	//stopBase();
	//startIntake(-63);
	//wait10Msec(50);
	//aton(51);
	//atonSetLiftArmDown();
	//startIntake(-63);
	//wait1Msec(500);
	//SensorValue[ballLift] = 1;
	//baseEncoderReset();
	//lineFollow(true, 700, 55, 95);
	//stopIntake();
	//baseEncoderReset();
	//lineFollowBack(false, 700);
	//ClearTimer(T1);
	//while(time1[T1] < 1500)
	//{
	//	startBase(-127);
	//}
	//stopBase();
	//wait1Msec(2500);
	//SensorValue(ballLift) = 0;
	//aton(31);
}
