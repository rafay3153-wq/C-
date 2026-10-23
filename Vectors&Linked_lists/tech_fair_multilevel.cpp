#include <iostream>
#include <string>
using namespace std;
 
struct DemoSlot {
    int       demoId;
    string    startupName;
    string    startTime;
    DemoSlot* nextDemo;
    DemoSlot(int id, const string& name, const string& time)
        : demoId(id), startupName(name), startTime(time), nextDemo(nullptr) {}
};
 
struct Category {
    int       categoryId;
    string    categoryName;
    DemoSlot* demoHead;        
    Category* nextCategory;   
    Category(int id, const string& name)
        : categoryId(id), categoryName(name), demoHead(nullptr), nextCategory(nullptr) {}
};
 
class TechFairSchedule {
private:
    Category* head;               
    bool demoExists(int demoId) const {
        for (Category* c = head; c != nullptr; c = c->nextCategory)
            for (DemoSlot* d = c->demoHead; d != nullptr; d = d->nextDemo)
                if (d->demoId == demoId) return true;
        return false;
    }

    Category* findOrCreateCategory(int catId, const string& catName) {
        Category* prev = nullptr;
        Category* cur  = head;
        while (cur != nullptr && cur->categoryId < catId) {
            prev = cur;
            cur  = cur->nextCategory;
        }
        if (cur != nullptr && cur->categoryId == catId) return cur;   
 
        Category* node = new Category(catId, catName);
        node->nextCategory = cur;          
        if (prev == nullptr) head = node;   
        else prev->nextCategory = node;     
        return node;
    }
 
public:
    TechFairSchedule() : head(nullptr) {}
    ~TechFairSchedule() {
        while (head != nullptr) {
            Category* c = head;
            head = head->nextCategory;
            while (c->demoHead != nullptr) {
                DemoSlot* d = c->demoHead;
                c->demoHead = d->nextDemo;
                delete d;
            }
            delete c;
        }
    }
 
    bool insertByCategoryAndDemoID(int catId, const string& catName,
                                   int demoId, const string& startup, const string& time) {
        if (demoExists(demoId)) {
            cout << "  [Error] Demo ID " << demoId << " already exists. Not inserted.\n";
            return false;
        }
        Category* cat = findOrCreateCategory(catId, catName);
 
        DemoSlot* prev = nullptr;
        DemoSlot* cur  = cat->demoHead;
        while (cur != nullptr && cur->demoId < demoId) {
            prev = cur;
            cur  = cur->nextDemo;
        }
        DemoSlot* slot = new DemoSlot(demoId, startup, time);
        slot->nextDemo = cur;
        if (prev == nullptr) cat->demoHead = slot;   
        else prev->nextDemo = slot;                  
        cout << "  Inserted demo " << demoId << " (" << startup << ") into category "
             << cat->categoryId << " [" << cat->categoryName << "]\n";
        return true;
    }
 
    bool deleteByDemoID(int demoId) {
        for (Category* c = head; c != nullptr; c = c->nextCategory) {
            DemoSlot* prev = nullptr;
            DemoSlot* cur  = c->demoHead;
            while (cur != nullptr && cur->demoId != demoId) {
                prev = cur;
                cur  = cur->nextDemo;
            }
            if (cur != nullptr) {                      
                if (prev == nullptr) c->demoHead = cur->nextDemo;   
                else prev->nextDemo = cur->nextDemo;                
                cout << "  Deleted demo " << demoId << " (" << cur->startupName                << ") from category " << c->categoryId << "\n";
                delete cur;
                return true;                  
            }
        }
        cout << "  [Error] Demo ID " << demoId << " not found. Nothing deleted.\n";
        return false;
    }
 
    void displaySchedule() const {
        cout << "  ---------------- TECH FAIR SCHEDULE ----------------\n";
        if (head == nullptr) { cout << "  (no categories)\n"; return; }
        for (Category* c = head; c != nullptr; c = c->nextCategory) {
            cout << "  Category " << c->categoryId << ": " << c->categoryName << "\n";
            if (c->demoHead == nullptr) cout << "      (no demo slots)\n";
            for (DemoSlot* d = c->demoHead; d != nullptr; d = d->nextDemo)
                cout << "      Demo " << d->demoId << " | " << d->startupName
                     << " | " << d->startTime << "\n";
        }
        cout << "  ----------------------------------------------------\n";
    }
};
 
int main() {
    TechFairSchedule fair;
 
    cout << "===== TEST 1: Inserts (new categories at beginning / middle / end) =====\n";
    fair.insertByCategoryAndDemoID(3, "Robotics",    301, "RoboWorks",   "11:00");
    fair.insertByCategoryAndDemoID(1, "AI & ML",     105, "NeuroNest",   "10:30");
    fair.insertByCategoryAndDemoID(5, "Green Tech",  501, "SolarSpark",  "14:00");
    fair.insertByCategoryAndDemoID(2, "FinTech",     201, "PayPulse",    "12:00");   
    fair.insertByCategoryAndDemoID(0, "Opening",     1, "Welcome Talk", "09:00");  
    fair.displaySchedule();
 
    cout << "\n===== TEST 2: Demo inserts inside a category (beginning/middle/end) =====\n";
    fair.insertByCategoryAndDemoID(1, "AI & ML", 101, "DataDawn",   "10:00");  
    fair.insertByCategoryAndDemoID(1, "AI & ML", 110, "VisionX",    "11:30");  
    fair.insertByCategoryAndDemoID(1, "AI & ML", 103, "ChatCraft",  "10:15");  
    fair.displaySchedule();
 
    cout << "\n===== TEST 3: Duplicate DemoID =====\n";
    fair.insertByCategoryAndDemoID(2, "FinTech", 105, "CopyCat", "13:00");
 
    cout << "\n===== TEST 4: Deletions (first / middle / last of a demo list) =====\n";
    fair.deleteByDemoID(101);   
    fair.deleteByDemoID(105);   
    fair.deleteByDemoID(110);  
    fair.displaySchedule();
 
    cout << "\n===== TEST 5: Delete last demo -> category stays, empty =====\n";
    fair.deleteByDemoID(201);
    fair.displaySchedule();
 
    cout << "\n===== TEST 6: Delete non-existing DemoID =====\n";
    fair.deleteByDemoID(999);
 
    cout << "\n===== TEST 7: Re-use the emptied category =====\n";
    fair.insertByCategoryAndDemoID(2, "FinTech", 202, "CoinCove", "12:30");
    fair.displaySchedule();
 
    cout << "\n===== TEST 8: Empty schedule =====\n";
    TechFairSchedule emptyFair;
    emptyFair.displaySchedule();
    emptyFair.deleteByDemoID(1);
    return 0;
}