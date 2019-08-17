
#include <Wire.h>
#include <Adafruit_WS2801.h>

int dataPin = 2;
int clockPin = 3;
int Strip = 3;

uint8_t red;
uint8_t green;
uint8_t blue;

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(Strip, dataPin, clockPin);

void setup() {
	strip.begin();
	Wire.begin(0x55);// join i2c bus with address #55
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);
    strip.setPixelColor(0, Color(255,0,0));
	
    strip.show();

int test= 16;
Serial.println(String(test)+"0");

}
void loop() {


}

uint32_t Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = g;
	c <<= 8;
	c |= b;
	c <<= 8;
	c |= r;
	return c;
}

void receiveEvent(int howMany) {
	while (0 < Wire.available()) {
		uint8_t data = Wire.read();   // read register
		if (data == 0x01) {
			data = Wire.read();   // read color value
			blue = data << 4;
			data = Wire.read();   // read color value
			green = data << 4;
			data = Wire.read();   // read color value
			red = data << 4;
		}
	}

	strip.setPixelColor(2, Color(red,green,blue));
	strip.show();

	Serial.print(red);
	Serial.print(" ");
	Serial.print(green);
	Serial.print(" ");
	Serial.println(blue);

}