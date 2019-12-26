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
void batch_populate_node(nodeMsg_t* front, char* sender, char* subject, char* content);
int removeQ(nodeMsg_t *front, int identifier);
int enqueue_nodeMsg_t(nodeMsg_t* q, char* sender, char* subject, char* content);
int populate_individual_node(nodeMsg_t *front, int ID, char *sender,
                             char *subject, char *content);
int empty_q(nodeMsg_t *front, int identifer);
void empty_all_qs(nodeMsg_t *front);
void free_individual_item(Item *Item);
size_t update_node_bytes(Item *front);
void skip_list(FILE *file);
long int decode_expiry(FILE *file);
char* decode_string(FILE *file);
#endif
