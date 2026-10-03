#include <iostream>
using namespace std;
 
const int STUDENTS = 10;
const int TOTAL_MARKS = 15;
 
double averageMarks(int marks[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += marks[i];
    return (double)sum / size;
}
 
int main()
{
    int marks[STUDENTS];
 
    cout << "Enter quiz 1 marks (out of " << TOTAL_MARKS << ") of "
         << STUDENTS << " students:" << endl;
    for (int i = 0; i < STUDENTS; i++)
    {
        do
        {
            cout << "Student " << i + 1 << ": ";
            cin >> marks[i];
            if (marks[i] < 0 || marks[i] > TOTAL_MARKS)
                cout << "  Invalid! Marks must be between 0 and "
                     << TOTAL_MARKS << "." << endl;
        } while (marks[i] < 0 || marks[i] > TOTAL_MARKS);
    }
 
    cout << "\nMarks: ";
    for (int i = 0; i < STUDENTS; i++)
        cout << marks[i] << " ";
    cout << endl;
 
    double avg = averageMarks(marks, STUDENTS);
    cout << "Average marks of the class = " << avg
         << " out of " << TOTAL_MARKS << endl;
    return 0;
}