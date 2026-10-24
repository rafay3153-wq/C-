#include <iostream>
#include <string>
using namespace std;
const int QUICK_LIMIT = 10;                
struct Order {
    int orderId;
    string restaurant;
    string address;
    string items;
    int prepTime;                           
    string orderTime;
};
struct OrderNode {
    Order info;
    OrderNode *prev, *next;
};
class DispatchDeque {
    OrderNode *front, *rear;
 
    static void show(const Order& o) {
        cout << "#" << o.orderId << " " << o.restaurant << " | " << o.items << " | "
             << o.address << " | prep " << o.prepTime << " min | ordered " << o.orderTime;
    }
public:
    DispatchDeque() : front(nullptr), rear(nullptr) {}
    DispatchDeque(const DispatchDeque&) = delete;
    DispatchDeque& operator=(const DispatchDeque&) = delete;
 
    ~DispatchDeque() {
        while (front) { OrderNode* t = front; front = front->next; delete t; }
    }
    bool isEmpty() const { return front == nullptr; }
    void addOrder(const Order& o) {
        OrderNode* n = new OrderNode{o, nullptr, nullptr};
        if (isEmpty()) {
            front = rear = n;
        } else if (o.prepTime <= QUICK_LIMIT) {    
            n->next = front;
            front->prev = n;
            front = n;
        } else {                                   
            n->prev = rear;
            rear->next = n;
            rear = n;
        }
        cout << "[ADD " << (o.prepTime <= QUICK_LIMIT ? "QUICK->front" : "NORMAL->rear") << "] ";
        show(o); cout << "\n";
    }
    void dispatchOrder() {
        if (isEmpty()) { cout << "[DISPATCH] No pending orders\n"; return; }
        OrderNode* old = front;
        cout << "[DISPATCH] "; show(old->info); cout << "\n";
        front = front->next;
        if (front) front->prev = nullptr; else rear = nullptr;
        delete old;
    }
    void viewNextOrder() const {
        if (isEmpty()) { cout << "[NEXT] No pending orders\n"; return; }
        cout << "[NEXT] "; show(front->info); cout << "\n";
    }
    void displayAllOrders() const {
        if (isEmpty()) { cout << "[ORDERS] Empty\n"; return; }
        cout << "[ORDERS] front -> rear:\n";
        for (const OrderNode* p = front; p; p = p->next) { cout << "  "; show(p->info); cout << "\n"; }
    }
    void cancelOrder(int orderId) {
        OrderNode* cur = front;
        while (cur && cur->info.orderId != orderId) cur = cur->next;    
        if (!cur) { cout << "[CANCEL] Order #" << orderId << " not found\n"; return; }
 
        if (cur->prev) cur->prev->next = cur->next; else front = cur->next;   
        if (cur->next) cur->next->prev = cur->prev; else rear = cur->prev;    
        cout << "[CANCEL] Removed "; show(cur->info); cout << "\n";
        delete cur;
    }
};
int main() {
    DispatchDeque d;
    cout << "--- Test 1: empty deque ---\n";
    d.dispatchOrder();
    d.viewNextOrder();
    d.cancelOrder(1);
    d.displayAllOrders();
    cout << "\n--- Test 2: mixed quick and normal orders ---\n";
    d.addOrder({101, "Karachi Biryani", "House 5, F-10",  "Chicken Biryani",   25, "12:00"});
    d.addOrder({102, "Pizza Point",     "Street 3, G-9",  "Large Pizza",       20, "12:02"});
    d.addOrder({103, "Juice Corner",    "Flat 7, F-8",    "Mango Juice",        5, "12:05"});
    d.addOrder({104, "Burger Hub",      "House 12, I-8",  "Zinger Burger",     10, "12:07"});  
    d.addOrder({105, "Grill House",     "House 9, G-10",  "BBQ Platter",       30, "12:10"});
    d.displayAllOrders();
    d.viewNextOrder();
    cout << "\n--- Test 3: cancellations (middle, last, first, missing) ---\n";
    d.cancelOrder(101);
    d.cancelOrder(105);
    d.cancelOrder(104);
    d.cancelOrder(999);
    d.displayAllOrders();
    cout << "\n--- Test 4: dispatch until empty, single-order case ---\n";
    d.dispatchOrder();
    d.displayAllOrders();
    d.dispatchOrder();
    d.dispatchOrder();
    d.addOrder({106, "Tea Stop", "Office 2, Blue Area", "Chai", 8, "12:20"});
    d.cancelOrder(106);                      
    d.displayAllOrders();
    d.addOrder({107, "Desi Dhaba", "House 1, E-7", "Karahi", 40, "12:30"});   
    return 0;
}