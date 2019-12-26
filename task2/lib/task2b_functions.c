#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "task2b_functions.h"
#include "task2b_utils.h"
#include "rlp.h"

#define FULL_QUEUE_ERROR -1
#define EMPTY_ERROR -2

#define MESSAGE_LENGTH 256
#define LIMIT 25

MsgQs_t* initializeMsgQs() {
	MsgQs_t *q = (MsgQs_t*) malloc(sizeof(MsgQs_t));
	q -> size = 0;
	q -> front = NULL;
	q -> rear = NULL;
	return q;
}

// Enqueue a MsgQs_t variable.
int createQ(MsgQs_t *q, int identifier) {
	if(contains_id(q->front, identifier))
		return -1;
	nodeMsg_t *tmp;
	tmp = malloc(sizeof(nodeMsg_t));
	tmp->next = NULL;
	tmp->ID = identifier;
	tmp->size = 0;
	if(is_empty(q)){
		q -> front = tmp;
		q -> rear = tmp;
	} else{
		q -> rear -> next = tmp;
		q -> rear = tmp;
	}
	q->size++;
	return 1;
}

void unloadMsgQs(MsgQs_t *q) {
	nodeMsg_t* node = q->front;
	free_node(node);
	q->size = 0;
}

void listQs(nodeMsg_t *front) {

	if(front->size == 0){
		puts("This is empty :/");
	} else {
		printf("\nID: %d", front->ID);
		listItems(front->front);
	}
	if(front->next != NULL){
		return listQs(front->next);
	}
	return;
}

int deleteQ(MsgQs_t* q, int identifier){
	if(q->front->ID == identifier){
		nodeMsg_t* temp = q->front;
		free_item(temp->front);
		q->front = temp->next;
		return 1;
	}
	return removeQ(q->front, identifier);
}

// returns an error if queue id doesn't exist
void sendMessageBatch(MsgQs_t *q, char* sender, char* subject, char* content) {
	batch_populate_node(q->front, sender, subject, content);
}

int sendMessage(MsgQs_t *q, void *ID, char *sender, char *subject,
                 char *content) {
	if (ID == NULL){
		sendMessageBatch(q, sender, subject, content);
		return 1;
	}
	return populate_individual_node(q->front,(int) ID, sender, subject, content);
}

int purgeQs(MsgQs_t *q, void* identifier) {
	if(identifier == NULL){
		empty_all_qs(q->front);
		return 1;
	}

	if(q->front->ID == (int)identifier){
		nodeMsg_t* temp = q->front;
		free_item(temp->front);
		q->front = temp->next;
		return 1;
	}
	return empty_q(q->front,(int)identifier);
}

int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages) {
	nodeMsg_t* front = q->front;
	for (size_t i = 0; i < q->size; ++i) {
		if (front->ID == identifier) {
			num_of_messages = num_of_messages > front->size ? front->size : num_of_messages;
			Item* front_item;
			for (size_t j = 0; j < num_of_messages; ++j) {
				// Link the front to the next item.
				front_item = front->front;
				printItem(front_item);
				free_individual_item(front_item);
				front->front = front_item->next;
				front->size--;
			}
			return 1;
		}else {
			front = front->next;
		}
	}
	return -1;

}

int persistQ(MsgQs_t* MsgQ, int identifier) {
	/*
	  The strings are already RLP encoded. The only thing that needs to
	  be taken care of is the encoding of the expiry.

	  Create a function which takes care of the list representation
	  of nodeMsg_t (just get the payload size ie. go through the
	  Item queue and get their sizes); Every time a function
	  finishes, its result is directly written into the file. Once
	  the list representation has been written, the sender and
	  expiry are written, followed by the list representation of the
	  message and its dumped text.

	  This whole algorithm will be encapsulated into a function
	*/

	// Go through all the nodes
	/*
	  This is necessary as opposed to taking the size of the stored
	  chars since the stored chars are already encoded.
	*/

	nodeMsg_t* q;
	nodeMsg_t* tmp = MsgQ->front;
	// Find the node with the matching ID
	if(contains_id(MsgQ->front, identifier)){
		for (size_t i = 0; i < MsgQ->size; ++i) {
			if(tmp->ID == identifier){
				q = tmp;
			}else{
				tmp = tmp->next;
			}
		}
	}else{
		return -1;
	}

	q->bytes = update_node_bytes(q->front);
	//https://stackoverflow.com/questions/14564813/how-to-convert-integer-to-character-array-using-c
	// 10 max decimal digits with 32 bits (4 byte int)
	// 4 extra to hold ".dat"
	// 1 extra for the null byte.
	FILE* file;
	char file_name[15];
	sprintf(file_name, "%d.dat", q->ID);
	if((file = fopen(file_name, "w")) == NULL){
		printf("ERROR OPENING %s", file_name);
		fclose(file);
		return -1;
	}
	char* list_encoding = rlp_encode_list(q->bytes);
	fwrite(rlp_encode_list(q->bytes), sizeof(char), strlen(list_encoding), file);
	Item* front = q->front;
	for (size_t i = 0; i < q->size; ++i) {
		char* item_encoding = rlp_encode_list(front->bytes);
		fwrite(item_encoding, sizeof(char), strlen(item_encoding), file);
		fwrite(front->sender, sizeof(char), strlen(front->sender), file);
		char* expiry_encoding = str_encode_length(byte_len(front->expiry));
		fwrite(expiry_encoding, sizeof(char), strlen(expiry_encoding), file);
		fwrite(&front->expiry, sizeof(long int), 1, file);
		char* message_encoding = rlp_encode_list(front->message->bytes);
		fwrite(message_encoding , sizeof(char), strlen(message_encoding), file);
		char* subject = front->message->subject;
		char* content = front->message->content;
		fwrite(subject, sizeof(char), strlen(subject), file);
		fwrite(content, sizeof(char), strlen(content), file);
		front = front->next;
	}
	fclose(file);
	return 1;
}

// Precondition: MsgQs_t is created from before hand.
int restoreQ(MsgQs_t *q, int identifier) {
	FILE* file;
	char file_name[15];
	sprintf(file_name, "%d.dat", identifier);
	if((file = fopen(file_name, "r")) == NULL){
		printf("ERROR OPENING %s", file_name);
		fclose(file);
		return -1;
	}
	skip_list(file);
	char* sender;
	long int expiry;
	char* subject;
	char* content;
	while(!feof(file)){
		skip_list(file);
		if(!feof(file)){
			sender = decode_string(file);
			expiry = decode_expiry(file);
			skip_list(file);
			subject = decode_string(file);
			content = decode_string(file);
			sendMessage(q, (void*)identifier, sender, subject, content);
		}
	}
}
