#ifndef BASIC_QUEUE_H
#define BASIC_QUEUE_H

#define QUEUE_LIMIT 25
#define NODE_LIMIT 25
#define MESSAGE_LIMIT 25
#define CHAR_LIMIT 256
#define DELETE_ERROR -1
#define SEND_ERROR -1
#define ENQUEUE_ERROR -1
#define DEQUEUE_ERROR -1
#define IDENTIFIER_ERROR -1
#define SUCCESS 0

#include <stdio.h>

/*
  Plan: The task specifies the MsgQs_t (which is the container of
  message queues which will from now on be called nodes) are stored on
  the heap. All that means is that the initializeMsgQs returns a
  pointer to a malloced MsgQs_t.

  Since this is the solution for just task 2a, a very basic
  implementation of a queue will be implemented (however, linked lists
  will be used in task 2b).
*/

/*
  Node represets a message queue. Each node needs to contain a null byte terminated char array (message) and an identifier (ID)
*/

typedef struct node {
	char *messages[MESSAGE_LIMIT];
    int ID;
	unsigned int index;
} node;

/*
  This struct will need to contain:
  1. Array of nodes.
  2. Index.
  3. Size.
  Size will be used to determine where the head of the queue is.
*/
typedef struct MsgQs_t {
	// This needs to be a pointer to nodes since we need to have the
	// ability to relinquish resources from specific nodes.
	node *nodes[NODE_LIMIT];
	unsigned int index;
} MsgQs_t;


/*
  Since the MsgQs_t has to be placed in heap, this function will
  malloc, give it default values and return a pointer to it.
*/
MsgQs_t* initializeMsgQs();

/*
  Simply free the MsgQs_t which is passed through the parameter. Of
  course in task 2a this will be a simple free. However, since linked
  lists are going to be used in task 2b, this process will have to be
  done recursively.

  @param *queue: Pointer to MsgQs_t variable which needs to be
  relinquished.
  *queue will also be set to null once the freeing process is done.
*/
void unloadMsgQs(MsgQs_t *queue);

/*
  Places a new node inside of a specified MsgQs_t variable. Its
  identifier will be given as an arguement.

  @param q: A variable of type MsgQs_t which is going to have a
  new node added to it.
  @param identifier: Identifier for node.
  @return: Returns a status code, 0 is successful, ENQUEUE_ERROR
  otherwise
*/
int createQ(MsgQs_t *q, int identifier);

/*
 Display all nodes by their identifier and their unsent messages.
*/
void listQs(MsgQs_t *queue);

/*
  When a queue is deleted, it will simply be overwritten by the
  following queues. If it's the last node, set it as null. If each
  node is also malloced and the individual queues are freed, that
  means that the max number of queues will decrease each time.

  @return: Returns DELETE_ERROR if the queue identifier doesn't exist.
*/
int deleteQ(MsgQs_t *queue, int indentifier);

/*
  Sends a message (enqueues a node) to all nodes or a specific node if
  an identifier is specified.

@param queue: MsgQs_t in which this function will operate.

@param identifier: If this is NULL, then the message is sent to all of
the queues (sendMessageBatch is sent). Otherwise it is directed to the
specified message queue

@param message: Message which will be sent.

@return: Return SEND_ERROR if identifier doesn't exist
*/
int sendMessage(MsgQs_t *queue, void *identifier, char* message);

/*
  Sends a message to all of the nodes in MsgQs_t
  @param queue: queue which will be operated on.
  @param message: Message which will be sent.
*/
void sendMessageBatch(MsgQs_t *queue, char message[MESSAGE_LIMIT]);

/*
  Clears a node from all of its messages, just loop through all of the
  messages and place a \0 at the very beginning.
  @param queue: MsgQs_t on which this function will operate.
  @param indetifier: Identifier of node to clear.
*/
int purgeQs(MsgQs_t *queue, void* indentifier);

/*
  Experiment with serialization and come back here once you figured it
  out
*/
int persistQ(MsgQs_t *q, int identifier);
int restoreQ(MsgQs_t *q, int identifier);

#endif
