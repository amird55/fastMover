#define pinBtn_R 2
#define pinBtn_G 12
#define pinControllerLed_R 3
#define pinControllerLed_G 4

#define pinVrX A6
#define pinVrY A5

struct FullBtnData {
	int Pin;
	bool isPressed;
};
FullBtnData BtnRed = { pinBtn_R,false };
FullBtnData BtnGreen = { pinBtn_G,false };

void setup_controller() {
	pinMode(BtnGreen.Pin, INPUT_PULLUP);
	pinMode(BtnRed.Pin, INPUT_PULLUP);
	pinMode(pinControllerLed_G, OUTPUT);
	pinMode(pinControllerLed_R, OUTPUT);
}
bool areBothButtonsPressed() {
	bool ret = false;
	if ((digitalRead(BtnRed.Pin) == LOW) && (digitalRead(BtnGreen.Pin) == LOW)) {
		ret = true;
	}
	return ret;
}
bool isRedBtnPressed() {
	bool ret = false;
	int val = digitalRead(BtnRed.Pin);
	if (val == LOW) {
		if (!BtnRed.isPressed) {
			ret = true;
		}
		BtnRed.isPressed = true;
	} else {
		BtnRed.isPressed = false;
	}
	return ret;
}
bool isGreenBtnPressed() {
	bool ret = false;
	if (digitalRead(BtnGreen.Pin) == LOW) {
		if (!BtnGreen.isPressed) {
			ret = true;
		}
		BtnGreen.isPressed = true;
	} else {
		BtnGreen.isPressed = false;
	}
	return ret;
}
void showControllerLight_Green(int prd) {
	digitalWrite(pinControllerLed_G, HIGH);
	delay(prd);
	digitalWrite(pinControllerLed_G, LOW);
}
void showControllerLight_Red(int prd) {
	digitalWrite(pinControllerLed_R, HIGH);
	delay(prd);
	digitalWrite(pinControllerLed_R, LOW);
}

//----- joystick-------
#define TOP				10
#define TOP_RIGHT		11
#define RIGHT			1
#define BOTTOM_RIGHT	21
#define BOTTOM			20
#define BOTTOM_LEFT		22
#define LEFT			2
#define TOP_LEFT		12
#define CENTER			0
int GetJstickPos() {
	int pos = 0;
	int vx = analogRead(pinVrX);
	int vy = analogRead(pinVrY);
	if (vx > 750) {
		pos += 1;//right
	} else if (vx < 250) {
		pos += 2;//left
	}

	if (vy > 750) {
		pos += 20;//bottom
	} else if (vy < 250) {
		pos += 10;//top
	}
	Serial.println("vx=" + String(vx) + " vy=" + String(vy)+" pos="+String(pos));
	return pos;
}