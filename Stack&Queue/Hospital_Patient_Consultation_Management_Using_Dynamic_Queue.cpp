#include <iostream>
#include <string>
using namespace std;
struct Patient {
    string name;
    int id;
    string doctor;
    string appointmentTime;
};
struct PatientNode {
    Patient info;
    PatientNode* next;
};
class ConsultationQueue {
    PatientNode* front;                     
    PatientNode* rear;                      
    static void show(const Patient& p) {
        cout << p.name << " (ID " << p.id << ") | Dr. " << p.doctor << " | " << p.appointmentTime;
    }
public:
    ConsultationQueue() : front(nullptr), rear(nullptr) {}
    ConsultationQueue(const ConsultationQueue&) = delete;
    ConsultationQueue& operator=(const ConsultationQueue&) = delete;
    ~ConsultationQueue() {
        int freed = 0;
        while (front) { PatientNode* t = front; front = front->next; delete t; freed++; }
        rear = nullptr;
        cout << "[DESTRUCTOR] Released " << freed << " remaining node(s)\n";
    }
    bool isEmpty() const { return front == nullptr; }
    void addPatient(const Patient& p) {
        PatientNode* n = new PatientNode{p, nullptr};
        if (isEmpty()) front = rear = n;    
        else { rear->next = n; rear = n; }
        cout << "[ADD] "; show(p); cout << "\n";
    }
    void callNextPatient() {
        if (isEmpty()) { cout << "[CALL] No patients waiting\n"; return; }
        PatientNode* old = front;
        cout << "[CALL] Now consulting: "; show(old->info); cout << "\n";
        front = front->next;
        if (!front) rear = nullptr;         
        delete old;
    }
    void viewNextPatient() const {
        if (isEmpty()) { cout << "[NEXT] Queue is empty\n"; return; }
        cout << "[NEXT] "; show(front->info); cout << "\n";
    }
    void displayAllPatients() const {
        if (isEmpty()) { cout << "[QUEUE] Empty\n"; return; }
        cout << "[QUEUE] front -> rear:\n";
        for (const PatientNode* p = front; p; p = p->next) { cout << "  "; show(p->info); cout << "\n"; }
    }
};
int main() {
    ConsultationQueue q;
    cout << "--- Test 1: empty queue ---\n";
    cout << "isEmpty() = " << (q.isEmpty() ? "true" : "false") << "\n";
    q.callNextPatient();
    q.viewNextPatient();
    q.displayAllPatients();
    cout << "\n--- Test 2: single patient added and removed ---\n";
    q.addPatient({"Zainab Ali", 201, "Hamid", "09:00"});
    q.viewNextPatient();
    q.callNextPatient();
    cout << "isEmpty() = " << (q.isEmpty() ? "true" : "false") << "\n";
    cout << "\n--- Test 3: several patients (FIFO) ---\n";
    q.addPatient({"Imran Butt",  202, "Hamid", "09:15"});
    q.addPatient({"Nadia Khan",  203, "Saima", "09:30"});
    q.addPatient({"Faisal Mir",  204, "Hamid", "09:10"});    
    q.displayAllPatients();
    q.callNextPatient();
    q.viewNextPatient();
    q.displayAllPatients();
    cout << "\n--- Test 4: leave patients in the queue; destructor frees them ---\n";
    q.addPatient({"Rabia Noor", 205, "Saima", "10:00"});
    q.displayAllPatients();
    return 0;
}