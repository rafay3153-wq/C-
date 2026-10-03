#include "LabTask.cpp"
 
void displayReverseLoop(Node *first)
{
    Node *stop = nullptr;           
    while (first != stop)
    {
        Node *p = first;
        while (p->next != stop)    
            p = p->next;
        cout << p->data << " ";
        stop = p;
    }
    cout << endl;
}

void displayReverseRecursive(Node *p)
{
    if (p == nullptr)              
        return;
    displayReverseRecursive(p->next);
    cout << p->data << " ";       
}
 
int main()
{
    SinglyLinkedList list;
    int values[] = {10, 20, 30, 40, 50};
    for (int v : values)
        list.insertEnd(v);
 
    cout << "Original list:" << endl;
    list.display();
 
    cout << "\nReverse display (using loops):" << endl;
    displayReverseLoop(list.first);
 
    cout << "\nReverse display (using recursion):" << endl;
    displayReverseRecursive(list.first);
    cout << endl;
 
    return 0;
}