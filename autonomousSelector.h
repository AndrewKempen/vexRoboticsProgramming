/*
+--------+-------------------+-----------------------------------+
| Number | First Number (#0) | Second Number (0#)                |
+        +                   +-----------------------------------+
|        |                   | Hanging Zone | Middle Zone        |
+--------+-------------------+--------------+--------------------+
| 0      | No Aton           | No Aton      | No Aton            |
+--------+-------------------+--------------+--------------------+
| 1      | Red Hanging Zone  | Hang         | Push Big Balls Off |
+--------+-------------------+--------------+--------------------+
| 2      | Red Middle Zone   |              |                    |
+--------+-------------------+--------------+--------------------+
| 3      | Blue Hanging Zone |              |                    |
+--------+-------------------+--------------+--------------------+
| 4      | Blue Middle Zone  |              |                    |
+--------+-------------------+--------------+--------------------+
*/
int autonomousSelector()
{
	bool timeout = true;
	int lastSelection = 0;
	int autonCode = 0;
	string display;
	ClearTimer(T1);
	ClearTimer(T2);
	if(SensorBoolean[isautonSelectFailure])
	{
		if(SensorBoolean[isredAlliance] && SensorBoolean[ishangingZone])
			autonCode = 11;
		else if(SensorBoolean[isredAlliance] && !SensorBoolean[ishangingZone])
			autonCode = 21;
		else if(!SensorBoolean[isredAlliance] && SensorBoolean[ishangingZone])
			autonCode = 31;
		else if(!SensorBoolean[isredAlliance] && !SensorBoolean[ishangingZone])
			autonCode = 41;
	}
	while(bIfiRobotDisabled && autonCode == 0) //15 Second Timeout
	{
		bLCDBacklight = true;									// Turn on LCD Backlight
		string mainBattery, backupBattery;
		if(SensorValue[autonSelector]<=573 && SensorValue[autonSelector]>=0 && autonCode == 0) //Red Hanging Zone
		{
			if(lastSelection != 1)
			{
				clearLCD();
				ClearTimer(T2);
			}
			lastSelection = 1;
			screen = lcdScreen(2);
			if(screen == 1)
			{
				parameter = "<     Hang      ";
				lcdPrint(0);
			}
			else if(screen == 2)
			{
				parameter = "< Move Big Ball ";
				lcdPrint(0);
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					autonCode = autonEncode(true, false, true, false, screen);
				}
			}
		}
		else if(SensorValue[autonSelector]>573 && SensorValue[autonSelector]<=1228 && autonCode == 0) //Red Middle Zone
		{

		}
		else if(SensorValue[autonSelector]>1228 && SensorValue[autonSelector]<=2294) //Battery Levels
		{
			if(lastSelection != 5)
			{
				clearLCD();
			}
			lastSelection = 5;
			sprintf(line0, "");
			sprintf(line1, "");
			displayLCDString(0, 0, "Primary: ");
			sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
			displayNextLCDString(mainBattery);
			displayLCDString(1, 0, "Backup: ");
			sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
			displayNextLCDString(backupBattery);
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					autonCode = 61;
				}
			}
			else if(nLCDButtons == rightButton)
			{
				waitRelease();
				ClearTimer(T1);
				int right = SensorValue(lineRight);
				int middle = SensorValue(lineMiddle);
				int left = SensorValue(lineLeft);
				if((right>middle) && (left>middle))
				{
					threshold = (((right+left)/2)+middle)/2;
				}
				clearLCD();
				displayLCDCenteredString(0, "Threshold");
				sprintf(display, "%4.0f%c", threshold);
        displayLCDCenteredString(1, display);
        wait1Msec(4000);
			}
		}
		else if(SensorValue[autonSelector]<=3522 && SensorValue[autonSelector]>2294 && autonCode == 0) //Blue Middle
		{

		}
		else if(SensorValue[autonSelector]>3522 && SensorValue[autonSelector]<=4095 && autonCode == 0) //Blue Hang
		{

		}
		if(time1[T2] < 5000)
		{
			ClearTimer(T1);
		}
	}
	if(timeout && autonCode == 0)
	{
		for(int i=0;i<4;i++)
		{
			displayLCDCenteredString(0, "Timeout!");
			wait10Msec(50);
			clearLCDLine(0);
			wait10Msec(50);
		}
		autonCode = 0;
	}
	bLCDBacklight = false;
	return autonCode;
}
