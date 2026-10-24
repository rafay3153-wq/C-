#include <iostream>
#include <string>
using namespace std;
const int CAPACITY = 5;
struct Passenger {
    string name;
    string category;                        
    int seat;
};
class ReservationDeque {
    Passenger data[CAPACITY];
    int front, rear;                        
    static void show(const Passenger& p) {
        cout << p.name << " [" << p.category << "] seat " << p.seat;
    }
    void status() const { cout << "   front=" << front << " rear=" << rear << "\n"; }
public:
    ReservationDeque() : front(-1), rear(-1) {}
    bool isEmpty() const { return front == -1; }
    bool isFull() const { return (rear + 1) % CAPACITY == front; }
    void bookAtFront(const string& name, int seat) {          
        if (isFull()) { cout << "[FULL] Cannot book VIP " << name << "\n"; return; }
        if (isEmpty()) front = rear = 0;
        else front = (front - 1 + CAPACITY) % CAPACITY;       
        data[front] = {name, "VIP", seat};
        cout << "[BOOK FRONT] "; show(data[front]); status();
    }
    void bookAtRear(const string& name, int seat) {          
        if (isFull()) { cout << "[FULL] Cannot book Regular " << name << "\n"; return; }
        if (isEmpty()) front = rear = 0;
        else rear = (rear + 1) % CAPACITY;                    
        data[rear] = {name, "Regular", seat};
        cout << "[BOOK REAR] "; show(data[rear]); status();
    }
    void cancelFromFront() {
        if (isEmpty()) { cout << "[EMPTY] Nothing to cancel at front\n"; return; }
        cout << "[CANCEL FRONT] "; show(data[front]);
        if (front == rear) front = rear = -1;
        else front = (front + 1) % CAPACITY;
        status();
    }
    void cancelFromRear() {
        if (isEmpty()) { cout << "[EMPTY] Nothing to cancel at rear\n"; return; }
        cout << "[CANCEL REAR] "; show(data[rear]);
        if (front == rear) front = rear = -1;
        else rear = (rear - 1 + CAPACITY) % CAPACITY;
        status();
    }
    void viewFrontReservation() const {
        if (isEmpty()) { cout << "[FRONT] Deque is empty\n"; return; }
        cout << "[FRONT] "; show(data[front]); cout << "\n";
    }
    void viewRearReservation() const {
        if (isEmpty()) { cout << "[REAR] Deque is empty\n"; return; }
        cout << "[REAR] "; show(data[rear]); cout << "\n";
    }
    void displayAllReservations() const {
        if (isEmpty()) { cout << "[ALL] No reservations"; status(); return; }
        cout << "[ALL] front -> rear:"; status();
        for (int i = front; ; i = (i + 1) % CAPACITY) {
            cout << "  index " << i << ": "; show(data[i]); cout << "\n";
            if (i == rear) break;
        }
    }
};
int main() {
    ReservationDeque d;
    cout << "--- Test 1: empty deque ---\n";
    cout << "isEmpty=" << d.isEmpty() << " isFull=" << d.isFull() << "\n";
    d.cancelFromFront();
    d.cancelFromRear();
    d.viewFrontReservation();
    d.viewRearReservation();
    cout << "\n--- Test 2: single reservation ---\n";
    d.bookAtRear("Asad", 12);
    d.viewFrontReservation();
    d.viewRearReservation();
    d.cancelFromRear();                     
    cout << "\n--- Test 3: mix of regular and VIP, fill the deque (front wraps) ---\n";
    d.bookAtRear("Asad", 12);
    d.bookAtRear("Bushra", 13);
    d.bookAtRear("Chand", 14);
    d.bookAtFront("Dr. Daud", 1);           
    d.bookAtFront("Elahi", 2);
    d.bookAtRear("Farah", 15);              
    cout << "isFull=" << d.isFull() << "\n";
    d.displayAllReservations();
    cout << "\n--- Test 4: cancellations and reuse (rear wraps) ---\n";
    d.cancelFromFront();
    d.cancelFromRear();
    d.bookAtRear("Gul", 16);
    d.bookAtRear("Hina", 17);
    d.displayAllReservations();
    cout << "\n--- Test 5: empty completely ---\n";
    while (!d.isEmpty()) d.cancelFromFront();
    d.displayAllReservations();
    return 0;
}