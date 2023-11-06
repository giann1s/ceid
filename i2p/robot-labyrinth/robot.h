#include <winsock2.h>
#include <stdbool.h>

#define REQ_ERROR -2
#define REQ_UNKNOWN -1

#define REQ_STOP 1
#define REQ_MOVE 2
#define REQ_STEP 3
#define REQ_TURNLEFT 4
#define REQ_TURNRIGHT 5
#define REQ_RESET 6
#define REQ_QUIT 7
#define REQ_SENSE 8
#define REQ_STATE 9
#define REQ_ROBOTINIT 10
#define REQ_ROBOTDESTROY 11
#define REQ_SETMODE 12
#define REQ_GOHOME 13
#define REQ_LOADLABYRINTH 14
#define REQ_EXITFOUND 15

#define RSP_ERROR -1
#define RSP_OK 1
#define RSP_SENSE 2
#define RSP_STATE 3
#define RSP_EXITFOUND 4

#define ROBOT_NAME_LENGHT 16

#define STATE_STOPED 1
#define STATE_MOVING 2
#define STATE_STEPING 3

#define MODE_MANUAL 0
#define MODE_AUTO 1
#define MODE_DEFAULT MODE_MANUAL

#define NO_WALL 1000

struct sensor {
	_Bool wall;
	int distance;
};

struct sensors {
	struct sensor front;
	struct sensor left;
	struct sensor right;
};

SOCKET connect2Labyrinth(const char *ip, int port);
int insertRobot(SOCKET socket,char *name);
int robotSetMode(SOCKET socket,char mode);
int robotGoAhead(SOCKET socket);
int robotTurnLeft(SOCKET socket);
int robotTurnRight(SOCKET socket);
int robotGetState(SOCKET socket);
int robotGetSensors(SOCKET socket,struct sensors *sens);
int robotStep(SOCKET sock, int n);
int robotGoHome(SOCKET sock);
int robotStop(SOCKET sock);
int destroyRobot(SOCKET sock) ;
int loadLabyrinth(SOCKET sock,char *fname);
