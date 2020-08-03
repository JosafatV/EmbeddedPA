#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

const char* read_path = "/home/josav09/Desktop/pass_message/led_status.txt";
const char* write_path = "/home/josav09/Desktop/pass_message/btn_status.txt";

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


int main () {
	char* read;
	int data = 0;
	while (1) {
		read_file(read);
		//printf("Read: %s \n", read);
		if (data) {
			write_file("1");
			data = 0;
		} else {
			write_file("0");
			data = 1;
		}
		
		usleep(5000000);
	}
   
   return 0;
}



