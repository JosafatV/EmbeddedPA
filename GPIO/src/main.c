#include <stdio.h>
#include <stdlib.h>
#include <libserver.h>
#include <libraspio.h>

int main() {
	short red_led = 17;
	short yel_led = 27;
	short grn_led = 22;
	short pin_btn = 2;
	int half_sec = 500000;
	
	// init pins
	pinMode(red_led, OUTPUT);
	pinMode(yel_led, OUTPUT);
	pinMode(grn_led, OUTPUT);

	// test leds
	digitalWrite(red_led, HIGH);
	usleep(half_sec);
	digitalWrite(red_led, LOW);
	digitalWrite(yel_led, HIGH);
	usleep(half_sec);
	digitalWrite(yel_led, LOW);
	digitalWrite(grn_led, HIGH);
	usleep(half_sec);
	digitalWrite(grn_led, LOW);
	usleep(half_sec);

	digitalWrite(red_led, HIGH);
	digitalWrite(yel_led, HIGH);
	digitalWrite(grn_led, HIGH);

	if(button(pin_btn, 1)) {
		printf("+++ Button was pressed! +++\n");
	}


}
