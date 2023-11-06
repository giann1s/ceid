#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "robot.h"

bool isIP(char ip[]);
bool isPort(int port);

int main() {
	char ip[16];
	int port;

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
	insertRobot(socketfd, "Cleo");
    robotSetMode(socketfd, MODE_AUTO);

	while ( ! robotExitFound(socketfd)) {
		1==1;	// Wait
	}

	return 0;
}

bool isIP(char ip[]) {
	bool isIP = true;
	int i = 0, str_end = 0, dot_cnt = 0, dots_idx[] = {-1, 0, 0, 0, 0};

	// dots_idx: first and last elements are used for checking the numbers validity
	// The other three are the actual dots' indexes

	str_end = strlen(ip) + 1;
	dots_idx[4] = str_end;

	if (ip[0] == '.' || ip[str_end - 1] == '.') {
		isIP = false;	// Starts or end with dot
	}

	for (i=0; i<str_end && isIP == true; i++) {		
		if ( ! (ip[i] >= '0' && ip[i] <= '9' || ip[i] == '.')) {
			isIP = false;	// Invalid character
		}

		// Find the number of dots and their positions and check if there is more than 1 dots in a row
		if (ip[i] == '.') {
			dot_cnt++;
			if (dot_cnt < 3) {
				dots_idx[dot_cnt] = i;
			}
			else
				isIP = false;
			
			if (ip[i+1] == '.')
				isIP = false;
		}

		// Check if the numbers are within the range
		if (isIP == true) {
			strncpy();

			for (i = 0; i<4 && isIP == true; i++) {
				if (dots_idx[i+1] - dots_idx[i] > 4) {
					isIP = true;
				}
				else if () {

				}
			}
		}
	}

	return isIP;
}

bool isPort(int port) {
	if (port > 0 && port < 65536) {
		return true;
	}
}
