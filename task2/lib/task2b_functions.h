#ifndef TASK2B_H
#define TASK2B_H
// include for size_t type.
#include <stdlib.h>
#include "task2b_structs.h"

MsgQs_t* initializeMsgQs();
int createQ(MsgQs_t* q, int identifer);
void unloadMsgQs(MsgQs_t* q);
void sendMessageBatch(MsgQs_t* q, char* sender, char* subject, char* content);
void listQs(nodeMsg_t* front);
int deleteQ(MsgQs_t* q, int identifier);
int sendMessage(MsgQs_t *q, void *ID, char *sender, char *subject,
				char *content);
int purgeQs(MsgQs_t *q, void *identifier);
int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages);
#endif
