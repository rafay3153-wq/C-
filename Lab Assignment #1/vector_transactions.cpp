#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
using namespace std;
 
struct Statistics {
    int    count;
    double maximum;
    double minimum;
    double average;
};
 
class TransactionManager {
private:
    vector<double> transactions;
 
public:
    void insertTransaction(double amount) {
        transactions.push_back(amount);
    }
 
    bool deleteTransaction(int index) {
        if (index < 0 || index >= (int)transactions.size()) {
            cout << "  [Error] Invalid index " << index
                 << " (vector size = " << transactions.size() << ")\n";
            return false;
        }
        transactions.erase(transactions.begin() + index);
        return true; }
 
    int findAndUpdate(double oldAmount, double newAmount) {
        int updated = 0;
        for (size_t i = 0; i < transactions.size(); i++) {
            if (transactions[i] == oldAmount) {
                transactions[i] = newAmount;
                updated++;
            }
        }
        if (updated == 0)
            cout << "  [Info] Amount " << oldAmount << " not found. Nothing updated.\n";
        return updated;
    }

    Statistics calculateStatistics() const {
        Statistics s = {0, 0.0, 0.0, 0.0};
        if (transactions.empty()) return s;
        double sum = 0;
        s.maximum = s.minimum = transactions[0];
        for (size_t i = 0; i < transactions.size(); i++) {
            double x = transactions[i];
            sum += x;
            if (x > s.maximum) s.maximum = x;
            if (x < s.minimum) s.minimum = x;
        }
        s.count   = (int)transactions.size();
        s.average = sum / s.count;
        return s;
    }
    
    void displayTransactionsSorted(bool ascending) const {
        vector<double> copy = transactions;
        if (ascending) sort(copy.begin(), copy.end());
        else           sort(copy.begin(), copy.end(), greater<double>());
        cout << (ascending ? "  Sorted (ascending) : " : "  Sorted (descending): ");
        printVector(copy);
    }
 
    void display(const string& label) const {
        cout << "  " << label << ": ";
        printVector(transactions);
    }
 
    void printStatistics() const {
        Statistics s = calculateStatistics();
        if (s.count == 0) { cout << "  Statistics: no transactions stored.\n"; return; }
        cout << "  Statistics: count = " << s.count << ", max = " << s.maximum
             << ", min = " << s.minimum << ", avg = " << s.average << "\n";
    }
 
private:
    static void printVector(const vector<double>& v) {
        if (v.empty()) { cout << "(empty)\n"; return; }
        for (size_t i = 0; i < v.size(); i++)
            cout << v[i] << (i + 1 < v.size() ? ", " : "\n");
    }
};
 
int main() {
    cout << fixed << setprecision(2);

    cout << "===== TEST 1: Example from the assignment =====\n";
    TransactionManager tm;
    double init[] = {2500, 3200, 1800, 2500, 4000};
    for (double x : init) tm.insertTransaction(x);
    tm.display("Initial transactions");
    tm.deleteTransaction(2);
    tm.display("After deleteTransaction(2)");
    int n = tm.findAndUpdate(2500, 2600);
    cout << "  (" << n << " occurrence(s) updated)\n";
    tm.display("After findAndUpdate(2500, 2600)");tm.printStatistics();
    tm.displayTransactionsSorted(false);
    tm.displayTransactionsSorted(true);
 
    cout << "\n===== TEST 2: Invalid indexes =====\n";
    tm.deleteTransaction(-1);
    tm.deleteTransaction(4);
    tm.deleteTransaction(100);
    tm.display("Vector unchanged");
 
    cout << "\n===== TEST 3: Amount that does not exist =====\n";
    tm.findAndUpdate(9999, 1);
    tm.display("Vector unchanged");
 
    cout << "\n===== TEST 4: Delete first and last element =====\n";
    tm.deleteTransaction(0);
    tm.display("After deleteTransaction(0)");
    tm.deleteTransaction(2);
    tm.display("After deleteTransaction(2) [last]");
 
    cout << "\n===== TEST 5: Empty vector =====\n";
    TransactionManager empty;
    empty.printStatistics();
    empty.displayTransactionsSorted(true);
    empty.deleteTransaction(0);
 
    cout << "\n===== TEST 6: Single element and new data with decimals =====\n";
    TransactionManager one;
    one.insertTransaction(750.50);
    one.printStatistics();
    one.displayTransactionsSorted(false);
    TransactionManager more;
    double data[] = {120.75, 99.99, 5000, 99.99, 310.40};
    for (double x : data) more.insertTransaction(x);
    more.display("Data");
    more.findAndUpdate(99.99, 100.00);
    more.display("After findAndUpdate(99.99, 100.00)");
    more.printStatistics();
    more.displayTransactionsSorted(true);
    more.displayTransactionsSorted(false);
    return 0;
}