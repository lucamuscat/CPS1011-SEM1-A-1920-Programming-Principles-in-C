/*
  Simply free the MsgQs_t which is passed through the parameter. Of
  course in task 2a this will be a simple free. However, since linked
  lists are going to be used in task 2b, this process will have to be
  done recursively.

  @param *q: Pointer to MsgQs_t variable which needs to be
  relinquished.
  *q will also be set to null once the freeing process is done.
*/
void unloadMsgQs(MsgQs_t *q);
