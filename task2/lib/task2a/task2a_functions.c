/*
  First implement a simple queue.
*/

#include "task2a_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MsgQs_t *initializeMsgQs() {
  // Initialize all of the nodes.
  MsgQs_t *q = (MsgQs_t *)malloc(sizeof(MsgQs_t));
  // Initialize the queue
  q->index = 0;
  return q;
}

int createQ(MsgQs_t *q, int identifier) {
  if (q->index < QUEUE_LIMIT) {
    q->nodes[q->index] = malloc(sizeof(node));
    q->nodes[q->index]->index = 0;
    q->nodes[q->index]->ID = identifier;
    q->index++;
    return SUCCESS;
  }
  return ENQUEUE_ERROR;
}

void unloadMsgQs(MsgQs_t *q) {
  // free nodes and msgqs_t
  for (size_t i = 0; i < q->index; ++i) {
    for (size_t j = 0; j < q->nodes[i]->index; ++j) {
      free(q->nodes[i]->messages[j]);
    }
    free(q->nodes[i]);
  }
  free(q);
}

void listQs(MsgQs_t *q) {
  for (size_t i = 0; i < q->index; ++i) {
    printf("=========\nIdentifier: %d\n", q->nodes[i]->ID);
    if (q->nodes[i]->index == 0) {
      puts("This Message Queue is Empty :(");
      continue;
    }
    for (size_t j = 0; j < q->nodes[i]->index; ++j) {
      printf("%d: %s\n", j, q->nodes[i]->messages[j]);
    }
  }
}

int deleteQ(MsgQs_t *q, int identifier) {
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier) {
      free(q->nodes[i]);
      // Final node in queue
      if (i == q->index) {
        q->index--;
      } else {
        // Not final node in queue
        // Shift following nodes back by 1.
        for (size_t j = i; j < q->index - 1; ++j) {
          q->nodes[i] = q->nodes[i + 1];
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
  if (node->index < MESSAGE_LIMIT) {
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
    // Strncpy will also prevent messages longer than CHAR_LIMIT
    // from being sent.
    strncpy(node->messages[node->index], message, CHAR_LIMIT);
    node->index++;
    return SUCCESS;
  }
  return SEND_ERROR;
}

void sendMessageBatch(MsgQs_t *q, char *message) {
  for (size_t i = 0; i < q->index; ++i) {
    sendIndividualMessage(q->nodes[i], message);
  }
}

/*
  If the identifer is null, use sendMessageBatch, otherwise just send
  the message
*/
int sendMessage(MsgQs_t *q, void *identifier, char *message) {
  if (identifier == NULL)
    sendMessageBatch(q, message);
  for (size_t i = 0; i < q->index; ++i) {
    if ((int)identifier == q->nodes[i]->ID) {
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
  for (size_t i = 0; i < q->index; ++i) {
    purgeIndividualNode(q->nodes[i]);
  }
}

int purgeQs(MsgQs_t *q, void *identifier) {
  // purge all
  if (identifier == NULL)
    purgeAllNodes(q);
  int int_id = (int)identifier;
  for (size_t i = 0; i < q->index; ++i) {
    if (int_id == q->nodes[i]->ID) {
      purgeIndividualNode(q->nodes[i]);
      return SUCCESS;
    }
  }
  return IDENTIFIER_ERROR;
}

int persistQ(MsgQs_t *q, int identifier) {
  node *node;
  for (size_t i = 0; i < q->index; ++i) {
    // Go through all the nodes and check their ID
    if (q->nodes[i]->ID == identifier)
      node = q->nodes[i];
  }
  if (node == NULL)
    return -1;

  FILE *file;
  char filename[26];
  sprintf(filename, "%d.dat", identifier);
  if ((file = fopen(filename, "w")) == NULL) {
    printf("ERROR OPENING %s", filename);
    fclose(file);
    return -1;
  }
  for (size_t i = 0; i < node->index; ++i) {
	// Go through each node and place it in the file, seperated by a
	// new line.
    fputs(strcat(node->messages[i], "\n"), file);
  }
  // Close the stream
  fclose(file);
  return SUCCESS;
}

int restoreQ(MsgQs_t *q, int identifier) {
  // search if identifier is in q
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier)
      // return an error if found.
      return -1;
  }

  FILE *file;
  char filename[26];
  sprintf(filename, "%d.dat", identifier);
  if ((file = fopen(filename, "r")) == NULL) {
    puts("This identifier has never been persisted");
    return -1;
  }
  // snippet taken from https://c-for-dummies.com/blog/?p=1112
  char buffer[CHAR_LIMIT];
  char *message = buffer;
  size_t buffer_size = 256;
  createQ(q, identifier);
  while (getline(&message, &buffer_size, file) != -1) {
    sendMessage(q, (void *)identifier, message);
  }
  free(message);
}

int receiveMessages(MsgQs_t *q, int identifier, size_t num_of_messages) {
  node *node;
  for (size_t i = 0; i < q->index; ++i) {
    if (q->nodes[i]->ID == identifier) {
      node = q->nodes[i];
    }
  }
  if (node == NULL)
    return -1;
  // Print it then free it.
  while (node->index > 0 && num_of_messages > 0) {
    printf("%d: %s", node->index, node->messages[node->index - 1]);
    free(node->messages[node->index]);
    node->index--;
    num_of_messages--;
  }
  return SUCCESS;
}
