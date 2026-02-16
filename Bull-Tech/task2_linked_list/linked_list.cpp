#include "node.h"
#include <iostream>

void delete_with_position(Node** head, int position) {
    if (!head || position < 0) return;

    Node** link = head;
    while (position > 0 && *link) {
        link = &((*link)->next);
        --position;
    }

    Node* victim = *link;
    if (!victim) return;

    std::cout << "Deleting node at " << static_cast<const void*>(victim)
              << " (data=" << victim->data << ")\n";
    *link = victim->next;
    delete victim;
}
