#pragma systemfile
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
	int lastScreen = 0;
	int autonCode = 0;
	int screen = 1;
	string display;
	string mainBattery, backupBattery;
	ClearTimer(T1);
	ClearTimer(T2);
	while(autonCode == 0 && time1[T1] < 15000 && vexRT[Btn7U] != 1 && vexRT[Btn7UXmtr2] != 1) //15 Second Timeout
	{
		bLCDBacklight = true;									// Turn on LCD Backlight
		screen = lcdScreen(screen, 2);
		if(screen == 1)
		{
			if(lastScreen != 1)
			{
				clearLCD();
				ClearTimer(T1);
			}
			lastScreen = 1;
			if(SensorBoolean[isRedAlliance] && SensorBoolean[isHangingZone])
			{
				parameter = "< Hanging Zone  ";
				lcdPrint(0);
			}
			else if(!SensorBoolean[isRedAlliance] && SensorBoolean[isHangingZone])
			{
				parameter = "  Hanging Zone >";
				lcdPrint(0);
			}
			else if(SensorBoolean[isRedAlliance] && !SensorBoolean[isHangingZone])
			{
				parameter = "<  Middle Zone  ";
				lcdPrint(0);
			}
			else if(!SensorBoolean[isRedAlliance] && !SensorBoolean[isHangingZone])
			{
				parameter = "   Middle Zone >";
				lcdPrint(0);
			}

			if(SensorBoolean[isHangingZone] && SensorBoolean[isAutonTwo])
			{
				parameter = "  >Move Balls<  ";
				lcdPrint(1);
			}
			else if(SensorBoolean[isHangingZone] && !SensorBoolean[isAutonTwo])
			{
				parameter = "     >Hang<     ";
				lcdPrint(1);
			}
			else if(!SensorBoolean[isHangingZone] && !SensorBoolean[isAutonTwo])
			{
				parameter = "  >Push Balls<  ";
				lcdPrint(1);
			}
			else if(!SensorBoolean[isHangingZone] && SensorBoolean[isAutonTwo])
			{
				parameter = "     >Stash<    ";
				lcdPrint(1);
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				ClearTimer(T1);
				if(confirm())
				{
					autonCode = autonEncode(SensorBoolean[isRedAlliance], !SensorBoolean[isRedAlliance], SensorBoolean[isHangingZone], !SensorBoolean[isHangingZone], (SensorValue[isAutonTwo] + 1));
				}
				else
				{
					screen = 2;
					line0 = "";
					line1 = "";
				}
			}
		}
		if(screen == 2) //Battery Levels
		{
			if(lastScreen != 2)
			{
				clearLCD();
				ClearTimer(T1);
			}
			lastScreen = 2;
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
	}
	if(autonCode == 0)
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
