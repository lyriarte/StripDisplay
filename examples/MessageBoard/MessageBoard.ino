#define FONT_5x8_FIXED_MEDIUM
#include <StripDisplay.h>
XBMFont * fontP = &fixedMedium_5x8;

#define STRIPLED_GPIO 5
#define STRIPLED_W	32
#define STRIPLED_H	8

CRGB leds[STRIPLED_W*STRIPLED_H];

StripDisplay strip(STRIPLED_GPIO, STRIPLED_W, STRIPLED_H, WRAP_COLUMNS, leds);

// message board globals
String message = "";
CRGB fg(4,2,1);
CRGB bg(0,0,1);
#define START_OFFSET -10
int offset = START_OFFSET;
// time managemet globals
#define SCROLL_MS 50;
int update_ms = 0;


// initial FastLED and StripDisplay setup
void setup() {
	FastLED.addLeds<NEOPIXEL,STRIPLED_GPIO>(leds, STRIPLED_W*STRIPLED_H);
	strip.setup(fontP);
	Serial.begin(9600);
	Serial.println(String(STRIPLED_W*STRIPLED_H) + String(" leds on gpio ") + String(strip.getGpio()));
// initial message setup
	strip.setFgColor(fg);
	strip.setBgColor(bg);
	updateMessageText("Hello");
}

// setup new message text
void updateMessageText(String text) {
	message = text;
	offset = START_OFFSET;
	strip.setText(text);
}

// display and scroll message
void displayMessageText() {
	if (offset > strip.getTextWidth())
		offset = START_OFFSET;
	strip.displayText(offset);
	offset++;
}

// get message from serial if any
void getMessageSerial() {
	if (Serial.available())
		updateMessageText(Serial.readString());
}

void loop() {
	// mesure current time
	int current_ms = millis();
	// poll for message on serial port
	getMessageSerial();
	// scroll and display message at a fixed time rate
	if (update_ms <= current_ms) {
		displayMessageText();
		update_ms = current_ms + SCROLL_MS;
	}
	else {
		FastLED.delay(update_ms - current_ms);
	}
}
