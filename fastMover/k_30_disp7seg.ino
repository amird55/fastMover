/* this sketch uses libraries:
* https://github.com/AlexisTM/ASCIIDic
* https://github.com/AlexisTM/NX7Seg
* need to download zip and install
*/
//
#include <ASCIIDic.h>
#include <NX7Seg.h>

#define CLK_DIO   8   // sclk
#define LATCH_DIO 7 //rclk
#define DATA_DIO  5  // dio
//bool reverse = false;
bool reverse = true;

nx7seg my4x7seg = nx7seg(LATCH_DIO, CLK_DIO, DATA_DIO, reverse);

void setup_7seg() {
    /* Set DIO pins to outputs */
    pinMode(LATCH_DIO, OUTPUT);
    pinMode(CLK_DIO, OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
}

/*
 * library supports also showing float(writeFloat) and INT(writeInt)
 * but it cannot reverse order of digits
 * and I had item that is reversed
 * .
 * This function uses the library function of printing chars
 * in order to reverse order of digits
 *
 * it is intended to show integers
 */
void showNum(int sec, int refreshTime) {
    my4x7seg.writeInt(sec);
    my4x7seg.refresh(refreshTime);
}
void showTimeNoWait(int min, int sec) {
    char data[4];
    data[0] = (min < 10) ? '0' : char('0' + min / 10);
    data[1] = char('0' + min % 10);
    data[2] = (sec < 10) ? '0' : char('0' + sec / 10);
    data[3] = char('0' + sec % 10);
    //Serial.println(data);
    my4x7seg.write(data, 4);
    my4x7seg.refresh(1000);
    //my4x7seg.send();
}
void showLevel(int gameLevel, int refresh_time) {
    char* data = "----";
    data[1] = char('0' + gameLevel % 10);
    data[2] = 'L';
    my4x7seg.write(data, 4);
    my4x7seg.refresh(refresh_time);
}
void showFinishedScore(int gameScore, int refresh_time) {
    char* data = "----";
    data[2] = char('0' + gameScore % 10);
    if (gameScore >= 10) {
        data[1] = char('0' + (gameScore / 10) % 10);
    }
    my4x7seg.write(data, 4);
    my4x7seg.refresh(refresh_time);
}
void displayOFF() {
    char* data = "    ";
    my4x7seg.write(data, 4);
    my4x7seg.refresh(1500);
}
void displayVoid(int refresh_time) {
    char* data = "----";
    my4x7seg.write(data, 4);
    my4x7seg.refresh(refresh_time);
}



