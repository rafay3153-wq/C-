#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int Data) {
        data = Data;
        next = NULL;
    }
};
void display(Node* head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }
    Node* current = head;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}
Node* DeleteEven(Node* head) {
    if (head == NULL)
        return NULL;
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    Node* last = head;
    while (last->next != head) {
        last = last->next;
    }
    Node* current = head;
    Node* prev = last;
    for (int i = 0; i < count; i++) {
        Node* nextNode = current->next;
        if (current->data % 2 == 0) {
            if (current == prev) {
                delete current;
                return NULL;
            }
            prev->next = nextNode;
            if (current == head) {
                head = nextNode;
            }
            delete current;
            current = nextNode;
        }
        else {
            prev = current;
            current = nextNode;
        }
    }
    return head;
}
Node* DeleteOdd(Node* head) {
    if (head == NULL)
        return NULL;
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    Node* last = head;
    while (last->next != head) {
        last = last->next;
    }
    Node* current = head;
    Node* prev = last;
    for (int i = 0; i < count; i++) {
        Node* nextNode = current->next;
        if (current->data % 2 != 0) {
            if (current == prev) {
                delete current;
                return NULL;
            }
            prev->next = nextNode;
            if (current == head) {
                head = nextNode;
            }
            delete current;
            current = nextNode;
        }
        else {
            prev = current;
            current = nextNode;
        }
    }
    return head;
}
int main() {
    Node* head = new Node(10);
    Node* node2 = new Node(11);
    Node* node3 = new Node(20);
    Node* node4 = new Node(88);
    Node* node5 = new Node(14);
    Node* node6 = new Node(12);
    Node* node7 = new Node(7);
    Node* node8 = new Node(9);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node7;
    node7->next = node8;
    node8->next = head;
    cout << "Displaying The Original List:" << endl;
    display(head);
    char choice;
    cout << "Do you want to delete Even Nodes (1) "
         << "or Odd Nodes (0)?" << endl;
    cin >> choice;
    if (choice == '1') {
        head = DeleteEven(head);
        cout << "Displaying The Even Deleted List:" << endl;
        display(head);
    }
    else if (choice == '0') {
        head = DeleteOdd(head);
        cout << "Displaying The Odd Deleted List:" << endl;
        display(head);
    }
    else {
        cout << "Invalid choice." << endl;
    }
    return 0;
}
