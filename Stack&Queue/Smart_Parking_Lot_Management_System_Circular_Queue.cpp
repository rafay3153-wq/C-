#include <iostream>
#include <string>
using namespace std;
const int SLOTS = 5;
struct Car {
    string carNumber;
    string arrivalTime;
    int slotNumber;                        
};
class ParkingQueue {
    Car data[SLOTS];
    int front, rear;                        
 
    static void show(const Car& c) {
        cout << c.carNumber << " | arrived " << c.arrivalTime << " | slot " << c.slotNumber;
    }
    void status() const { cout << "   front=" << front << " rear=" << rear << "\n"; }
public:
    ParkingQueue() : front(-1), rear(-1) {}
    bool isEmpty() const { return front == -1; }
    bool isFull() const { return (rear + 1) % SLOTS == front; }
    void parkCar(const string& number, const string& time) {
        if (isFull()) { cout << "[FULL] No free slot for " << number << "\n"; return; }
        if (isEmpty()) front = rear = 0;
        else rear = (rear + 1) % SLOTS;     
        data[rear] = {number, time, rear + 1};
        cout << "[PARK] "; show(data[rear]); status();
    }
    void removeCar() {
        if (isEmpty()) { cout << "[EMPTY] No car to remove\n"; return; }
        cout << "[REMOVE] "; show(data[front]);
        if (front == rear) front = rear = -1;   
        else front = (front + 1) % SLOTS;
        status();
    }
    void viewNextCar() const {
        if (isEmpty()) { cout << "[NEXT] Parking is empty\n"; return; }
        cout << "[NEXT] "; show(data[front]); cout << "\n";
    }
    void displayParkingStatus() const {
        if (isEmpty()) { cout << "[STATUS] Empty"; status(); return; }
        cout << "[STATUS] front -> rear:";
        status();
        for (int i = front; ; i = (i + 1) % SLOTS) {
            cout << "  index " << i << ": "; show(data[i]); cout << "\n";
            if (i == rear) break;
        }
    }
};
int main() {
    ParkingQueue p;
    cout << "--- Test 1: empty ---\n";
    cout << "isEmpty=" << p.isEmpty() << " isFull=" << p.isFull() << "\n";
    p.removeCar();
    p.viewNextCar();
    p.displayParkingStatus();
    cout << "\n--- Test 2: fill the lot ---\n";
    p.parkCar("LEA-1001", "08:00");
    p.parkCar("ISB-2002", "08:10");
    p.parkCar("RWP-3003", "08:20");
    p.parkCar("LHR-4004", "08:30");
    p.parkCar("KHI-5005", "08:40");
    p.parkCar("PBA-6006", "08:50");         
    cout << "isFull=" << p.isFull() << "\n";
    cout << "\n--- Test 3: remove two cars, then park two (wrap-around) ---\n";
    p.removeCar();
    p.removeCar();
    p.parkCar("ABC-7007", "09:00");         
    p.parkCar("XYZ-8008", "09:10");         
    p.displayParkingStatus();
    p.viewNextCar();
    cout << "\n--- Test 4: empty the lot, then reuse ---\n";
    while (!p.isEmpty()) p.removeCar();
    p.removeCar();
    p.parkCar("NEW-9009", "10:00");
    p.displayParkingStatus();
    return 0;
}