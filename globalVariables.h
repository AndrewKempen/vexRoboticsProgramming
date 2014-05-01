#pragma systemFile

const int maxSpeed = 127;
const int minSpeed = -127;
const float MAINBATTERYTHRESHOLD = 7.2;
const float SECONDBATTERYTHRESHOLD = 7.2;
const float BACKUPBATTERYTHRESHOLD = 9;
int powerExpanderLevel;
int autonNumber;
string parameter;
string line1;
string line0;
int MOD = 1;
bool intakeOn = false;
bool intakeBtnReleased = false;
int intakeSpeed = 0;
int liftSpeed = 0;

int liftBtnUpLastState;
int liftBtnDownLastState;

bool armIsDown = true;
int threshold = 1448;
int farThreshold = 2104;

const int	noZone = 00;
const int	redHangingZone = 10;
const int	redMiddleZone = 20;
const int	blueHangingZone = 30;
const int	blueMiddleZone = 40;
const int	noAuton = 0;
const int	hangAuton = 1;
const	int stashAuton = 2;
const int hangingZoneStashAuton = 3;
const int	moveBigBallAuton = 4;
const int getBigBallAuton = 5;

struct lift{
	bool isDown;
	int maxHeight;
	int stashHeight;
	int tipHeight;
	int location;
	int lastLocation;
	bool isDown;
	bool isMax;
	bool isPIDon;
	bool isManualPos;
	bool isJammed;
	float requestedLocation;
	float error;
	float lastError;
	float kp;
	float kd;
} liftStruct;
static liftStruct lift;


//struct{
//	float requestedLocation;
//	float error;
//	float lastError;
//} rightStruct;
//static rightStruct right;

//struct{
//	float requestedLocation;
//	float error;
//	float lastError;
//} leftStruct;
//static leftStruct left;

//struct{
//	bool isPIDon;
//	float kp;
//	float kd;
//} baseStruct;
//static baseStruct robot;

void liftPIDValues()
{
	lift.kp = 2;
	lift.kd = 0.4;
	lift.lastError = 0;
}
//void robotPIDValues()
//{
//	robot.kp = 0.19;
//	robot.kd = 0.11;
//	right.lastError = 0;
//	left.lastError = 0;
//}
void liftValues() //Set Hanging Arm Maximum
{
	liftPIDValues();
	//robotPIDValues();
	lift.maxHeight = 1820;
	lift.stashHeight = 1550;
	lift.tipHeight = 500;
}
