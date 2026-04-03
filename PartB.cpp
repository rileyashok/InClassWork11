#include <memory>
#include<iostream>
using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next; //unique pointer will automatically cleanup
    //don't have to delete later

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head)); //no need to delete later
        count++;
    }

    //Don't need a removeNode function becauseall of the nodes automatically clear themselves

    void display() const {
        SmartListNode* curr = head.get();
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null" << endl;
    }
//QUESTION ANSWERS
    //No destructor is needed because unique_ptr handles all of the cleanup
//Do not need the rule of three because the unique_ptr automatically deletes it
//Significantly decreases risk of memory bugs because unique_ptr hands it for you, all of them will be deleted and not leak memory

};

int main() {
    return 0;
}
