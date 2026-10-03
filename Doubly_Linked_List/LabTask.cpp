#include <iostream>
using namespace std;
 
struct DNode
{
    int data;
    DNode *prev = nullptr;
    DNode *next = nullptr;
};
 
class DoublyLinkedList
{
public:
    DNode *head = nullptr;
    DNode *tail = nullptr;
 
    ~DoublyLinkedList()
    {
        while (head != nullptr)
        {
            DNode *p = head;
            head = head->next;
            delete p;
        }
    }
 
    void insertEnd(int value)
    {
        DNode *p = new DNode;
        p->data = value;
        if (head == nullptr)
            head = tail = p;
        else
        {
            p->prev = tail;
            tail->next = p;
            tail = p;
        }
    }
 
    DNode *search(int key) const
    {
        DNode *p = head;
        while (p != nullptr && p->data != key)
            p = p->next;
        return p;
    }
 
    void displayForward() const
    {
        cout << "NULL <-> ";
        for (DNode *p = head; p != nullptr; p = p->next)
            cout << p->data << " <-> ";
        cout << "NULL" << endl;
    }
 
    void displayBackward() const
    {
        cout << "NULL <-> ";
        for (DNode *p = tail; p != nullptr; p = p->prev)
            cout << p->data << " <-> ";
        cout << "NULL" << endl;
    }
};