#include <iostream>
#include <string>
using namespace std;
 
struct Tab {
    int    id;
    string title;
    string url;
    Tab*   prev;
    Tab*   next;
    Tab(int i, const string& t, const string& u)
        : id(i), title(t), url(u), prev(nullptr), next(nullptr) {}
};
 
class TabManager {
private:
    Tab* head;       
    Tab* tail;       
    Tab* active;     
 
    Tab* findTab(int id) const {
        for (Tab* cur = head; cur != nullptr; cur = cur->next)
            if (cur->id == id) return cur;
        return nullptr;
    }
 
public:
    TabManager() : head(nullptr), tail(nullptr), active(nullptr) {}
    ~TabManager() {
        while (head != nullptr) {
            Tab* t = head;
            head = head->next;
            delete t;
        }
    }
 
    bool openTab(int id, const string& title, const string& url) {
        if (findTab(id) != nullptr) {
            cout << "  [Error] Tab ID " << id << " already exists.\n";
            return false;
        }
        Tab* t = new Tab(id, title, url);
        if (head == nullptr) {
            head = tail = t;
        } else {
            t->prev    = tail;
            tail->next = t;
            tail       = t;
        }
        active = t;
        return true;
    }

    bool closeTabByID(int id) {
        Tab* t = findTab(id);
        if (t == nullptr) {
            cout << "  [Error] Tab ID " << id << " not found. Nothing closed.\n";
            return false;
        }
        if (t->prev != nullptr) t->prev->next = t->next;   
        else                    head = t->next;
        if (t->next != nullptr) t->next->prev = t->prev;   
        else                    tail = t->prev;
 
        if (active == t)                                   
            active = (t->next != nullptr) ? t->next : t->prev;
        cout << "  Closed tab " << t->id << " (" << t->title << ")\n";
        delete t;
        return true;
    }
 
    bool switchTab(int id) {
        Tab* t = findTab(id);
        if (t == nullptr) {
            cout << "  [Error] Tab ID " << id << " not found. Active tab unchanged.\n";
            return false;
        }
        active = t;
        cout << "  Switched to tab " << t->id << " (" << t->title << ")\n";
        return true;
    }

    void displayTabsForward() const {
        cout << "  Forward : ";
        if (head == nullptr) { cout << "(no open tabs)\n"; return; }
        for (Tab* cur = head; cur != nullptr; cur = cur->next) print(cur);
        cout << "\n";
    }
 
    void displayTabsReverse() const {
        cout << "  Reverse : ";
        if (tail == nullptr) { cout << "(no open tabs)\n"; return; }
        for (Tab* cur = tail; cur != nullptr; cur = cur->prev) print(cur);
        cout << "\n";
    }
 
    void showActive() const {
        if (active == nullptr) cout << "  Active tab: (none)\n";
        else cout << "  Active tab: " << active->id << " | " << active->title
                  << " | " << active->url << "\n";
    }
 
private:
    void print(Tab* t) const {
        cout << (t == active ? "*" : "") << "[" << t->id << ": " << t->title << "] ";
    }
};
 
int main() {
    TabManager tm;
 
    cout << "===== TEST 1: Empty tab list =====\n";
    tm.displayTabsForward();
    tm.displayTabsReverse();
    tm.showActive();
    tm.closeTabByID(1);
    tm.switchTab(1);
 
    cout << "\n===== TEST 2: Open tabs =====\n";
    tm.openTab(1, "Google",   "https://google.com");
    tm.openTab(2, "YouTube",  "https://youtube.com");
    tm.openTab(3, "GitHub",   "https://github.com");
    tm.openTab(4, "Wikipedia","https://wikipedia.org");
    tm.displayTabsForward();
    tm.displayTabsReverse();
    tm.showActive();
    tm.openTab(3, "Duplicate", "https://dup.com");
 
    cout << "\n===== TEST 3: Switch tab =====\n";
    tm.switchTab(2);
    tm.showActive();
    tm.displayTabsForward();
    tm.switchTab(99);
    tm.showActive();
 
    cout << "\n===== TEST 4: Close middle tab (active tab 2 is closed) =====\n";
    tm.closeTabByID(2);
    tm.displayTabsForward();
    tm.displayTabsReverse();
    tm.showActive();
 
    cout << "\n===== TEST 5: Close first tab =====\n";
    tm.closeTabByID(1);
    tm.displayTabsForward();
    tm.displayTabsReverse();
 
    cout << "\n===== TEST 6: Close last tab =====\n";
    tm.openTab(5, "Stack Overflow", "https://stackoverflow.com");
    tm.displayTabsForward();
    tm.closeTabByID(5);
    tm.displayTabsForward();
    tm.displayTabsReverse();
    tm.showActive();
 
    cout << "\n===== TEST 7: Non-existing tab, single tab, then empty =====\n";
    tm.closeTabByID(42);
    tm.closeTabByID(3);                      
    tm.displayTabsForward();
    tm.displayTabsReverse();
    tm.closeTabByID(4);                       
    tm.displayTabsForward();
    tm.showActive();
    tm.openTab(6, "New Tab", "about:blank");  
    tm.displayTabsForward();
    return 0;
}