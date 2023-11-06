#include <stdio.h>
#include "robot.h"

#define LEFT 0
#define RIGHT 1

typedef int DIRECTION;

int follow_wall(SOCKET socket, DIRECTION direction);

int main() {

	SOCKET socketfd = connect2Labyrinth("127.0.0.1", 12345);
	loadLabyrinth(socketfd , "labyrinth6.lab");
	insertRobot(socketfd, "Cleo");
    robotSetMode(socketfd, MODE_MANUAL);
    
    while (robotExitFound(socketfd) == RSP_EXITFOUND) {
    	follow_wall(socketfd, RIGHT);
	}

	return 0;
}

int follow_wall(SOCKET socket, DIRECTION direction) {

	if (direction == LEFT) {
		while () {
			robotTurnRight(SOCKET sock);
		}
		
	}
	else if (direction == RIGHT) {
		while () {
			robotTurnLeft(SOCKET sock);
		}	
	}
}

