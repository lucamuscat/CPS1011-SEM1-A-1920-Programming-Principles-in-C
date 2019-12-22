#ifndef TASK2B_H
#define TASK2B_H
#include "linked_list.h"

_Bool contains_id(nodeMsg_t* front, int identifier);
int is_empty(MsgQs_t *queue);
void free_item(Item *Item);
void free_node(nodeMsg_t *node);
void printItem(Item *Item);
void listItems(Item *Item);
int removeQ(nodeMsg_t *front, int identifier);


#endif
