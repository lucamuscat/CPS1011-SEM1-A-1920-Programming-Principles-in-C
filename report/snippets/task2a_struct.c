typedef struct MsgQs_t {
  // This needs to be a pointer to nodes since we need to have the
  // ability to relinquish resources from specific nodes.
  node *nodes[NODE_LIMIT];
  unsigned int index;
} MsgQs_t;

/*
  Node represets a message queue. Each node needs to contain a null byte
  terminated char array (message) and an identifier (ID)
*/

typedef struct node {
  char *messages[MESSAGE_LIMIT];
  int ID;
  unsigned int index;
} node;
