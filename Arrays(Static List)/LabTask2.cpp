#include <iostream>
using namespace std;
 
const int MAX_SIZE = 7;                 
 
struct ArrayList
{
    float Element[MAX_SIZE];
    int position = 0;                 
};
 
void insert(ArrayList *List, float value)
{
    if (List->position < MAX_SIZE)
        List->Element[List->position++] = value;
    else
        cout << "List is full." << endl;
}
 
void display(ArrayList *List)
{
    for (int i = 0; i < List->position; i++)
        cout << List->Element[i] << " ";
    cout << endl;
}
 
float findMax(ArrayList *List, int &dayIndex)
{
    float max = List->Element[0];
    dayIndex = 0;
    for (int i = 1; i < List->position; i++)
    {
        if (List->Element[i] > max)
        {
            max = List->Element[i];
            dayIndex = i;
        }
    }
    return max;
}
 
int main()
{
    const char *days[MAX_SIZE] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                                  "Friday", "Saturday", "Sunday"};
    ArrayList week;
    float t;
 
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << "Enter temperature for " << days[i] << " (C): ";
        cin >> t;
        insert(&week, t);
    }
 
    cout << "\nTemperatures of the week: ";
    display(&week);
 
    int day;
    float max = findMax(&week, day);
    cout << "Maximum temperature of the week = " << max
         << " C (" << days[day] << ")" << endl;
    return 0;
}