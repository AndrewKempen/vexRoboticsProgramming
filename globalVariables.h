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

const int	noZone = 00;
const int	redHangingZone = 10;
const int	redMiddleZone = 20;
const int	blueHangingZone = 30;
const int	blueMiddleZone = 40;
const int	noAuton = 0;
const int	hangAuton = 1;
const	int stashAuton = 2;
const int	moveBigBallAuton = 3;

struct{
	bool isDown;
	int maxHeight;
	int stashHeight;
	int tipHeight;
	bool isDown;
	bool isMax;
	bool PIDon;
	bool auton;
	int requestedLocation;
	int error;
	int lastError;
	float kp;
	float kd;
} liftStruct;
liftStruct lift;

void liftValues() //Set Hanging Arm Maximum
{
	lift.maxHeight = 1790;
}
