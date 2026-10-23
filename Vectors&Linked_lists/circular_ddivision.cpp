#include <iostream>
#include <string>
using namespace std;
 
struct Node {
    int   participant;
    Node* next;
    Node(int p) : participant(p), next(nullptr) {}
};
 
Node* createCircle(int n) {
    if (n <= 0) return nullptr;
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    tail->next = head;                     
    return head;
}

void printGroup(Node* head) {
    cout << "{";
    Node* cur = head;
    do {
        cout << cur->participant;
        cur = cur->next;
        if (cur != head) cout << ", ";
    } while (cur != head);
    cout << "}";
}
 
Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;
    Node* slow = head;
    Node* fast = head->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
 
void splitCircle(Node* head, Node*& firstHalf, Node*& secondHalf) {
    firstHalf  = head;
    secondHalf = nullptr;
    if (head == nullptr || head->next == head) return;   
    Node* mid  = findMiddle(head);         
    secondHalf = mid->next;                
 
    Node* tail = secondHalf;               
    while (tail->next != head) tail = tail->next;
 
    mid->next  = head;                    
    tail->next = secondHalf;               
}
 
void divideCircle(Node* head, int level = 1) {
    if (head == nullptr) return;
    string indent((level - 1) * 4, ' ');
 
    if (head->next == head) {             
        cout << indent << "Participant " << head->participant
             << " is alone -> stop dividing\n";
        delete head;                       
        return;
    }
 
    Node *firstHalf = nullptr, *secondHalf = nullptr;
    splitCircle(head, firstHalf, secondHalf);
 
    cout << indent << "Level " << level << ": ";
    printGroup(firstHalf);
    cout << " and ";
    printGroup(secondHalf);
    cout << "\n";
 
    divideCircle(firstHalf,  level + 1);
    divideCircle(secondHalf, level + 1);
}
 
int main() {
    cout << "===== TEST 1: n = 8 (assignment demonstration) =====\n";
    Node* circle = createCircle(8);
    cout << "Initial circle: ";
    printGroup(circle);
    cout << " -> back to " << circle->participant << "\n";
    cout << "Middle node (end of first half): " << findMiddle(circle)->participant << "\n\n";
    divideCircle(circle);
 
    cout << "\n===== TEST 2: single split pointer check (n = 6) =====\n";
    Node* c6 = createCircle(6);
    Node *a = nullptr, *b = nullptr;
    splitCircle(c6, a, b);
    cout << "First half : "; printGroup(a);
    cout << "  (last node's next = " << a->next->next->next->participant << " -> circular)\n";
    cout << "Second half: "; printGroup(b);
    cout << "  (last node's next = " << b->next->next->next->participant << " -> circular)\n";
    divideCircle(a);
    divideCircle(b);
 
    cout << "\n===== TEST 3: n = 1 (base case immediately) =====\n";
    divideCircle(createCircle(1));
 
    cout << "\n===== TEST 4: n = 2 =====\n";
    divideCircle(createCircle(2));
 
    cout << "\n===== TEST 5: n = 0 (empty) =====\n";
    divideCircle(createCircle(0));
    cout << "Nothing to divide.\n";
 
    cout << "\n===== TEST 6: n = 5 (odd; first half gets the extra node) =====\n";
    divideCircle(createCircle(5));
    return 0;
}