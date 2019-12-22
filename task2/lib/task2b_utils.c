#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "task2b_functions.h"
// The recursed data can be saved into a hashmap
// but that will make my current solution more complex.
_Bool contains_id(nodeMsg_t* front, int identifier) {
	if(front->next != NULL)
		return contains_id(front -> next, identifier);
	return front->ID == identifier;
}

// Returns EMPTY_ERROR when empty and 1 when not empty.
int is_empty(MsgQs_t *queue) {
	return queue->size == 0;
}

void free_item(Item *Item) {
	if(Item->next != NULL)
		free_item(Item->next);
	free(Item->message->content);
	free(Item->message->subject);
	free(Item->message);
	free(Item->sender);
	free(Item);
	return;
}
// Free everything using tail-recursion.
void free_node(nodeMsg_t *node) {
	if(node->next != NULL)
		free_node(node->next);
	free_item(node->front);
	free(node);
	return;
}

void printItem(Item *Item) {
	printf("Sender: %s\n", Item->sender);
	printf("Subject: %s\n", Item->message->subject);
	printf("%s\n", Item->message->content);
	printf("Expiry: %llu\n", Item->expiry);
}

void listItems(Item *Item) {
	if(Item->next != NULL){
		printItem(Item);
		listItems(Item->next);
	}
	printItem(Item);
	return;
}


int removeQ(nodeMsg_t *front, int identifier) {
  /*
	Are we on the rear node? If so return an error since the ID
	doesn't exist.
  */
	if(front->next == NULL)
		return -1;

	if(front->next->ID == identifier){
		nodeMsg_t* next = front->next;
		// Free all the Qs items
		free_item(next->front);
		// Replace the next node with the next node's next node.
		front->next = next->next;
		// free the memory allocated to the item pointers.
		free(next);
		return 1;
	}

	/*
	  If the next node isn't null or an identifier, go to the next
	  node to repeat the process. This way, the result will bubble
	  back up the stack.
	*/

	return removeQ(front->next, identifier);
}

// https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
// Don't forget to strcpy everything. To avoid bugs due to references.
Item* create_item(char *sender, char *subject, char *content) {
	Item* temp = malloc(sizeof(Item));
	temp->sender = malloc(sizeof(char) * strlen(sender));
	temp->message = malloc(sizeof(Message));
	temp->message->subject = malloc(sizeof(char)*strlen(subject));
	temp->message->content = malloc(sizeof(char)*strlen(subject));

	strcpy(temp->sender, sender);
	strcpy(temp->message->subject, subject);
	strcpy(temp->message->content, content);

	temp->next = NULL;

	return temp;
}

int enqueue_nodeMsg_t(nodeMsg_t* q, char* sender, char* subject, char* content) {
	Item *tmp;
    tmp = create_item(sender, subject, content);
	// is the node not empty?
    if(q->size!=0) {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else {
        q->front = q->rear = tmp;
    }
	q->size++;
}
