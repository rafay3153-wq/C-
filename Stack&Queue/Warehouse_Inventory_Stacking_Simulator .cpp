#include <iostream>
#include <string>
using namespace std;
const int MAX_BOXES = 10;
struct Box {
    string id;
    int weight;
};
class BoxStack {
    Box data[MAX_BOXES];
    int top;
    bool push(const Box& b) {
        if (top == MAX_BOXES - 1) { cout << "  [OVERFLOW] Stack full\n"; return false; }
        data[++top] = b;
        return true;
    }
    bool pop(Box& b) {
        if (top == -1) { cout << "  [UNDERFLOW] Stack empty\n"; return false; }
        b = data[top--];
        return true;
    }
public:
    BoxStack() : top(-1) {}
    bool isEmpty() const { return top == -1; }
 
    void addBox(const Box& nb) {
        cout << "Arriving: " << nb.id << " (" << nb.weight << " kg)\n";
        Box removed[MAX_BOXES];            
        int nRemoved = 0;
        while (!isEmpty() && data[top].weight < nb.weight)
            pop(removed[nRemoved++]);
 
        if (nRemoved > 0) {
            cout << "  Set aside " << nRemoved << " lighter box(es):";
            for (int i = 0; i < nRemoved; i++) cout << " " << removed[i].id << "(" << removed[i].weight << ")";
            cout << "\n";
        }
        if (push(nb)) cout << "  Pushed " << nb.id << "\n";
        displayStack();
    }
    void removeTopBox() {
        Box b;
        if (pop(b)) cout << "Removed top box: " << b.id << " (" << b.weight << " kg)\n";
    }
    void viewTopBox() const {
        if (isEmpty()) { cout << "View top: stack is empty\n"; return; }
        cout << "Top box: " << data[top].id << " (" << data[top].weight << " kg)\n";
    }
    void displayStack() const {
        if (isEmpty()) { cout << "  Stack (top -> bottom): empty\n"; return; }
        cout << "  Stack (top -> bottom):";
        for (int i = top; i >= 0; i--) cout << " " << data[i].id << "(" << data[i].weight << ")";
        cout << "\n";
    }
};
int main() {
    BoxStack s;
    cout << "--- Test 1: empty stack ---\n";
    s.viewTopBox();
    s.removeTopBox();
    cout << "\n--- Test 2: main sequence 40,30,50,20,35,35 ---\n";
    s.addBox({"B1", 40});                   
    s.addBox({"B2", 30});                   
    s.addBox({"B3", 50});                  
    s.addBox({"B4", 20});                   
    s.addBox({"B5", 35});                   
    s.addBox({"B6", 35});                  
    s.viewTopBox();
    cout << "\n--- Test 3: remove boxes ---\n";
    s.removeTopBox();
    s.viewTopBox();
    cout << "\n--- Test 4: single box, then heavier than all ---\n";
    while (!s.isEmpty()) s.removeTopBox();
    s.addBox({"B7", 10});
    s.addBox({"B8", 99});
    s.displayStack();
    return 0;
}
