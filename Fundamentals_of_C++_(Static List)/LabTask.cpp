#include <iostream>
using namespace std;
 
class ArrayList
{
    static const int MAX = 100;
    int data[MAX];
    int count;
 
    int findIndex(int value) const
    {
        for (int i = 0; i < count; i++)
            if (data[i] == value)
                return i;
        return -1;
    }
 
    void shiftRight(int pos)
    {
        for (int i = count; i > pos; i--)
            data[i] = data[i - 1];
    }
 
    void shiftLeft(int pos)
    {
        for (int i = pos; i < count - 1; i++)
            data[i] = data[i + 1];
    }
 
public:
    ArrayList() : count(0) {}
 
    int size() const { return count; }
    int at(int i) const { return data[i]; }
 
    void insertEnd(int value)
    {
        if (count == MAX) { cout << "List is full." << endl; return; }
        data[count++] = value;
    }
 
    void insertStart(int value)
    {
        if (count == MAX) { cout << "List is full." << endl; return; }
        shiftRight(0);
        data[0] = value;
        count++;
    }
 
    void insertAfter(int key, int value)
    {
        if (count == MAX) { cout << "List is full." << endl; return; }
        int pos = findIndex(key);
        if (pos == -1) { cout << "Value " << key << " not found." << endl; return; }
        shiftRight(pos + 1);
        data[pos + 1] = value;
        count++;
    }
 
    void insertBefore(int key, int value)
    {
        if (count == MAX) { cout << "List is full." << endl; return; }
        int pos = findIndex(key);
        if (pos == -1) { cout << "Value " << key << " not found." << endl; return; }
        shiftRight(pos);
        data[pos] = value;
        count++;
    }
 
    void display() const
    {
        if (count == 0) { cout << "List is empty." << endl; return; }
        cout << "List: ";
        for (int i = 0; i < count; i++)
            cout << data[i] << " ";
        cout << endl;
    }
 
    void deleteEnd()
    {
        if (count == 0) { cout << "List is empty." << endl; return; }
        cout << "Deleted " << data[count - 1] << " from the end." << endl;
        count--;
    }
 
    void deleteStart()
    {
        if (count == 0) { cout << "List is empty." << endl; return; }
        cout << "Deleted " << data[0] << " from the start." << endl;
        shiftLeft(0);
        count--;
    }
 
    void deleteValue(int value)
    {
        int pos = findIndex(value);
        if (pos == -1) { cout << "Value " << value << " not found." << endl; return; }
        shiftLeft(pos);
        count--;
        cout << "Deleted " << value << " from the list." << endl;
    }
};
