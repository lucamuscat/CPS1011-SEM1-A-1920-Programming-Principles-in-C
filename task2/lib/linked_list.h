#ifndef TASK2B_H
#define TASK2B_H
// include for size_t type.
#include <stdlib.h>


struct Message {
	char* subject;
	char* content;
};
typedef struct Message Message;

struct Item {
	char* sender;
	Message* message;
	long long unsigned int expiry;
	struct Item* next;
};
typedef struct Item Item;

struct nodeMsg_t {
	Item* front;
	Item* rear;
	int ID;
	struct nodeMsg_t *next;
};
typedef struct nodeMsg_t nodeMsg_t;

typedef struct MsgQs_t {
	size_t size;
	nodeMsg_t *front;
	nodeMsg_t *rear;
} MsgQs_t;

MsgQs_t* initializeMsgQs();
int createQ(MsgQs_t *q, int identifer);
void unloadMsgQs(MsgQs_t *q);
void listQs(nodeMsg_t *front);
int deleteQ(MsgQs_t *q, int identifier);

#endif
