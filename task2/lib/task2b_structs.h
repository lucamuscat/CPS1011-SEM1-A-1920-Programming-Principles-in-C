#ifndef STRUCTS_H
#define STRUCTS_H
#
/*
  This struct was created in order to remove the circular dependency
  caused by linked_list.h including task2_utils and vice versa.
*/
#include <stdio.h>
#include <time.h>

struct Message {
	char* subject;
	char* content;
	size_t bytes;
};
typedef struct Message Message;

/*
  As you may have noticed, an extra member called bytes has been added.
  This is going to help with figuring out the payload.
*/

struct Item {
	char* sender;
	Message* message;
	time_t expiry;
	struct Item* next;
	size_t bytes;
};
typedef struct Item Item;

struct nodeMsg_t {
	Item* front;
	Item* rear;
	int ID;
	size_t size;
	struct nodeMsg_t *next;
	size_t bytes;
};
typedef struct nodeMsg_t nodeMsg_t;

typedef struct MsgQs_t {
	size_t size;
	nodeMsg_t *front;
	nodeMsg_t *rear;
	size_t bytes;
} MsgQs_t;


#endif
