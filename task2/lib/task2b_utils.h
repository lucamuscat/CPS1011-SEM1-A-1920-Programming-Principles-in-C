#ifndef TASK2B_UTILS_H
#define TASK2B_UTILS_H
#include <stdbool.h>
#include "task2b_structs.h"
_Bool contains_id(nodeMsg_t* front, int identifier);
int is_empty(MsgQs_t *queue);
void free_item(Item *Item);
void free_node(nodeMsg_t *node);
void printItem(Item *Item);
void listItems(Item *Item);
int removeQ(nodeMsg_t *front, int identifier);


#endif
