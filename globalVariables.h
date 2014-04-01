#pragma systemFile

const int maxSpeed = 127;
const int minSpeed = -127;
const float MAINBATTERYTHRESHOLD = 7.2;
const float SECONDBATTERYTHRESHOLD = 7.2;
const float BACKUPBATTERYTHRESHOLD = 9;
int powerExpanderLevel;
bool IMEFAILURE = false;
int autonNumber;
string parameter;
string line1;
string line0;
int MOD = 1;
bool intakeOn = false;
bool intakeBtnReleased = false;

int liftBtnUpLastState;
int liftBtnDownLastState;

bool armIsDown = true;
int threshold = 1852;

typedef enum
{
	none = 00,
	redHanging = 10,
	redMiddle = 20,
	blueHanging = 30,
	blueMiddle = 40,
}autonZoneCode;

typedef enum
{
	none = 0,
	hang = 1,
	stash = 2,
	moveBigBalls = 3,
}autonCode;

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
