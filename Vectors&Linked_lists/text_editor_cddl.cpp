#include <iostream>
#include <string>
using namespace std;
 
struct Node {
    string word;
    Node*  next;
    Node*  prev;
    Node(const string& w) : word(w), next(nullptr), prev(nullptr) {}
};
 
class TextEditor {
private:
    Node* head;      
    Node* cursor;    
 
public:
    TextEditor() : head(nullptr), cursor(nullptr) {}
    ~TextEditor() {
        if (head == nullptr) return;
        head->prev->next = nullptr;        
        while (head != nullptr) {
            Node* t = head;
            head = head->next;
            delete t;       }
    }

     void insert(const string& word) {
        Node* n = new Node(word);
        if (head == nullptr) {             
            n->next = n->prev = n;
            head = cursor = n;
            return;
        }
        Node* tail = head->prev;
        n->prev    = tail;
        n->next    = head;
        tail->next = n;
        head->prev = n;
    }
 
    void deleteCurrent() {
        if (cursor == nullptr) { cout << "  [Error] Text is empty. Nothing to delete.\n"; return; }
        Node* victim = cursor;
        cout << "  Deleting \"" << victim->word << "\"\n";
        if (victim->next == victim) {     
            head = cursor = nullptr;
        } else {
            victim->prev->next = victim->next;
            victim->next->prev = victim->prev;
            if (victim == head) head = victim->next;
            cursor = victim->next;         
        }
        delete victim;
    }

    int findAndReplace(const string& oldWord, const string& newWord) {
        if (head == nullptr) { cout << "  [Info] Text is empty.\n"; return 0; }
        int replaced = 0;
        Node* cur = head;
        do {
            if (cur->word == oldWord) { cur->word = newWord; replaced++; }
            cur = cur->next;
        } while (cur != head);
        if (replaced == 0) cout << "  [Info] \"" << oldWord << "\" not found.\n";
        return replaced;
    }

    int count() const {
        if (head == nullptr) return 0;
        int n = 0;
        Node* cur = head;
        do { n++; cur = cur->next; } while (cur != head);
        return n;
    }

    void gotoNext() {
        if (cursor == nullptr) { cout << "  [Error] Text is empty.\n"; return; }
        cursor = cursor->next;
    }
    void gotoPrevious() {
        if (cursor == nullptr) { cout << "  [Error] Text is empty.\n"; return; }
        cursor = cursor->prev;
    }
 
    void displayForward() const {
        cout << "  Forward : ";
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* cur = head;
        do {
            printWord(cur);
            cur = cur->next;
        } while (cur != head);
        cout << "\n";  }
    void displayBackward() const {
        cout << "  Backward: ";
        if (head == nullptr) { cout << "(empty)\n"; return; }
        Node* last = head->prev;
        Node* cur  = last;
        do {
            printWord(cur);
            cur = cur->prev;
        } while (cur != last);
        cout << "\n";
    }
    void showCursor() const {
        if (cursor == nullptr) cout << "  Cursor: (none)\n";
        else cout << "  Cursor at: \"" << cursor->word << "\"\n";
    }
 
private:
    void printWord(Node* n) const {
        if (n == cursor) cout << "<" << n->word << "> ";
        else             cout << n->word << " ";
    }
};
 
int main() {
    TextEditor ed;
 
    cout << "===== TEST 1: Empty editor =====\n";
    ed.displayForward();
    ed.displayBackward();
    cout << "  count = " << ed.count() << "\n";
    ed.deleteCurrent();
    ed.gotoNext();
    ed.gotoPrevious();
    ed.findAndReplace("a", "b");
 
    cout << "\n===== TEST 2: Insert words =====\n";
    const char* words[] = {"the", "quick", "brown", "fox", "jumps"};
    for (const char* w : words) ed.insert(w);
    ed.displayForward();
    ed.displayBackward();
    cout << "  count = " << ed.count() << "\n";
    ed.showCursor();
 
    cout << "\n===== TEST 3: Cursor movement and wrap-around =====\n";
    ed.gotoNext();     ed.showCursor();
    ed.gotoNext();     ed.showCursor();
    ed.gotoPrevious(); ed.showCursor();
    ed.gotoPrevious(); ed.showCursor();
    cout << "  -- previous from FIRST word wraps to LAST --\n";
    ed.gotoPrevious(); ed.showCursor();
    cout << "  -- next from LAST word wraps to FIRST --\n";
    ed.gotoNext();     ed.showCursor();
    ed.displayForward();
 
    cout << "\n===== TEST 4: deleteCurrent (middle, first, last) =====\n";
    ed.gotoNext(); ed.gotoNext();          
    ed.deleteCurrent();                    
    ed.displayForward(); ed.displayBackward();
    ed.gotoPrevious(); ed.gotoPrevious(); 
    ed.showCursor();
    ed.deleteCurrent();                     
    ed.displayForward(); ed.displayBackward();
    ed.gotoPrevious();                    
    ed.showCursor();
    ed.deleteCurrent();                    
    ed.displayForward(); ed.displayBackward();
    cout << "  count = " << ed.count() << "\n";
 
    cout << "\n===== TEST 5: findAndReplace =====\n";
    TextEditor ed2;
    const char* w2[] = {"to", "be", "or", "not", "to", "be", "to"};
    for (const char* w : w2) ed2.insert(w);
    ed2.displayForward();
    int r = ed2.findAndReplace("to", "2");
    cout << "  replaced " << r << " occurrence(s)\n";
    ed2.displayForward();
    r = ed2.findAndReplace("xyz", "abc");
    cout << "  replaced " << r << " occurrence(s)\n";
 
    cout << "\n===== TEST 6: Single word list =====\n";
    TextEditor one;
    one.insert("hello");
    one.displayForward(); one.displayBackward();
    one.gotoNext();     one.showCursor();
    one.gotoPrevious(); one.showCursor();
    cout << "  count = " << one.count() << "\n";
    one.deleteCurrent();
    one.displayForward();
    one.showCursor();
    cout << "  count = " << one.count() << "\n";
    one.insert("again");                  
    one.displayForward();
    return 0;
}