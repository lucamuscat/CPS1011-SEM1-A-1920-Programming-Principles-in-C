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
