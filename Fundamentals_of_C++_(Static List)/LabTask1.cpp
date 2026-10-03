#include <iostream>
using namespace std;
 
int main()
{
    int start, stop;
    long long sum = 0;
 
    cout << "Enter the starting value: ";
    cin >> start;
    cout << "Enter the stopping value: ";
    cin >> stop;
 
    if (start > stop)
    {
        cout << "Starting value must not be greater than stopping value." << endl;
        return 1;
    }
 
    int x = start;
    while (x <= stop)
    {
        cout << x << "^2 = " << x * x << endl;
        sum += (long long)x * x;
        x++;
    }
 
    cout << "Sum of X^2 from " << start << " to " << stop << " = " << sum << endl;
    return 0;
}
