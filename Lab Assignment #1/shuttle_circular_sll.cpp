#include <iostream>
#include <string>
using namespace std;
 
struct Stop {
    int    id;
    string name;
    int    distance;    
    Stop*  next;
    Stop(int i, const string& n, int d) : id(i), name(n), distance(d), next(nullptr) {}
};
 
class ShuttleRoute {
private:
    Stop* tail;        
 
    Stop* findStop(int id) const {
        if (tail == nullptr) return nullptr;
        Stop* cur = tail->next;
        do {
            if (cur->id == id) return cur;
            cur = cur->next;
        } while (cur != tail->next);
        return nullptr;
    }
 
public:
    ShuttleRoute() : tail(nullptr) {}
    ~ShuttleRoute() {
        if (tail == nullptr) return;      Stop* head = tail->next;
        tail->next = nullptr;              
        while (head != nullptr) {
            Stop* t = head;
            head = head->next;
            delete t;
        }
    }
 
    bool addStopAtEnd(int id, const string& name, int distance) {
        if (findStop(id) != nullptr) {
            cout << "  [Error] Stop ID " << id << " already exists.\n";
            return false;
        }
        Stop* n = new Stop(id, name, distance);
        if (tail == nullptr) {             
            n->next = n;
        } else {
            n->next    = tail->next;       
            tail->next = n;                
        }
        tail = n;                          
        return true;
    }
 
    bool addStopAfter(int id, int newId, const string& newName, int distance) {
        Stop* pos = findStop(id);
        if (pos == nullptr) {
            cout << "  [Error] Stop ID " << id << " not found. Cannot insert after it.\n";
            return false;
        }
        if (findStop(newId) != nullptr) {
            cout << "  [Error] Stop ID " << newId << " already exists.\n";
            return false;
        }
        Stop* n = new Stop(newId, newName, distance);
        n->next   = pos->next;
        pos->next = n;
        if (pos == tail) tail = n;        
        return true;
    }
 
    bool removeStop(int id) {
        if (tail == nullptr) {
            cout << "  [Error] Route is empty. Nothing to remove.\n";
            return false;
        }
        Stop* head = tail->next;
        Stop* prev = tail;
        Stop* cur  = head;
        do {
            if (cur->id == id) break;
            prev = cur;
            cur  = cur->next;
        } while (cur != head);
 
        if (cur->id != id) {
            cout << "  [Error] Stop ID " << id << " not found. Nothing removed.\n";
            return false;
        }
        if (cur->next == cur) {           
            tail = nullptr;
        } else {
            prev->next = cur->next;        
            if (cur == tail) tail = prev;  
        }
        cout << "  Removed stop " << cur->id << " (" << cur->name << ")\n";
        delete cur;
        return true;
    }
 
    void displayRoute() const {
        if (tail == nullptr) { cout << "  Route: (empty)\n"; return; }
        Stop* head = tail->next;
        cout << "  Route: ";
        Stop* cur = head;
        do {        cout << "[" << cur->id << ", " << cur->name << ", " << cur->distance << " km] -> ";
            cur = cur->next;
        } while (cur != head);
        cout << "back to " << head->name << "\n";
    }
 
    void findLongestDistance() const {
        if (tail == nullptr) { cout << "  [Info] Route is empty.\n"; return; }
        Stop* head = tail->next;
        int maxDist = head->distance;
        Stop* cur = head;
        do {
            if (cur->distance > maxDist) maxDist = cur->distance;
            cur = cur->next;
        } while (cur != head);
        cur = head;
        do {                                
            if (cur->distance == maxDist)
                cout << "  " << cur->name << " has the longest distance of " << maxDist
                     << " km to the next stop.\n";
            cur = cur->next;
        } while (cur != head);
    }
};
 
int main() {
    ShuttleRoute route;
 
    cout << "===== TEST 1: Example from the assignment =====\n";
    route.addStopAtEnd(1, "Main Gate",     2);
    route.addStopAtEnd(2, "Roller Coaster", 3);
    route.addStopAtEnd(3, "Water Park",    5);
    route.displayRoute();
    route.addStopAtEnd(4, "Zoo", 4);
    route.displayRoute();
    route.findLongestDistance();
 
    cout << "\n===== TEST 2: addStopAfter (middle, last, non-existing) =====\n";
    route.addStopAfter(2, 5, "Aquarium", 1);
    route.displayRoute();
    route.addStopAfter(4, 6, "Food Court", 2);       
    route.displayRoute();
    route.addStopAfter(42, 7, "Ghost Stop", 1);      
    route.addStopAtEnd(3, "Duplicate", 1);           
 
    cout << "\n===== TEST 3: removeStop (middle, first, last, non-existing) =====\n";
    route.removeStop(5);                             
    route.displayRoute();
    route.removeStop(1);                             
    route.displayRoute();
    route.removeStop(6);                             
    route.displayRoute();
    route.removeStop(99);                            
    route.findLongestDistance();
 
    cout << "\n===== TEST 4: Shrink to one stop, then empty =====\n";
    route.removeStop(2);
    route.removeStop(3);
    route.displayRoute();                           
    route.findLongestDistance();
    route.addStopAfter(4, 8, "Gift Shop", 6);        
    route.displayRoute();
    route.removeStop(8);
    route.removeStop(4);                             
    route.displayRoute();
    route.removeStop(4);                             
    route.findLongestDistance();
 
    cout << "\n===== TEST 5: Tie for longest distance =====\n";
    ShuttleRoute r2;
    r2.addStopAtEnd(1, "A", 4);
    r2.addStopAtEnd(2, "B", 7);
    r2.addStopAtEnd(3, "C", 7);
    r2.displayRoute();
    r2.findLongestDistance();
    return 0;
}