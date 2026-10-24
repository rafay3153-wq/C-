#include <iostream>
#include <string>
using namespace std;
const int QUEUE_CAP = 5;
struct Passenger {
    string name;
    string destination;
    string ticketType;                      
};
class ShuttleQueue {
    Passenger data[QUEUE_CAP];
    int front, rear;                      
    static void show(const Passenger& p) {
        cout << p.name << " -> " << p.destination << " [" << p.ticketType << "]";
    }
public:
    ShuttleQueue() : front(-1), rear(-1) {}
    bool isEmpty() const { return front == -1; }
    bool isFull() const { return rear == QUEUE_CAP - 1; }
    void enqueuePassenger(const Passenger& p) {
        if (isFull()) {
            cout << "[OVERFLOW] Cannot add " << p.name << " (rear = " << rear << ")\n";
            return;
        }
        if (isEmpty()) front = 0;           // first insertion
        data[++rear] = p;
        cout << "[ENQUEUE] "; show(p); cout << "   front=" << front << " rear=" << rear << "\n";
    }
    void dequeuePassenger() {
        if (isEmpty()) { cout << "[UNDERFLOW] No passengers waiting\n"; return; }
        cout << "[DEQUEUE] Ticket sold to "; show(data[front]);
        if (front == rear) front = rear = -1;  
        else front++;
        cout << "   front=" << front << " rear=" << rear << "\n";
    }
    void viewFrontPassenger() const {
        if (isEmpty()) { cout << "[FRONT] Queue is empty\n"; return; }
        cout << "[FRONT] "; show(data[front]); cout << "\n";
    }
    void displayQueue() const {
        if (isEmpty()) { cout << "[QUEUE] Empty\n"; return; }
        cout << "[QUEUE] front -> rear:\n";
        for (int i = front; i <= rear; i++) { cout << "  [" << i << "] "; show(data[i]); cout << "\n"; }
    }
};
int main() {
    ShuttleQueue q;
    cout << "--- Test 1: empty queue ---\n";
    q.dequeuePassenger();
    q.viewFrontPassenger();
    q.displayQueue();
    cout << "\n--- Test 2: normal arrivals and sales ---\n";
    q.enqueuePassenger({"Ahmed",  "Terminal 1", "Regular"});
    q.enqueuePassenger({"Fatima", "Terminal 3", "VIP"});     
    q.enqueuePassenger({"Hassan", "Terminal 2", "Regular"});
    q.viewFrontPassenger();
    q.dequeuePassenger();
    q.displayQueue();
    cout << "\n--- Test 3: fill the queue (overflow) ---\n";
    q.enqueuePassenger({"Ayesha", "Terminal 1", "Regular"});
    q.enqueuePassenger({"Bilal",  "Terminal 2", "VIP"});
    q.enqueuePassenger({"Maria",  "Terminal 3", "Regular"});  
    cout << "isFull() = " << (q.isFull() ? "true" : "false") << "\n";
    q.displayQueue();
    cout << "\n--- Test 4: empty it, then reuse (reset on last removal) ---\n";
    while (!q.isEmpty()) q.dequeuePassenger();
    q.dequeuePassenger();                   
    q.enqueuePassenger({"Kamran", "Terminal 1", "Regular"});  
    q.displayQueue();
    return 0;
}