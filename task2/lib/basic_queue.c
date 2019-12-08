/*
  First implement a simple queue.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "basic_queue.h"

MsgQs_t *initializeMsgQs() {
	// Initialize all of the nodes.
	MsgQs_t *q = (MsgQs_t*) malloc(sizeof(MsgQs_t));
	// Initialize the queue
	q -> index = 0;
	return q;
}

int createQ(MsgQs_t *q, int identifier) {
	if(q -> index < QUEUE_LIMIT){
		q->nodes[q->index] = malloc(sizeof(node));
		q->nodes[q->index]->index=0;
		q->nodes[q->index]->ID=identifier;
		q->index++;
		return SUCCESS;
	}
	return ENQUEUE_ERROR;
}

void unloadMsgQs(MsgQs_t *q) {
	// free nodes and msgqs_t
	for(size_t i = 0; i < q->index; ++i){
		for (size_t j = 0; j < q->nodes[i]->index; ++j) {
			free(q->nodes[i]->messages[j]);
		}
		free(q->nodes[i]);
	}
	free(q);
}

void listQs(MsgQs_t *q) {
	for (size_t i = 0; i < q->index; ++i){
		printf("=========\nIdentifier: %d\n", q->nodes[i]->ID);
		if(q->nodes[i]->index == 0){
			puts("This Message Queue is Empty :(");
			continue;
		}
		for(size_t j = 0; j < q->nodes[i]->index; ++j){
			printf("%d: %s\n", j, q->nodes[i]->messages[j]);
		}
	}
}

int deleteQ(MsgQs_t *q, int identifier) {
	for(size_t i = 0; i < q->index; ++i){
		if(q->nodes[i]->ID == identifier){
			free(q->nodes[i]);
			// Final node in queue
			if(i==q->index){
				q->index--;
			}else{
				// Not final node in queue
				// Shift following nodes back by 1.
				for(size_t j = i; j < q->index-1; ++j){
					q->nodes[i] = q->nodes[i+1];
				}
				// free the last node since this was already shifted
				// one back
				free(q->nodes[q->index]);
				q->index--;
			}
			return 0;
		}
	}
	return DEQUEUE_ERROR;
}

int sendIndividualMessage(node *node, char *message) {
	if(node->index < MESSAGE_LIMIT){
          /*
			strcpy is used instead of assigning the message arguement
			message[node->index] since side effects might occur on the
			value referenced by the message pointer arguement.
			This will cause unexpected bugs when a reference to a
			mutable char array is passed into the message
			arguement. Once the mutable char array is modified outside
			of the function's scope, the value saved in the node will
			also change.
		  */
		node->messages[node->index] = malloc(sizeof(char) * CHAR_LIMIT);
		strcpy(node->messages[node->index], message);
		node->index++;
		return SUCCESS;
	}
	return SEND_ERROR;
}

void sendMessageBatch(MsgQs_t *q, char *message) {
	for (size_t i = 0; i < q->index; ++i){
		sendIndividualMessage(q->nodes[i], message);
	}
}

int sendMessage(MsgQs_t *q, void *identifier, char *message) {
	if(identifier == NULL)
		sendMessageBatch(q, message);
	for(size_t i = 0; i < q->index; ++i){
		if((int) identifier == q->nodes[i]->ID){
			sendIndividualMessage(q->nodes[i], message);
			return SUCCESS;
		}
	}
	return IDENTIFIER_ERROR;
}

void purgeIndividualNode(node *node) {
	for (size_t i = 0; i < node->index; ++i) {
		free(node->messages[i]);
	}
	node->index = 0;
}

void purgeAllNodes(MsgQs_t *q) {
	for (size_t i=0; i < q->index; ++i) {
		purgeIndividualNode(q->nodes[i]);
	}
}

int purgeQs(MsgQs_t *q, void* identifier) {
	//purge all
	if(identifier == NULL)
		purgeAllNodes(q);
	int int_id = (int)identifier;
	for (size_t i = 0; i < q->index; ++i){
		if(int_id == q->nodes[i]->ID){
			purgeIndividualNode(q->nodes[i]);
			return SUCCESS;
		}
	}
	return IDENTIFIER_ERROR;
}

int persistQ(MsgQs_t *q, int identifier){
	node *node;
	for(size_t i = 0; i < q->index; ++i){
		if(q->nodes[i]->ID == identifier)
			node = q->nodes[i];
	}
	if(node == NULL)
		return -1;

	FILE *file;
	char filename[26];
	sprintf(filename, "%d.dat", identifier);
	if((file = fopen(filename, "w")) == NULL){
		printf("ERROR OPENING %s", filename);
	}
	for (size_t i = 0; i < node->index; ++i) {
		fputs(strcat(node->messages[i],"\n"), file);
	}
	fclose(file);
	return SUCCESS;
}
