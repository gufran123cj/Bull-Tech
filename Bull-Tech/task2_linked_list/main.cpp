#include "node.h"
#include <iostream>

static Node* create_list(const int* values, int n) {
    if (!values || n <= 0) return nullptr;
    Node* head = new Node{values[0], nullptr};
    Node* tail = head;
    for (int i = 1; i < n; ++i) {
        tail->next = new Node{values[i], nullptr};
        tail = tail->next;
    }
    return head;
}

static void print_list(Node* head) {
    for (; head; head = head->next)
        std::cout << head->data << (head->next ? " -> " : "\n");
}

static void print_list_with_addresses(Node* head) {
    for (int i = 0; head; head = head->next, ++i) {
        std::cout << "  [" << i << "] data=" << head->data
                  << "  addr=" << static_cast<const void*>(head)
                  << "  next=" << static_cast<const void*>(head->next) << '\n';
    }
}

static void free_list(Node* head) {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    int values[] = {10, 20, 30, 40, 50};
    Node* head = create_list(values, 5);

    std::cout << "--- Before delete ---\n";
    std::cout << "head = " << static_cast<const void*>(head) << '\n';
    std::cout << "List (value): ";
    print_list(head);
    std::cout << "List (with addresses):\n";
    print_list_with_addresses(head);

    int position;
    std::cout << "Enter position to delete (0-based): ";
    std::cin >> position;
    delete_with_position(&head, position);

    std::cout << "\n--- After delete ---\n";
    std::cout << "head = " << static_cast<const void*>(head) << '\n';
    std::cout << "List (value): ";
    print_list(head);
    std::cout << "List (with addresses):\n";
    print_list_with_addresses(head);

    free_list(head);
    return 0;
}
