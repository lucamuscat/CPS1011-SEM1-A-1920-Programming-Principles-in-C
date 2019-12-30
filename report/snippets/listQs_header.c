/*
  Places a new node inside of a specified MsgQs_t variable. Its
  identifier will be given as an arguement.

  @param q: A variable of type MsgQs_t which is going to have a
  new node added to it.
  @param identifier: Identifier for node.
  @return: Returns a status code, 0 is successful, ENQUEUE_ERROR
  otherwise
*/
int createQ(MsgQs_t *q, int identifier);
