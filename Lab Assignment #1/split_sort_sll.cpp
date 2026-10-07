#include <iostream>
#include <string>
using namespace std;
 
struct Node {
    int   marks;
    Node* next;
    Node(int m) : marks(m), next(nullptr) {}
};
 
void appendNode(Node*& head, int marks) {
    Node* n = new Node(marks);
    if (head == nullptr) { head = n; return; }
    Node* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = n;
}
 
Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
 
void splitList(Node* head, Node*& first, Node*& second) {
    first  = head;
    second = nullptr;
    Node* mid = findMiddle(head);
    if (mid == nullptr) return;      
    mid->next = nullptr;              
}
 
Node* sortDescending(Node* head) {
    Node* sorted = nullptr;          
    while (head != nullptr) {
        Node* cur = head;            
        head = head->next;
        if (sorted == nullptr || cur->marks > sorted->marks) {
            cur->next = sorted;      
            sorted = cur;
        } else {
            Node* p = sorted;
            while (p->next != nullptr && p->next->marks >= cur->marks)
                p = p->next;
            cur->next = p->next;     
            p->next = cur;
        }
    }
    return sorted;
}
 
void displayList(const string& label, Node* head) {
    cout << label << ": ";
    if (head == nullptr) { cout << "(empty)\n"; return; }
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        cout << cur->marks;
        if (cur->next != nullptr) cout << " -> ";
    }
    cout << " -> NULL\n";
}
 
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
 
void runTest(const string& title, const int* data, int n) {
    cout << "----- " << title << " -----\n";
    Node* head = nullptr;
    for (int i = 0; i < n; i++) appendNode(head, data[i]);
    displayList("Original ", head);
 
    Node *list1 = nullptr, *list2 = nullptr;
    splitList(head, list1, list2);
    head = nullptr;                   
    displayList("List 1 after split", list1);
    displayList("List 2 after split", list2);
 
    list1 = sortDescending(list1);
    list2 = sortDescending(list2);
    displayList("List 1 sorted     ", list1);
    displayList("List 2 sorted     ", list2);
 
    freeList(list1);
    freeList(list2);
    cout << "\n";
}
 
int main() {
    int t1[] = {47, 33, 12, 89, 21, 50, 65, 30};
    runTest("TEST 1: Example from the assignment", t1, 8);
 
    int t2[] = {10, 20};
    runTest("TEST 2: Two nodes only", t2, 2);
 
    runTest("TEST 3: Empty list", nullptr, 0);
 
    int t4[] = {50, 50, 70, 70, 10, 10}; runTest("TEST 4: Duplicate marks", t4, 6);
 
    int t5[] = {1, 2, 3, 4, 5, 6};
    runTest("TEST 5: Ascending input", t5, 6);
 
    int t6[] = {99, 88, 77, 66};
    runTest("TEST 6: Already descending", t6, 4);
 
    int t7[] = {5, 1, 9};
    runTest("TEST 7: Odd count (outside assumption; 1st half gets extra node)", t7, 3);
    return 0;
}