#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define OFF 0
#define ON 1
int main(int argc, char** argv){
	//open device file control buton and led
	int button_fd = open("/dev/buttons", O_RDONLY);
	if(button_fd < 0){
		printf("Error: cant open button device file\n");
		exit();
	}	
	int led_fd = open("/dev/leds", O_WRONLY);
	if(led_fd < 0){
		printf("Error: cannot open led device file\n");
		exit();
	}

	char led_status[] = {0, 0, 0, 0};
	char button_status[] = {0, 0, 0, 0, 0, 0};
	while(1){
		//read button status from file device
		int readcount = read(button_fd, button_status, sizeof(button_status));
		if(readcount != sizeof(button_status)){
			printf("Error read button status\n");
		}
		for(current_button = 0; current_button < 4; current_button++){
			if(buttton_status[current_button] != led_status[current_button]){
				led_status[current_button] = button_status[current_button];
				ioctl(led_fd, button_status[current_button]%2, current_button);
			}
		}
		if(button_status[4] == ON){
			//light all up
			for(int i = 0; i < 4; i++){
				ioctl(led_fd, ON, i);
			}
		}
		if(button_status[5] == ON){
			//light all off
			for(int i = 0; i < 4; i+)
		}
	}
}

int led_toggle(void){
	//turn off all led
	for(int i = 0; i < 4; i++){
		ioctl(led_fd, OFF, i);
	}
	sleep(1);
	//turn on all led
	for(int i = 0; i < 4; i++){
		ioctl(led_fd, ON, i);
	}
	sleep(1);
}

int interleave_toggle(void){
	int interleave_matrix[] = {ON, OFF, ON, OFF};
	for(int i = 0; i < 4; i++){
		ioctl(led_fd, interleave_matrix[i], i);
	}
	sleep(1);

	for(int i = 0; i < 4; i++){
		ioctl(led_fd, ~interleave_matrix[i], i);
	}
	sleep(1);
}

int chasing_led(void){
	for(int led_no = 0; led_no < 4; led_no++){
		//turn off all led
		for(int i = 0; i < 4; i++){
			ioctl(led_fd, OFF, i);
		}
		//turn on led number led_no
		ioctl(led_fd, ON, led_no);
		sleep(1);
	}
}
