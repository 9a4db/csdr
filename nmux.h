#include <stdio.h>
#include <socket.h>

#define MSG_START "nmux: "

typedef enum client_status_e
{
	CS_CREATED,
	CS_THREAD_RUNNING,
	CS_THREAD_FINISHED
} client_status_t;


typedef struct client_s
{
	struct sockaddr_in addr;
	int socket;
	int error; //set to non-zero on error (data transfer failed)
	pthread_t thread;
    tsmthread_t tsmthread;
	client_status_t status;
    //the following members are there to give access to some global variables inside the thread:
    tsmpool* lpool; //local pool
    int sleeping;
    pthread_cond_t* wait_condition;
    pthread_mutex_t wait_mutex;
} client_t;
