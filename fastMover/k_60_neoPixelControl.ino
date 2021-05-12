
#include <Adafruit_NeoPixel.h>
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define MATRIX_TOTAL 64

#define PIN 11         // Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MATRIX_TOTAL, PIN, NEO_GRB + NEO_KHZ800);

#define MARKER_LEN  7
#define POS_NUM     8
int markers[POS_NUM][MARKER_LEN] = {
    { 57,58,59,60,61,62,62 },//top
    {1,2,3,4,5,6,6},//bottom
    {8,16,24,32,40,48,48},//right
    {15,23,31,39,47,55,55},//left
    {59,58,57,56,48,40,32},//top-right
    {60,61,62,63,55,47,39},//top left
    {3,2,1,0,8,16,24},//bottom-right
    {4,5,6,7,15,23,31} //bottom-left
};
int PosValue[POS_NUM] = { TOP,BOTTOM,RIGHT,LEFT,TOP_RIGHT,TOP_LEFT,BOTTOM_RIGHT,BOTTOM_LEFT };
int currentPos = 0;
int currColorIndex = 0;
int middleRect[4] = { 27,28,35,36 };

uint32_t dotColors[3] = { strip.Color(10, 10, 10),
                            strip.Color(30, 0 ,0),
                            strip.Color(0, 30, 0) };
void neoSetup() {
    strip.begin();
}
void slowLightAll(uint32_t clr) {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, clr);
        strip.show();
        delay(20);
    }
}
void slowOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
        strip.show();
        delay(40);
    }
    delay(200);
}
void MatOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
    }
    strip.show();
}
void lightPosition(int pos) {
    int pixelNum;
    for (short k = 0; k < MARKER_LEN; k++) {
        pixelNum = markers[pos][k];
        strip.setPixelColor(pixelNum, dotColors[currColorIndex]);
    }
    strip.show();
}
void FeedbackGreen() {
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 30, 0));
    }
    strip.show();
    delay(300);
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 0, 0));
    }
    strip.show();
}
void FeedbackRed() {
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(30, 0, 0));
    }
    strip.show();
    delay(500);
    for (int k = 0; k < 4; k++) {
        strip.setPixelColor(middleRect[k], strip.Color(0, 0, 0));
    }
    strip.show();
}
