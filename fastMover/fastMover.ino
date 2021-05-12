/*
 Name:		fastMover.ino
 Created:	5/12/2021 11:45:22 PM
 Author:	amird
*/

// the setup function runs once when you press reset or power the board
void setup() {
	setup_7seg();
	neoSetup();
	setup_controller();
	startWaitingForNewGame();
}

// the loop function runs over and over again until power down or reset
void loop() {
	gameManager_SM();
}
