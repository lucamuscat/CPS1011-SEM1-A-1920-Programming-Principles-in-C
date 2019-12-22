#ifndef TASK2B_H
#define TASK2B_H
// include for size_t type.
#include <stdlib.h>
#include "task2b_structs.h"

MsgQs_t* initializeMsgQs();
int createQ(MsgQs_t *q, int identifer);
void unloadMsgQs(MsgQs_t *q);
void listQs(nodeMsg_t *front);
int deleteQ(MsgQs_t *q, int identifier);

#endif
