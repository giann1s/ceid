#include <stdio.h>
#include "robot.h"

void fwd(SOCKET socket, int steps);

int main() {
	int i;
	
	SOCKET socketfd = connect2Labyrinth("127.0.0.1", 12345);
	loadLabyrinth(socketfd , "labyrinth5.lab");
	insertRobot(socketfd, "Cleo");
    robotSetMode(socketfd, MODE_MANUAL);

	fwd(socketfd, 2);
	robotTurnRight(socketfd);
	robotStep(socketfd, 8);
	robotTurnLeft(socketfd);
	fwd(socketfd, 2);
	robotTurnRight(socketfd);
	fwd(socketfd, 2);
	robotTurnRight(socketfd);
	fwd(socketfd, 2);
	robotTurnRight(socketfd);

	for (i=0; i<2; i++) {
    	fwd(socketfd, 1);
		robotTurnLeft(socketfd);
	}
	
	fwd(socketfd, 1);
	robotTurnRight(socketfd);

	for (i=0; i<2; i++) {
    	fwd(socketfd, 1);
		robotTurnLeft(socketfd);
	}

	fwd(socketfd, 4);

	return 0;
}

void fwd(SOCKET socket, int steps) {
	int i;
	for (i=0; i<steps; i++) {
    	robotStep(socket, 8);
	}
}
