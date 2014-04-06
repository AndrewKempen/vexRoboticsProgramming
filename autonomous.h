#pragma systemFile
/*
+--------+---------------------+-----------------------------------------+
| Number | First Number (#0)   | Second Number (0#)                      |
+        +                     +-----------------------------------------+
|        |                     | Hanging Zone - 1   | Middle Zone - 2    |
+--------+---------------------+--------------------+--------------------+
| 0      | No Aton             | No Aton            | No Aton            |
+--------+---------------------+--------------------+--------------------+
| 1      | Red Hanging Zone    | Hang               | Push Big Balls Off |
+--------+---------------------+--------------------+--------------------+
| 2      | Red Middle Zone     | Big Ball Move      |                    |
+--------+---------------------+--------------------+--------------------+
| 3      | Blue Hanging Zone   |                    |                    |
+--------+---------------------+--------------------+--------------------+
| 4      | Blue Middle Zone    |                    |                    |
+--------+---------------------+--------------------+--------------------+
| 5      | Programing Skills   | Retreat From Right | Retreat From Left  |
+--------+---------------------+--------------------+--------------------+
*/

void hangingZoneHang(bool red)
{

}
void hangingZoneMoveBigBall(bool red)
{

}
void middleZoneStash(bool red)
{

}
void middleZoneGetBigBall(bool red)
{

}

void auton(int autonomusCode)
{
	bool red;
	int zone = (autonomusCode/10);
	if(zone == 1 || zone == 2)
	{
		red = true;
	}
	else
	{
		red = false;
	}
	if(zone == 1 || zone == 3)
	{
		switch(autonomusCode - (zone*10))
		{
		case hangAuton:
			hangingZoneHang(red);
			return;
		case moveBigBallAuton:
			hangingZoneMoveBigBall(red);
			return;
		default:
			writeDebugStreamLine("ERROR: Unexpected auton number at \"auton\"");
			return;
		}
	}
	else if(zone == 2 || zone == 4)
	{
		switch(autonomusCode - (zone*10))
		{
		case stashAuton:
			middleZoneStash(red);
			return;
		case getBigBallAuton:
			middleZoneGetBigBall(red);
			return;
		default:
			writeDebugStreamLine("ERROR: Unexpected auton number at \"auton\"");
			return;
		}
	}
	else
	{
		writeDebugStreamLine("ERROR: Unexpected zone number at \"auton\"");
	}
}
