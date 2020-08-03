#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <libraspio.h>

const char* read_path = "./led_status.txt";
const char* write_path = "./btn_status.txt";
int half_sec = 500000;

// GPIO pin definitions
short red_led = 17;
short yel_led = 27;
short grn_led = 22;

/** Launches the python3 pyrebase server*/
void* start_pyrebase_server() {
	system("python3 ./pyrebase_server.py");
}

/** Launches the python3 audio recording and speech recognition service*/
void* start_audio_service() {
	system("python3 ./audio_service.py");
}

void gpio_control () {
	FILE *fp;
	char str[16];
	char* value;
	while (1) {
		fp = fopen(read_path, "r"); // read mode

		if (fp == NULL) {
			perror("Error while opening the r_file.\n");
			exit(EXIT_FAILURE);
		}

		fgets(str, 16, fp);
		printf("%d:%d:%d\n", str[0]-48,str[2]-48,str[4]-48);
		//digitalWrite(red_led, str[0]-48);
		//digitalWrite(yel_led, str[2]-48);
		//digitalWrite(grn_led, str[3]-48);
		fclose(fp);
		usleep(half_sec);
	}
    
}

int main() {
	
	/* init pins
	pinMode(red_led, OUTPUT);
	pinMode(yel_led, OUTPUT);
	pinMode(grn_led, OUTPUT);
	pinMode(pin_btn, INPUT);
	*/
	// Manage python as threads
	pthread_t server, service;
	int ret;

	ret = pthread_create(&server, NULL, start_pyrebase_server, NULL);
	if(ret!=0) {printf("+++ Error creating server thread +++\n");}

	ret = pthread_create(&service, NULL, start_audio_service, NULL);
    if(ret!=0) {printf("+++ Error creating service thread +++\n");}

	// Control GPIO
	gpio_control();

	pthread_join(server, NULL);
    pthread_join(service, NULL);

   return 0;
}
