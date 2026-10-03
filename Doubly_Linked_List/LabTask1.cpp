#include "LabTask.cpp"
 
void reverseList(DoublyLinkedList &list)
{
    DNode *current = list.head;
    DNode *temp = nullptr;
 
    while (current != nullptr)
    {
        temp = current->prev;           
        current->prev = current->next;
        current->next = temp;
        current = current->prev;        
    }
 
    temp = list.head;                   
    list.head = list.tail;
    list.tail = temp;
}
 
int main()
{
    DoublyLinkedList list;
    int values[] = {10, 20, 30, 40, 50};
    for (int v : values)
        list.insertEnd(v);
 
    cout << "Before reversing:" << endl;
    cout << "  Forward : "; list.displayForward();
    cout << "  Backward: "; list.displayBackward();
 
    reverseList(list);
 
    cout << "\nAfter reversing:" << endl;
    cout << "  Forward : "; list.displayForward();
    cout << "  Backward: "; list.displayBackward();
 
    return 0;
}