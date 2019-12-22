#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
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
