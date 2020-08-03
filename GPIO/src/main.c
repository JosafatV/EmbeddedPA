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
short pin_btn = 2;

void read_file (char* data) {
	FILE *fp;
	char str[128];
	char* value;
	
	fp = fopen(read_path, "r"); // read mode

	if (fp == NULL) {
		perror("Error while opening the r_file.\n");
		exit(EXIT_FAILURE);
	}

	fgets(str, 128, fp);
	puts(str);
	//printf("%s\n", str);
	fclose(fp);
    data = &str[0];
}

void write_file (char* data) {
	FILE *fp;
	char* newline = "\n";
	fp = fopen(write_path, "w"); // overwrite mode

	if (fp == NULL) {
	  perror("Error while opening the w_file.\n");
	  exit(EXIT_FAILURE);
	}

	fprintf(fp, "%s", data);

	fclose(fp);
}

/** Launches the python3 pyrebase server*/
void* start_pyrebase_server() {
	system("python3 ./pyrebase_server.py");
}

/** Launches the python3 audio recording and speech recognition service*/
void* start_audio_service() {
	system("python3 ./audio_service.py");
}

/** Dummy GPIO control function */
void gpio_control () {
	char* read;
	int data = 0; // swap to GPIO read
	while (1) {
		read_file(read);
		if (data) {
			write_file("1"); //digitalRead(button)
			data = 0;
		} else {
			write_file("0");
			data = 1;
		}
		
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
