#pragma systemfile

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

void WARNINGREMOVER()
{
	if(leftButton == rightButton){}
}

void clearLCD(int line = 2) //Clear LCD
{
	if(line != 1 && line != 0)
	{
		clearLCDLine(0);
		clearLCDLine(1);
	}
	else
	{
		clearLCDLine(line);
	}
}

void waitPress(int btnPressed = 5)
{
	bool exit = false;
	while(!exit)
	{
		while(nLCDButtons == 0){}
		if(btnPressed == 5 || btnPressed == nLCDButtons)
		{
			exit = true;
		}
	}
	wait1Msec(5);
}

void waitRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

bool confirm()
{
	bool confirm = false;
	float timeRemaining;
	string display;
	waitRelease();
	ClearTimer(T3);
	while(time1[T3] < 5000 && !confirm)
	{
		clearLCD();
		timeRemaining = 5-(time1[T3]*0.001);
		sprintf(display, "%1.1f%c", timeRemaining);
		displayLCDCenteredString(0, display);
		displayLCDCenteredString(1, "Confirm?");
		if(nLCDButtons == centerButton)
		{
			confirm = true;
		}
		wait1Msec(1);
	}
	return confirm;
}

void lcdPrint(int line = 1)
{
	if(line != 0 && line != 1)
	{
		writeDebugStreamLine("ERROR: LCD Print Recived Parameter Besides 0 or 1");
	}
	if(line == 0)
	{
		if(strncmp(line0 , parameter, 16) != 0)
		{
			ClearTimer(T1);
			displayLCDCenteredString(0, parameter);
			writeDebugStream("INFO: Printing \"");
			writeDebugStream(parameter);
			writeDebugStreamLine("\" to LCD Line 0");
			sprintf(line0, parameter);
		}
	}
	else if(line == 1)
	{
		if(strncmp(line1 , parameter, 16) != 0)
		{
			ClearTimer(T1);
			displayLCDCenteredString(1, parameter);
			writeDebugStream("INFO: Printing \"");
			writeDebugStream(parameter);
			writeDebugStreamLine("\" to LCD Line 1");
			sprintf(line1, parameter);
		}
	}
}

int lcdScreen(int screen, int maxScreen = 2)
{
	if(nLCDButtons == rightButton)
	{
		waitRelease();
		screen++;
	}
	else if(nLCDButtons == leftButton)
	{
		waitRelease();
		screen--;
	}
	if(screen < 0)
	{
		screen = maxScreen;
	}
	else if(screen > maxScreen)
	{
		screen = 1;
	}
	return screen;
}
