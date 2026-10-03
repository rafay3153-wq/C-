#include "LabTask.cpp"
 
int linearSearch(const ArrayList &list, int key, int &comparisons)
{
    int i = 0;
    comparisons = 0;
    while (i < list.size())
    {
        comparisons++;
        if (list.at(i) == key)
            return i;
        i++;
    }
    return -1;
}
 
int main()
{
    ArrayList list;
    int n, value, key, comparisons;
 
    cout << "How many values do you want to enter? ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter value " << i + 1 << ": ";
        cin >> value;
        list.insertEnd(value);
    }
    list.display();
 
    cout << "Enter the value to search: ";
    cin >> key;
 
    int index = linearSearch(list, key, comparisons);
    if (index != -1)
        cout << key << " found at index " << index << " (position " << index + 1
             << ") after " << comparisons << " comparison(s)." << endl;
    else
        cout << key << " not found in the list after " << comparisons
             << " comparison(s)." << endl;
 
    return 0;
}