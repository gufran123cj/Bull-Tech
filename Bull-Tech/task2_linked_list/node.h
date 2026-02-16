#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    Node* next;
};

void delete_with_position(Node** head, int position);

#endif
