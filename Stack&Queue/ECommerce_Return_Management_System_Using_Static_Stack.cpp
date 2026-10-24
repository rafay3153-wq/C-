#include <iostream>
#include <string>
using namespace std;
const int MAX_REQUESTS = 5;                
struct ReturnRequest {
    int orderId;
    string customerName;
    string reason;
    string date;
};
class ReturnStack {
    ReturnRequest data[MAX_REQUESTS];      
    int top;                                
 
    static void show(const ReturnRequest& r) {
        cout << "Order #" << r.orderId << " | " << r.customerName
             << " | Reason: " << r.reason << " | Date: " << r.date << "\n";
    }
public:
    ReturnStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == MAX_REQUESTS - 1; }
    void pushReturnRequest(const ReturnRequest& r) {
        if (isFull()) {
            cout << "[OVERFLOW] Stack full - cannot add order #" << r.orderId << "\n";
            return;
        }
        data[++top] = r;                   
        cout << "[PUSH] "; show(r);
    }
    void popReturnRequest() {
        if (isEmpty()) {
            cout << "[UNDERFLOW] No return requests to process\n";
            return;
        }
        cout << "[POP] Processed: "; show(data[top]);
        top--;                             
    }
    void peekLatestRequest() const {
        if (isEmpty()) {
            cout << "[PEEK] Stack is empty\n";
            return;
        }
        cout << "[PEEK] Latest: "; show(data[top]);
    }
    void displayAllRequests() const {
        if (isEmpty()) {
            cout << "[DISPLAY] No pending requests\n";
            return;
        }
        cout << "[DISPLAY] Pending requests (top -> bottom), top = " << top << ":\n";
        for (int i = top; i >= 0; i--) { cout << "  [" << i << "] "; show(data[i]); }
    }
};
int main() {
    ReturnStack s;
    cout << "--- Test 1: empty stack ---\n";
    s.popReturnRequest();
    s.peekLatestRequest();
    s.displayAllRequests();
    cout << "\n--- Test 2: normal pushes ---\n";
    s.pushReturnRequest({1001, "Ali Khan",   "Damaged item",    "2026-10-01"});
    s.pushReturnRequest({1002, "Sara Ahmed", "Wrong size",      "2026-10-02"});
    s.pushReturnRequest({1003, "Usman Raza", "Not as described","2026-10-03"});
    s.peekLatestRequest();
    s.displayAllRequests();
    cout << "\n--- Test 3: pop, then fill the stack (overflow) ---\n";
    s.popReturnRequest();
    s.pushReturnRequest({1004, "Hina Malik",  "Late delivery",  "2026-10-04"});
    s.pushReturnRequest({1005, "Bilal Shah",  "Defective",      "2026-10-05"});
    s.pushReturnRequest({1006, "Zara Iqbal",  "Changed mind",   "2026-10-06"});
    s.pushReturnRequest({1007, "Omar Farooq", "Wrong colour",   "2026-10-07"}); 
    s.displayAllRequests();
    cout << "\n--- Test 4: mixed push / pop / peek, then empty it ---\n";
    s.popReturnRequest();
    s.peekLatestRequest();
    while (!s.isEmpty()) s.popReturnRequest();
    s.popReturnRequest();                 
    s.displayAllRequests();
    return 0;
}