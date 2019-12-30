/*
  Since the MsgQs_t has to be placed in heap, this function will
  malloc, give it default values and return a pointer to it.
*/
MsgQs_t *initializeMsgQs();
