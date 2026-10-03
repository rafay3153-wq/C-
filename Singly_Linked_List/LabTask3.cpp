#include "LabTask.cpp"
 
int findAllOccurrences(const SinglyLinkedList &list, int key)
{
    int position = 1, count = 0;
 
    cout << "Searching for " << key << "..." << endl;
    for (Node *p = list.first; p != nullptr; p = p->next, position++)
    {
        if (p->data == key)
        {
            count++;
            cout << "  Found at position " << position << endl;
        }
    }
 
    if (count == 0)
        cout << "  " << key << " is not present in the list." << endl;
    else
        cout << "  Total occurrences of " << key << ": " << count << endl;
    return count;
}
 
int main()
{
    SinglyLinkedList list;
    int values[] = {5, 12, 7, 12, 3, 12, 9, 7};
    for (int v : values)
        list.insertEnd(v);
 
    list.display();
    cout << endl;
 
    int key;
    cout << "Enter the value to search: ";
    cin >> key;
    findAllOccurrences(list, key);
 
    return 0;
}