#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl>
#include <unistd.h>
#include <string.h>


#define OFF 0
#define ON 1

int function_running, led_fd;
char* USAGE = "led_control control_function time_delay";
int main(int argc, char** argv){
	if(argc != 3)
		printf("%s", USAGE);
	
	function_running = atoi(argv[1]);
	if(function_running < 1 || function_running > 3)
		printf("%s", USAGE);
	
	time_delay = atoi(argv[2]);
	//open file device
	led_fd = open("/dev/leds", 0_RDWR);
	if(led_fd < 0)
		printf("Error: fail to open file device");
	while(1){
		switch(function_running){
			case 1:
				chasing_led();
				break;
			case 2:
				toggle_led();
				break;
			case 3:
				interleave_toggle();
				break;
			default:
				exit();
		}	
	}
}

void chasing_led(void){
	int led_no, tmp;
	for(led_no = 0; led_no < 4; led_no++){
		//turn off all leds
		for(tmp = 0; tmp < 4; tmp++)
			ioctl(led_fd, OFF, tmp);
		//turn on led_no
		ioctl(led_fd, ON, led_no);
		ms_delay(time_delay);
	}
}

void toggle_led(void){
	//turn off all leds
	int tmp;
	for(tmp = 0; tmp < 4; tmp++)
		ioctl(led_fd, OFF, tmp);
	ms_delay(time_delay);

	//turn on all leds
	for(tmp = 0; tmp < 4; tmp++)
		ioctl(led_fd, ON, tmp);
	ms_delay(time_delay);
}

char interleave_map[] = {1, 0, 1, 0};
void interleave_toggle(void){
	int tmp;
	for(tmp = 0; tmp < 4; tmp++)
		ioctl(led_fd, interleave_map[tmp], tmp);
	ms_delay(time_delay);
	for(tmp = 0; tmp < 4; tmp++)
		interleave_map[tmp] = ~interleave_map[tmp];
}
