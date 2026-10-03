#include "LabTask.cpp"
 
bool swapNodes(DoublyLinkedList &list, int a, int b)
{
    if (a == b)
    {
        cout << "Both values are the same; nothing to swap." << endl;
        return false;
    }
 
    DNode *x = list.search(a);
    DNode *y = list.search(b);
    if (x == nullptr || y == nullptr)
    {
        cout << "Swap not possible: ";
        if (x == nullptr) cout << a << " not found. ";
        if (y == nullptr) cout << b << " not found.";
        cout << endl;
        return false;
    }
 
    if (y->next == x)                   
    {
        DNode *t = x; x = y; y = t;
    }
 
    DNode *xp = x->prev, *xn = x->next;
    DNode *yp = y->prev, *yn = y->next;
 
    if (xn == y)                        
    {
        x->prev = y;   x->next = yn;
        y->prev = xp;  y->next = x;
        if (xp) xp->next = y;
        if (yn) yn->prev = x;
    }
    else                              
    {
        x->prev = yp;  x->next = yn;
        y->prev = xp;  y->next = xn;
        if (xp) xp->next = y;
        if (xn) xn->prev = y;
        if (yp) yp->next = x;
        if (yn) yn->prev = x;
    }
 
    if (list.head == x)      list.head = y;     
    else if (list.head == y) list.head = x;
    if (list.tail == x)      list.tail = y;     
    else if (list.tail == y) list.tail = x;
 
    cout << "Nodes containing " << a << " and " << b << " swapped." << endl;
    return true;
}
 
int main()
{
    DoublyLinkedList list;
    int values[] = {10, 20, 30, 40, 50, 60};
    for (int v : values)
        list.insertEnd(v);
 
    cout << "Original list:" << endl;
    cout << "  Forward : "; list.displayForward();
 
    int a, b;
    cout << "\nEnter first value : "; cin >> a;
    cout << "Enter second value: "; cin >> b;
 
    if (swapNodes(list, a, b))
    {
        cout << "\nList after swapping:" << endl;
        cout << "  Forward : "; list.displayForward();
        cout << "  Backward: "; list.displayBackward();
    }
    return 0;
}