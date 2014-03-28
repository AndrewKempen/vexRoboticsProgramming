const int maxSpeed = 127;
const int minSpeed = -127;
const float MAINBATTERYTHRESHOLD = 7.2;
const float SECONDBATTERYTHRESHOLD = 7.2;
const float BACKUPBATTERYTHRESHOLD = 9;
int powerExpanderLevel;
bool IMEFAILURE = false;
int atonNumber;
string parameter;
string line1;
string line0;
int MOD = 1;
bool intakeOn = false;
bool intakeBtnReleased = false;

bool armIsDown = true;
int threshold = 1852;

struct{
	bool isDown;
	int maxHeight;
	bool isDown;
	bool isMax;
} liftStruct;
liftStruct lift;

void max() //Set Hanging Arm Maximum
{
	lift.maxHeight = 1790;
}
