void listItems(Item *Item) {
  printItem(Item);
  if (Item->next != NULL)
    listItems(Item->next);
  return;
}
