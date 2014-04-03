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
| 5      | Programing Skills 1 | Retreat From Right | Retreat From Left  |
+--------+---------------------+--------------------+--------------------+
*/
void hangingZone(bool red)
{

}

void auton(int autonomusCode)
{
	int zone = (autonomusCode/10);
	switch(zone)
	{
	case redHangingZone:
		switch(autonomusCode - zone)
		{
		case hangAuton:
			return;
		case moveBigBallAuton:
			return;
		default:
			writeDebugStreamLine("ERROR: Unexpected auton number at \"auton\"");
			return;
		}
		return;
	case redMiddleZone:

		return;
	case blueHangingZone:

		return;
	case blueMiddleZone:

		return;
	default:
		writeDebugStreamLine("ERROR: Unexpected zone number at \"auton\"");
		return;
	}
}
