const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

void WARNINGREMOVER()
{
	if(leftButton == rightButton){}
}

void clearLCD() //Clear LCD
{
	clearLCDLine(0);
	clearLCDLine(1);
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
