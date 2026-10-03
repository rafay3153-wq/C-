#include "LabTask.cpp"
 
int main()
{
    ArrayList list;
    int choice, value, key;
 
    do
    {
        cout << "\n--- Array List Menu ---" << endl;
        cout << "1. Insert at end" << endl;
        cout << "2. Insert at start" << endl;
        cout << "3. Insert after a value" << endl;
        cout << "4. Insert before a value" << endl;
        cout << "5. Display list" << endl;
        cout << "6. Delete from end" << endl;
        cout << "7. Delete from start" << endl;
        cout << "8. Delete a specific value" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
 
        switch (choice)
        {
        case 1:
            cout << "Enter value: "; cin >> value;
            list.insertEnd(value);
            break;
        case 2:
            cout << "Enter value: "; cin >> value;
            list.insertStart(value);
            break;
        case 3:
            cout << "Insert after which value? "; cin >> key;
            cout << "Enter new value: "; cin >> value;
            list.insertAfter(key, value);
            break;
        case 4:
            cout << "Insert before which value? "; cin >> key;
            cout << "Enter new value: "; cin >> value;
            list.insertBefore(key, value);
            break;
        case 5:
            list.display();
            break;
        case 6:
            list.deleteEnd();
            break;
        case 7:
            list.deleteStart();
            break;
        case 8:
            cout << "Enter value to delete: "; cin >> value;
            list.deleteValue(value);
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
 
    return 0;
}