#pragma config(StandardModel, "POC")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool IMEFAILURE = false;

int atonNumber;
string line1;
string line0;

int mod = 1;

bool intakeOn = false;
bool intakeBtnReleased = false;

#include "lcdFunctions.h"
#include "functions.h"
#include "atonomousSelector.h"
#include "atonomous.h"
#include "driverControl.h"
#include "programmingSkills.h"
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"

void pre_auton()
{
	bStopTasksBetweenModes = true;
	fullClear();
	max();
}

task autonomous()
{
	if(atonNumber == 61)
	{

	}
	else
	{
		aton(31);
	}
}

task usercontrol()
{
	driverControl(true);
}
