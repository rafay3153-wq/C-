#include <iostream>
#include <string>
using namespace std;
struct PageNode {
    string title, url, timeVisited;
    PageNode* next;                        
};
class BrowserHistory {
    PageNode* top;                         
 
    static void show(const PageNode* p) {
        cout << p->title << " <" << p->url << "> visited at " << p->timeVisited << "\n";
    }
public:
    BrowserHistory() : top(nullptr) {}
    BrowserHistory(const BrowserHistory&) = delete;             
    BrowserHistory& operator=(const BrowserHistory&) = delete;
    ~BrowserHistory() {
        int freed = 0;
        while (top) { PageNode* t = top; top = top->next; delete t; freed++; }
        cout << "[DESTRUCTOR] Released " << freed << " remaining node(s)\n";
    }
    void visitPage(const string& title, const string& url, const string& time) {
        top = new PageNode{title, url, time, top};  // new node points to old top
        cout << "[VISIT] "; show(top);
    }
    void goBack() {
        if (!top || !top->next) {           
            cout << "[BACK] Cannot go back - no previous page"
                 << (top ? " (only one page in history)\n" : " (history is empty)\n");
            return;
        }
        PageNode* old = top;
        top = top->next;                  
        cout << "[BACK] Left: " << old->title << " -> now on: " << top->title << "\n";
        delete old;                         
    }
    void viewCurrentPage() const {
        if (!top) { cout << "[CURRENT] History is empty - no current page\n"; return; }
        cout << "[CURRENT] "; show(top);
    }
    void displayHistory() const {
        if (!top) { cout << "[HISTORY] Empty\n"; return; }
        cout << "[HISTORY] newest -> oldest:\n";
        for (const PageNode* p = top; p; p = p->next)
            cout << (p == top ? "  * " : "    ") << p->title << " <" << p->url << "> "
                 << p->timeVisited << "\n";
    }
};
int main() {
    BrowserHistory h;
    cout << "--- Test 1: empty history ---\n";
    h.viewCurrentPage();
    h.goBack();
    h.displayHistory();
    cout << "\n--- Test 2: single page ---\n";
    h.visitPage("Google", "www.google.com", "10:00");
    h.viewCurrentPage();
    h.goBack();                            
    cout << "\n--- Test 3: several visits and goBack ---\n";
    h.visitPage("COMSATS", "www.comsats.edu.pk", "10:05");
    h.visitPage("Stack Overflow", "stackoverflow.com", "10:12");
    h.visitPage("YouTube", "www.youtube.com", "10:20");
    h.displayHistory();
    h.goBack();
    h.goBack();
    h.viewCurrentPage();
    h.visitPage("GitHub", "github.com", "10:30");
    h.displayHistory();
    h.goBack();
    h.goBack();
    h.goBack();                             
    h.viewCurrentPage();
    cout << "\n--- Test 4: leave pages in history; destructor frees them ---\n";
    h.visitPage("Wikipedia", "www.wikipedia.org", "10:40");
    return 0;
}
