/*
  This is the ADT.
*/


#ifndef TASK2B_H
#define TASK2B_H
// include for size_t type.
#include "task2b_structs.h"
#include <stdlib.h>
/*
  Operation: Initalize a MsgQs_t struct.
  Precondition: The variable needs to be NULL.
  Postcondition: The variable will contain the address of the
  initialized (but still empty)MsgQs_t.
*/
MsgQs_t *initializeMsgQs();

/*
  Operation: Enqueues a nodeMsg_t in the specified MsgQs_t containing
  the specified ID

  Precondition: MsgQs_t* q needs to have been initialized by
  initializeMsgQs().

  Postcondition: An empty and initialized nodeMsg_t will be enqueued
  in in the specified MsgQs_t.
*/
int createQ(MsgQs_t *q, int identifer);

/*
  Operation: Reliquish all resources allocated to specified MsgQs_t
  variable.

  Precondition: Everything added into the MsgQs_t was added by a
  provided API function. To make sure no segfaults occur.

  Postcondition: Everything in MsgQs_t will be freed, including
  MsgQs_t, leaving the provided MsgQ_t as a NULL pointer.
*/
void unloadMsgQs(MsgQs_t *q);

/*
  Operation: Send a message (Enqueue every nodeMsg_t with an Item) to
  every nodeMsg_t inside of the procided MsgQs_t

  Precondition: The MsgQs_t provided is initialized from before hand.

  Postcondition: Each nodeMsg_t under the provided MsgQs_t will
  contain a new item with the providied details.
*/
void sendMessageBatch(MsgQs_t *q, char *sender, char *subject, char *content);

/*
  Operation: List the ID, sender, subject, expiry and content of every
  nodeMsg_t. Message sent will also be RLP encoded.

  Precondition: The front of a MsgQs_t is provided (MsgQs_t -> front).

  Postcondition: All the nodeMsg_t will be listed to stdout.
*/
void listQs(nodeMsg_t *front);

/*
  Operation: Reliquishes resources related to a nodeMsg_t with the
  same ID as identifier.

  Precondition: nodeMsg_t specified through the identifier exists,
  otherwise an error will be thrown

  Postcondition: All resources held by the deleted nodeMsg_t will be
  relinquished
*/
int deleteQ(MsgQs_t *q, int identifier);

/*
  Operation: Sends a message (enqueues a nodeMsg_t with an item) to
  the specified ID or to all if the ID is null. If the ID doesn't
  exist, then an error will be thrown.

  Precondition: Node to which the message is going to be sent exists,
  otherwise an error will be thrown.

  Postcondition: A new item will be enqueued in the specified
  nodeMsg_t.
*/
int sendMessage(MsgQs_t *q, void *ID, char *sender, char *subject,
                char *content);

/*
  Operation: Completely dequeue a node from the specified MsgQs_t (and
  relinquish the node's resources). Message sent will also be RLP
  encoded

  Precondition: Node which is to be dequeued exists, otherwise an
  error will be thrown.

  Postcondition: Specified nodeMsg_t won't be found in specified
  MsgQs_t anymore.
*/
int purgeQs(MsgQs_t *q, void *identifier);

/*
  Operation: Display information related to an item, then dequeue it.

  Precondition: Specified nodeMsg_t contains items.

  Postcondition: The number of messages specified in the arguement
  will be displayed and popped (Of course if more is specified than
  what actually exists, the arguement will round down to the current
  max).

*/
int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages);

/*
 Operation: Persist specified MsgQs_t into a file which contains the
 identifier followed by .dat.

 Precondition: MsgQs_t is actaully initialized from before hand. Also
 the specified ID shouldn't have been persisted from before hand.

 Postcondition: A file with the name following the pattern "{ID}.dat"
 will be saved. The file will be saved with RLP encoding.
*/
int persistQ(MsgQs_t *MsgQ, int identifier);

/*
  Operation: Decode an RLP encoded nodeMsg_t.

  Precondition: The file specified actually exists, isn't corrupted
  and properly RLP encoded.

  Postcondition: The data decoded will be restored into the specified
  MsgQs_t.
*/
int restoreQ(MsgQs_t *MsgQ, int identifier);
#endif
