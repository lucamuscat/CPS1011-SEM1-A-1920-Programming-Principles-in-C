#include "rlp.h"
#include "task2b_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
  Most of these functions are recursive in nature,
*/

_Bool contains_id(nodeMsg_t *front, int identifier) {
  if (front == NULL)
    return 0;

  if (front->next == NULL)
    return front->ID == identifier;

  if (front->ID == identifier)
    return 1;

  return contains_id(front->next, identifier);
}

// Returns EMPTY_ERROR when empty and 1 when not empty.
int is_empty(MsgQs_t *queue) { return queue->size == 0; }

void free_individual_item(Item *Item) {
  free(Item->message->content);
  free(Item->message->subject);
  free(Item->message);
  free(Item->sender);
  free(Item);
}

void free_item(Item *Item) {
  if(Item == NULL)
	return;

  if (Item->next != NULL)
    free_item(Item->next);
  free_individual_item(Item);
  return;
}

// Free everything using tail-recursion.  This way, we won't need a
// pointer to the previous element Since all we need to do is go back
// up the stack.
void free_node(nodeMsg_t *node) {
  if (node->next != NULL)
    free_node(node->next);
  free_item(node->front);
  free(node);
  return;
}

void printItem(Item *Item) {
  printf("\nSender: %s\n", Item->sender);
  printf("Subject: %s\n", Item->message->subject);
  printf("%s\n", Item->message->content);
  printf("Expiry: %llu\n", Item->expiry);
}

/*
  Is the next node null? If so, pass the next node into listItems.
  If the next node isn't null just bubble up the stack.
 */

void listItems(Item *Item) {
  printItem(Item);
  if (Item->next != NULL)
    listItems(Item->next);
  return;
}

int removeQ(nodeMsg_t *front, int identifier) {
  /*
	Are we on the rear node? If so return an error since the ID
	doesn't exist.
  */
  if (front->next == NULL)
    return -1;

  if (front->next->ID == identifier) {
    nodeMsg_t *next = front->next;
    next->size = 0;
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
Item *create_item(char *sender, char *subject, char *content) {
  Item *temp = malloc(sizeof(Item));
  temp->sender = malloc(sizeof(char) * rlp_strlen(sender));
  temp->message = malloc(sizeof(Message));
  temp->message->subject = malloc(sizeof(char) * rlp_strlen(subject));
  temp->message->content = malloc(sizeof(char) * rlp_strlen(content));
  // Plus 4 since time_t is an unsigned int which is 4 bytes.
  temp->bytes = strlen(sender) + strlen(subject) + strlen(content) + 4;
  temp->message->bytes = strlen(subject) + strlen(content);

  time(&temp->expiry);
  rlp_encode_str(temp->sender, sender);
  rlp_encode_str(temp->message->subject, subject);
  rlp_encode_str(temp->message->content, content);
  temp->next = NULL;

  return temp;
}

// return number of bytes written

int enqueue_nodeMsg_t(nodeMsg_t *q, char *sender, char *subject,
                      char *content) {
  Item *tmp;
  tmp = create_item(sender, subject, content);
  // is the node not empty?
  if (q->size != 0) {
    q->rear->next = tmp;
    q->rear = tmp;
  } else {
    q->front = q->rear = tmp;
  }
  q->size++;
}

void batch_populate_node(nodeMsg_t *front, char *sender, char *subject,
                         char *content) {
  if (front == NULL)
    return;
  enqueue_nodeMsg_t(front, sender, subject, content);
  if (front->next != NULL)
    batch_populate_node(front->next, sender, subject, content);
  return;
}

int populate_individual_node(nodeMsg_t *front, int ID, char *sender,
                             char *subject, char *content) {
  // Return an error if the first node is null.
  if (front == NULL)
    return -1;

  // If the ID's match, populate the node.
  if (front->ID == ID) {
    enqueue_nodeMsg_t(front, sender, subject, content);
    return 1;
  }

  /*
    Check if we aren't at the last node.  If we are, that means
    that the previous condition which checks for the Identifier
    failed
  */
  if (front->next != NULL)
    return populate_individual_node(front->next, ID, sender, subject, content);

  // The code can only reach this case if it is the last node in the linkedlist.

  return -1;
}

// Takes the front of a MsgQs_t.
void empty_all_qs(nodeMsg_t *front) {

  free_item(front->front);
  front->size = 0;
  if (front->next != NULL) {
    return empty_all_qs(front->next);
  }
  return;
}

// Empties a queue with a specific ID.
int empty_q(nodeMsg_t *front, int identifier) {

  if (front->next == NULL)
    return -1;

  if (front->next->ID == identifier) {
    nodeMsg_t *next = front->next;
    next->size = 0;
    // Free all the Qs items
    free_item(next->front);
    return 1;
  }

  /*
    If the next node isn't null or an identifier, go to the next
    node to repeat the process. This way, the result will bubble
    back up the stack.
  */
  return empty_q(front->next, identifier);
}

// Update the bytes variable which falls under nodeMsg_t.
// This will just recurse through all of the items and sum their bytes.
// provide the front Item of the node.
size_t update_node_bytes(Item *front) {
  if (front == NULL)
    return 0;

  if (front->next != NULL) {
    return front->bytes + update_node_bytes(front->next);
  }
  // This statement will only be reached by the last Item.
  return front->bytes;
}

/*
  Skip the list encoding of the file by moving the file pointer
  accordingly.
*/

void skip_list(FILE *file) {
  unsigned char ch = fgetc(file);
  if (ch >= 0xc0 && ch <= 0xf7) {
    /*
      Self encoding list
      Since the encoding is only 1 byte long the next fgetc will get a valid
      char
    */
    return;
  } else if (ch >= 0xf8 && ch <= 0xff) {
    size_t byte_length = ch - 0xf7;
    while (byte_length > 0) {
      // Skip the byte characters representing the list length
      fgetc(file);
      byte_length--;
    }
  }
}

long int decode_expiry(FILE *file) {
  unsigned char ch = fgetc(file);
  long int temp;
  fread(&temp, sizeof(long int), 1, file);
  return temp;
}


/*
  Decode the string according to the character obtained.
  The algorithm followed can be found in the Ethereum RLP wiki.
*/
char *decode_string(FILE *file) {
  unsigned char ch = fgetc(file);
  char *buffer;
  if (ch < 0x80) {
    buffer = malloc(sizeof(char) * 2);
    buffer[0] = ch;
    buffer[1] = '\0';
    return buffer;
  } else if (ch >= 0x80 && ch < 0xb8) {
    // 0x7f instead of 0x80 due to the fact that if we get 0x80 and minus it by
    // 0x80 we will get a length of 0
    size_t length = ch - 0x80;
    buffer = malloc(sizeof(char) * length + 1);
    fread(buffer, sizeof(char), length, file);
    buffer[length] = '\0';
    return buffer;
  } else if (ch >= 0xb8 && ch < 0xbf) {
    size_t byte_length = ch - 0xb7;
    size_t size = 0;
    for (size_t i = 0; i < byte_length; ++i) {
      size |= fgetc(file) << 8 * (byte_length - 1 - i);
    }
    buffer = malloc(sizeof(char) * size);
    fread(buffer, sizeof(char), size, file);
    buffer[size] = '\0';
    return buffer;
  }
}
