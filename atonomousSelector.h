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
int atonomousSelector()
{
	bool timeout = true;
	bool red, blue, hangingZone, middleZone;
	int lastSelection = 0;
	int screenRH = 1; //1
	int screenRM = 1; //2
	int screenBH = 1; //3
	int screenBM = 1; //4
	int atonCode = 0;
	string display;
	ClearTimer(T1);
	ClearTimer(T2);
	while(bIfiRobotDisabled && atonCode == 0) //15 Second Timeout
	{
		bLCDBacklight = true;									// Turn on LCD Backlight
		string mainBattery, backupBattery;
		if(SensorValue[atonSelector]<=573 && SensorValue[atonSelector]>=0 && atonCode == 0) //Red Hanging Zone
		{
			if(lastSelection != 1)
			{
				clearLCD();
				ClearTimer(T2);
			}
			lastSelection = 1;
			//
			if(strncmp(line1 , "<     Lock     >", 16) != 0)
			{
				displayLCDCenteredString(1, "<     Lock     >");
				sprintf(line1, "<     Lock     >");
			}
			//
			if(nLCDButtons == rightButton)
			{
				waitRelease();
				screenRH++;
			}
			else if(nLCDButtons == leftButton)
			{
				waitRelease();
				screenRH--;
			}
			if(screenRH == -1)
			{
				screenRH = 2;
			}
			else if(screenRH == 3)
			{
				screenRH = 1;
			}
			if(screenRH == 1)
			{
				//
				if(strncmp(line0 , "<     Hang      ", 16) != 0)
				{
					displayLCDCenteredString(0, "<     Hang      ");
					sprintf(line0, "<     Hang      ");
				}
				//
			}
			else if(screenRH == 2)
			{
				//
				if(strncmp(line0 , "< Move Big Ball ", 16) != 0)
				{
					displayLCDCenteredString(0, "< Move Big Ball ");
					sprintf(line0, "< Move Big Ball ");
				}
				//
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					red = true;
					blue = false;
					hangingZone = true;
					middleZone = false;
					atonCode = atonEncode(red, blue, hangingZone, middleZone, screenRH);
				}
			}
		}
		else if(SensorValue[atonSelector]>573 && SensorValue[atonSelector]<=1228 && atonCode == 0) //Red Middle Zone
		{
			if(lastSelection != 2)
			{
				clearLCD();
				ClearTimer(T2);
			}
			lastSelection = 2;
			//
			if(strncmp(line1 , "      Lock      ", 16) != 0)
			{
				displayLCDCenteredString(1, "      Lock      ");
				sprintf(line1, "      Lock      ");
			}
			//
			if(screenRM == 1)
			{
				//
				if(strncmp(line0 , "< Push Big Ball ", 16) != 0)
				{
					displayLCDCenteredString(0, "< Push Big Ball ");
					sprintf(line0, "< Push Big Ball ");
				}
				//
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					red = true;
					blue = false;
					hangingZone = false;
					middleZone = true;
					atonCode = atonEncode(red, blue, hangingZone, middleZone, screenRM);
				}
			}
		}
		else if(SensorValue[atonSelector]>1228 && SensorValue[atonSelector]<=2294) //Battery Levels
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
					atonCode = 61;
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
		else if(SensorValue[atonSelector]<=3522 && SensorValue[atonSelector]>2294 && atonCode == 0) //Blue Middle
		{
			if(lastSelection != 3)
			{
				clearLCD();
				ClearTimer(T2);
			}
			lastSelection = 3;
			//
			if(strncmp(line1 , "      Lock      ", 16) != 0)
			{
				displayLCDCenteredString(1, "      Lock      ");
				sprintf(line1, "      Lock      ");
			}
			//
			if(screenBM == 1)
			{
				//
				if(strncmp(line0 , " Push Big Ball >", 16) != 0)
				{
					displayLCDCenteredString(0, " Push Big Ball >");
					sprintf(line0, " Push Big Ball >");
				}
				//
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					red = false;
					blue = true;
					hangingZone = false;
					middleZone = true;
					atonCode = atonEncode(red, blue, hangingZone, middleZone, screenBM);
				}
			}
		}
		else if(SensorValue[atonSelector]>3522 && SensorValue[atonSelector]<=4095 && atonCode == 0) //Blue Hang
		{
			if(lastSelection != 4)
			{
				clearLCD();
				ClearTimer(T2);
			}
			lastSelection = 4;
			//
			if(strncmp(line1 , "<     Lock     >", 16) != 0)
			{
				displayLCDCenteredString(1, "<     Lock     >");
				sprintf(line1, "<     Lock     >");
			}
			//
			if(nLCDButtons == rightButton)
			{
				waitRelease();
				screenBH++;
			}
			else if(nLCDButtons == leftButton)
			{
				waitRelease();
				screenBH--;
			}
			if(screenBH == -1)
			{
				screenBH = 2;
			}
			else if(screenBH == 3)
			{
				screenBH = 1;
			}
			if(screenBH == 1)
			{
				//
				if(strncmp(line0 , "      Hang     >", 16) != 0)
				{
					displayLCDCenteredString(0, "      Hang     >");
					sprintf(line0, "      Hang     >");
				}
				//
			}
			else if(screenBH == 2)
			{
				//
				if(strncmp(line0 , " Move Big Ball >", 16) != 0)
				{
					displayLCDCenteredString(0, " Move Big Ball >");
					sprintf(line0, " Move Big Ball >");
				}
				//
			}
			if(nLCDButtons == centerButton)
			{
				waitRelease();
				if(confirm())
				{
					red = false;
					blue = true;
					hangingZone = true;
					middleZone = false;
					atonCode = atonEncode(red, blue, hangingZone, middleZone, screenBH);
				}
			}
		}
		if(time1[T2] < 5000)
		{
			ClearTimer(T1);
		}
	}
	if(timeout && atonCode == 0)
	{
		for(int i=0;i<4;i++)
		{
			displayLCDCenteredString(0, "Timeout!");
			wait10Msec(75);
			clearLCDLine(0);
			wait10Msec(50);
		}
		atonCode = 0;
	}
	bLCDBacklight = false;
	return atonCode;
}
