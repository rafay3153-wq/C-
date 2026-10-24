#include <iostream>
#include <string>
using namespace std;
struct Patient {
    int id;
    string name;
    string condition;
    int priority;                          
};
struct PNode {
    Patient info;
    PNode* next;
};
const char* levelName(int p) {
    switch (p) {
        case 1:  return "Critical";
        case 2:  return "High";
        case 3:  return "Moderate";
        default: return "Low";
    }
}
class ERQueue {
    PNode* head;                           
 
    static void show(const Patient& p) {
        cout << "ID " << p.id << " | " << p.name << " | " << p.condition
             << " | P" << p.priority << " (" << levelName(p.priority) << ")";
    }
public:
    ERQueue() : head(nullptr) {}
    ERQueue(const ERQueue&) = delete;
    ERQueue& operator=(const ERQueue&) = delete;
    ~ERQueue() {
        while (head) { PNode* t = head; head = head->next; delete t; }
    }
    bool isEmpty() const { return head == nullptr; }
    void addPatient(const Patient& p) {
        if (p.priority < 1 || p.priority > 4) {
            cout << "[INVALID] Priority " << p.priority << " for " << p.name << " (must be 1-4)\n";
            return;
        }
        PNode* n = new PNode{p, nullptr};
        if (!head || p.priority < head->info.priority) {    
            n->next = head;
            head = n;
        } else {
            PNode* cur = head;
            while (cur->next && cur->next->info.priority <= p.priority) cur = cur->next;
            n->next = cur->next;
            cur->next = n;
        }
        cout << "[ADD] "; show(p); cout << "\n";
    }
    void treatNextPatient() {
        if (isEmpty()) { cout << "[TREAT] No patients waiting\n"; return; }
        PNode* old = head;
        cout << "[TREAT] "; show(old->info); cout << "\n";
        head = head->next;
        delete old;
    }
    void viewNextPatient() const {
        if (isEmpty()) { cout << "[NEXT] No patients waiting\n"; return; }
        cout << "[NEXT] "; show(head->info); cout << "\n";
    }
    void displayAllPatients() const {
        if (isEmpty()) { cout << "[QUEUE] Empty\n"; return; }
        cout << "[QUEUE] treatment order:\n";
        int pos = 1;
        for (const PNode* p = head; p; p = p->next) {
            cout << "  " << pos++ << ". "; show(p->info); cout << "\n";
        }
    }
};
int main() {
    ERQueue er;
    cout << "--- Test 1: empty queue ---\n";
    er.treatNextPatient();
    er.viewNextPatient();
    er.displayAllPatients();
    cout << "\n--- Test 2: arrival priorities 4, 1, 3, 2 ---\n";
    er.addPatient({1, "Adnan",  "Minor cut",       4});
    er.addPatient({2, "Bushra", "Cardiac arrest",  1});
    er.addPatient({3, "Chand",  "Fever",           3});
    er.addPatient({4, "Dawood", "Fracture",        2});
    er.displayAllPatients();
    er.viewNextPatient();
    cout << "\n--- Test 3: equal priorities keep arrival order (2, 3, 2, 3, 2) ---\n";
    while (!er.isEmpty()) er.treatNextPatient();
    er.addPatient({11, "Eman",   "Burn",        2});
    er.addPatient({12, "Fahad",  "Migraine",    3});
    er.addPatient({13, "Ghazal", "Deep wound",  2});
    er.addPatient({14, "Hamza",  "Sprain",      3});
    er.addPatient({15, "Iqra",   "Chest pain",  2});
    er.displayAllPatients();
    cout << "\n--- Test 4: invalid priority and a late critical patient ---\n";
    er.addPatient({16, "Junaid", "Unknown", 7});
    er.addPatient({17, "Kiran",  "Unknown", 0});
    er.addPatient({18, "Laiba",  "Severe bleeding", 1});
    er.treatNextPatient();
    er.treatNextPatient();
    er.displayAllPatients();
    return 0;
}