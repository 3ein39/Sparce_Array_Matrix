#include<iostream>
using namespace std;

class Node {
public:
    int value;
    int idx;
    Node* next{};
    Node* prev{};
    
    // default constructor
    Node() : next(nullptr), prev(nullptr) {}

    Node(int val, int idx) {
        this->value = val;
        this->idx = idx;
    }
};

class ArrayLinkedList {
private:
    Node* head{};
    Node* tail{};
    int length;

    void link(Node* first, Node* second) {
        first->next = second;
        second->prev = first;
    }

public:
    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}

    void Set(int val, int idx) {
        Node* item = new Node(val, idx);

        if (!length)
            head = tail = item;
        else {
            link(tail, item);
            tail = item;
        }
        ++length;
    }
};

int main() {
    ArrayLinkedList list;
    list.Set(50, 5);
    list.Set(20, 2);
    list.Set(70, 7);
    list.Set(40, 4);


    return 0;
}