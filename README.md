# Simply Linked List with Shortcuts

A **simply linked list** containing:
- An integer value
- A level denoting the amount of pointers to be used in each node
- An array of a (macro) specified amount of `next` pointers 
  - Each pointing to the following node with the same as or smaller level

Functions in the [header file](https://github.com/fruit-bird/linked-list-shortcuts/blob/main/functions.h) are the basic functions to manipulate a linked list:
- `buildListR`: Building a list from a simple array
- `findNode`: Returning a pointer to a node with a given value (if it exists)
- `insertNode`: Inserts a node in any poisition
- `deleteNode`: Deletes a node in any position, while not breaking links in other levels
- `printAll`: Prints list with all levels in a readable way
