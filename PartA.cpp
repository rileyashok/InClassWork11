#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

public:
    NodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = new ListNode{id, name, head};
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) return;

        if (prev) prev->next = curr->next;
        else head = curr->next;

        delete curr;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": " << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    //RULE OF THREE:
    //Copy Constructor
    NodeList(const NodeList& other) {
         if (!other.head) {
            head = nullptr;
            count = 0;
            return;
        }

        head = new ListNode{other.head->id, other.head->name, nullptr};
        ListNode* currNew = head;
        ListNode* currOld = other.head->next;

        while (currOld) {
            currNew->next = new ListNode{currOld->id, currOld->name, nullptr};
            currNew = currNew->next;
            currOld = currOld->next;
        }

        count = other.count;;
    }

    // Assignment operator
    NodeList& operator=(const NodeList& other) {
    if (this != &other) {

        // delete current list
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }

        head = nullptr;
        count = 0;
        // deep copy from other
        ListNode* curr = other.head;
        ListNode* tail = nullptr;

        while (curr) {
            ListNode* newNode = new ListNode{curr->id, curr->name, nullptr};
            if (!head) {
                head = newNode;
                tail = newNode;
            } 
            else {
                tail->next = newNode;
                tail = newNode;
            }

            curr = curr->next;
        }
        count = other.count;
    }
    return *this;
}

    // Destructor, destroy all nodes
    ~NodeList() {
        //delete everything in the list
        ListNode* curr = head;
        while (curr) {
            removeNode(curr->id);
            curr = curr->next;
        }
        delete head; //delete the list
       
    }
};

int main() {
    NodeList* list1 = new NodeList();
    list1->addNode(1,"one");
    list1->addNode(2,"two");
    list1->addNode(3,"three");
    list1->addNode(4,"four)");
    list1->addNode(5,"five)");
    list1->display();
    list1->removeNode(1);
    list1->removeNode(2);
    list1->removeNode(3);
    list1->removeNode(4);
    list1->removeNode(5);
    list1->display();
    delete list1;
    return 0;
}
