/*
Things left to do:
- Update the client function to "void *client(void *arg)"
- Make the main
- Testing and debugging
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 5
#define QUEUE_CAPACITY 10
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

// queues
int vip_queue[QUEUE_CAPACITY];
int vip_queue_clients = 0;
int vip_queue_first = 0;
int vip_queue_last = -1;

int normal_queue[QUEUE_CAPACITY];
int normal_queue_clients = 0;
int normal_queue_first = 0;
int normal_queue_last = -1;


// critical region
int current_clients = 0;


// synchronization
pthread_mutex_t m;
pthread_cond_t vip_cond;
pthread_cond_t normal_cond;


// tClient
typedef struct {
	int id;
	int isvip;
} tClient;


void *client(tClient *c) {
	pthread_mutex_lock(&m);

	if(c->isvip) {
		enter_vip_client(c->id);
	}
	else {
		enter_normal_client(c->id);
	}
	dance(c->id, c->isvip);
	exit_client();
}

void enter_normal_client(int id)
{
	// entering the queue (we assume there is room)
	if(normal_queue_last == QUEUE_CAPACITY) {
		normal_queue_last = 0;
	}
	else {
		normal_queue_last++;
	}
	normal_queue[vip_queue_last] = id;

	// waiting in line
	while(current_clients >= CAPACITY || normal_queue_first != id) {
		pthread_cond_wait(&normal_cond, &m); // atomically releases the mutex
	}

	// exiting the queue
	if(normal_queue_first == QUEUE_CAPACITY) {
		normal_queue_first = 0;
	}
	else {
		normal_queue_first++;
	}

	// going into the club
	printf("Normal Client %2d entering the club, id\n");
}

void enter_vip_client(int id)
{
	// entering the queue (we assume there is room)
	if(vip_queue_last == QUEUE_CAPACITY) {
		vip_queue_last = 0;
	}
	else {
		vip_queue_last++;
	}
	vip_queue[vip_queue_last] = id;

	// waiting in line
	while(current_clients >= CAPACITY || vip_queue_first != id) {
		pthread_cond_wait(&vip_cond, &m); // atomically releases the mutex
	}

	// exiting the queue
	if(vip_queue_first == QUEUE_CAPACITY) {
		vip_queue_first = 0;
	}
	else {
		vip_queue_first++;
	}

	// going into the club
	printf("VIP Client %2d entering the club\n, id");
}

void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in the club\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip)
{
	pthread_mutex_lock(&m);
	if(vip_queue_clients > 0) {
		pthread_cond_broadcast(&vip_cond);
	}
	else {
		pthread_cond_broadcast(&normal_cond);
	}

	printf("Client %2d (%s) is leaving\n", id, VIPSTR(isvip));
}

int main(int argc, char *argv[])
{


	return 0;
}
