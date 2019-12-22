#ifndef STRUCTS_H
#define STRUCTS_H

/*
  This struct was created in order to remove the circular dependency
  caused by linked_list.h including task2_utils and vice versa.
*/
#include <stdio.h>

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
	size_t size;
	struct nodeMsg_t *next;
};
typedef struct nodeMsg_t nodeMsg_t;

typedef struct MsgQs_t {
	size_t size;
	nodeMsg_t *front;
	nodeMsg_t *rear;
} MsgQs_t;


#endif
