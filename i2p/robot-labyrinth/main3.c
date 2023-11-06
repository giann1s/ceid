#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "robot.h"

bool isIP(char ip[]);
bool isPort(int port);

int main() {
	char ip[16];
	int port, success;

	printf("Type the IP address: ");
	scanf("%s", ip);
	printf("Type the port number: ");
	scanf("%d", &port);
	
	if ( ! ( isIP(ip) == true && isPort(port) == true ) ) {
		printf("Invalid IP or port number!");
		return 0;
	}

	SOCKET socketfd = connect2Labyrinth(ip, port);
	loadLabyrinth(socketfd , "labyrinth6.lab");
	success = 0 == insertRobot(socketfd, "Cleo");

	if (success) {
		printf("Connection successful!\n");
	}
	else {
		printf("Unable to connect!\n");
	}

    robotSetMode(socketfd, MODE_AUTO);

	while ( ! robotExitFound(socketfd)) {
		1==1;	// Wait
	}

	return 0;
}

bool isIP(char ip[]) {
	bool isIP = true;
	int i = 0, str_end = 0, dot_cnt = 0, last_num_start = 0;

	str_end = strlen(ip) + 1;

	if (ip[0] == '.' || ip[str_end - 1] == '.') {
		isIP = false;
	}

	for (i=0; i<str_end && isIP == true; i++) {		
		if (! (ip[i] >= '0' && ip[i] <= '9') && ip[i] != '.') {
			isIP = false;	// Invalid character
		}

		if (ip[i] == '.') {
			dot_cnt++;
			last_num_start = i + 1;

			if (ip[i+1] == '.') {
				isIP = false;	// More than 1 dots in a row
			}
		}
		else {
			if (i - last_num_start > 2) {
				isIP = false;	// More than 3 digits
			}
		}
	}

	if (dot_cnt != 3) {
		isIP = false;
	}

	return isIP;
}

bool isPort(int port) {
	if (port > 0 && port < 65536) {
		return true;
	}
}
