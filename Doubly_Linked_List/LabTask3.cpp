#include "LabTask.cpp"
 
struct SNode
{
    int data;
    SNode *next = nullptr;
};
 
SNode *insertEndSingly(SNode *head, int value)
{
    SNode *p = new SNode;
    p->data = value;
    if (head == nullptr)
        return p;
    SNode *t = head;
    while (t->next != nullptr)
        t = t->next;
    t->next = p;
    return head;
}
 
void displaySingly(SNode *head)
{
    for (SNode *p = head; p != nullptr; p = p->next)
        cout << p->data << " -> ";
    cout << "NULL" << endl;
}
 
DoublyLinkedList *convertToDoubly(SNode *head)
{
    DoublyLinkedList *dlist = new DoublyLinkedList;
    for (SNode *p = head; p != nullptr; p = p->next)
        dlist->insertEnd(p->data);      
    return dlist;
}
 
int main()
{
    SNode *head = nullptr;
    int values[] = {15, 25, 35, 45, 55};
    for (int v : values)
        head = insertEndSingly(head, v);
 
    cout << "Singly linked list:" << endl;
    cout << "  "; displaySingly(head);
 
    DoublyLinkedList *dlist = convertToDoubly(head);
 
    cout << "\nConverted doubly linked list:" << endl;
    cout << "  Forward : "; dlist->displayForward();
    cout << "  Backward: "; dlist->displayBackward();
 
    delete dlist;
    while (head != nullptr)
    {
        SNode *t = head;
        head = head->next;
        delete t;
    }
    return 0;
}