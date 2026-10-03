#include <iostream>
using namespace std;
 
struct Node
{
    int data;
    Node *next = nullptr;
};
 
class SinglyLinkedList
{
public:
    Node *first = nullptr;
    Node *last = nullptr;
 
    ~SinglyLinkedList()
    {
        while (first != nullptr)
        {
            Node *p = first;
            first = first->next;
            delete p;
        }
    }
 
    void insertEnd(int value)
    {
        Node *p = new Node;
        p->data = value;
        if (first == nullptr)
            first = last = p;
        else
        {
            last->next = p;
            last = p;
        }
    }
 
    void display() const
    {
        if (first == nullptr) { cout << "List is empty." << endl; return; }
        for (Node *p = first; p != nullptr; p = p->next)
            cout << p->data << " -> ";
        cout << "NULL" << endl;
    }
};