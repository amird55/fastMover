#define WAITING_FOR_NEW_GAME	1
#define START_WAITING			2
#define START_NEW_GAME			3
#define PLAYING					4
short currState;

int BreakLong_min = 1400;
int BreakLong_max = 2400;
int LightLong_min = 800;
int LightLong_max = 1000;
int LightLong_min_quick = 600;
int LightLong_max_quick = 800;

int sectionLong;
long sectionStartTime;
bool sectionIsBreak;
int sectionPosition;

long gameLong = 60000;
long gameStartTime;
int gameScore;

void gameManager_SM() {
	switch (currState) {
	case START_WAITING:
		startWaitingForNewGame();
		currState = WAITING_FOR_NEW_GAME;
		break;
	case WAITING_FOR_NEW_GAME:
		blinkScore();
		if (areBothButtonsPressed()) {
			currState = START_NEW_GAME;
		}
		break;
	case START_NEW_GAME:
		StartGame();
		currState = PLAYING;
		break;
	case PLAYING:
		gameManager();
		break;
	}
}
void StartGame() {
	gameStartTime = millis();
	gameScore = 0;
}
void FinishGame() {
	currState = START_WAITING;
}
void gameManager() {
	showNum(gameScore, 50);
	if (millis() - gameStartTime >= gameLong) {
		FinishGame();
	} else {
		int Jpos = GetJstickPos();
		if (Jpos != CENTER) {
			if (PosValue[sectionPosition] == Jpos) {
				goodAns();
			} else {
				wrongAns();
			}
		}
		if (millis() - sectionStartTime >= sectionLong) {
			if (sectionIsBreak) {
				choosePosition();
				lightPosition(sectionPosition);
			} else {
				setBreak();
				MatOffAll();
			}
		}
	}
}
void choosePosition() {
	sectionLong = (gameScore > 8) ? random(LightLong_min_quick, LightLong_max_quick) : random(LightLong_min, LightLong_max);
	sectionPosition = random(POS_NUM);
	sectionIsBreak = false;
	sectionStartTime = millis();
}
void setBreak() {
	sectionLong = random(BreakLong_min, BreakLong_max);
	sectionPosition = CENTER;
	sectionIsBreak = true;
	sectionStartTime = millis();
}
void goodAns() {
	gameScore++;
	FeedbackGreen();
	setBreak();
}
void wrongAns() {
	if (gameScore > 0) {
		gameScore--;
	}
	FeedbackRed();
	setBreak();
}
//----- before start-------
bool blinkPartON;
int blinkRate = 500;
unsigned long lastToggleTimeForDisplay;
void startWaitingForNewGame() {
	lastToggleTimeForDisplay = millis();
	blinkPartON = true;
	currState = WAITING_FOR_NEW_GAME;
}
void blinkScore() {
	if (millis() - lastToggleTimeForDisplay >= blinkRate) {
		blinkPartON = !blinkPartON;
		lastToggleTimeForDisplay = millis();
	}
	if (blinkPartON) {
		showFinishedScore(gameScore, 50);
	} else {
		displayOFF();
	}
}
