#include "LabTask.cpp"
 
SinglyLinkedList *mergeLists(const SinglyLinkedList &a, const SinglyLinkedList &b)
{
    SinglyLinkedList *merged = new SinglyLinkedList;
 
    for (Node *p = a.first; p != nullptr; p = p->next)
        merged->insertEnd(p->data);
 
    for (Node *p = b.first; p != nullptr; p = p->next)
        merged->insertEnd(p->data);
 
    return merged;
}
 
int main()
{
    SinglyLinkedList list1, list2;
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8, 10};
    for (int v : a) list1.insertEnd(v);
    for (int v : b) list2.insertEnd(v);
 
    cout << "List 1: "; list1.display();
    cout << "List 2: "; list2.display();
 
    SinglyLinkedList *list3 = mergeLists(list1, list2);
    cout << "Merged: "; list3->display();
 
    cout << "\nOriginal lists after merge (unchanged):" << endl;
    cout << "List 1: "; list1.display();
    cout << "List 2: "; list2.display();
 
    delete list3;
    return 0;
}