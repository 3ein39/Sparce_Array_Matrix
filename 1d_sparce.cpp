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
    int length = 0;         // total number of nodes
    int array_length {};    // total number of array elements

    void link(Node* first, Node* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

public:
    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}

    ArrayLinkedList(int length) {
        for (int i = 0; i < length; ++i)
            set_value(0, i);
    }

    void set_value(int val, int idx) {
        Node* item = new Node(val, idx);

        Node* p = head;
        if (!length) {
            head = tail = item;
            ++length;
            return;
        }
        while (p) {
            if (p->idx == item->idx) {
                p->value = item->value;
                break;
            }
            else if (p->idx > item->idx){
                // here we have three cases
                // head, tail or in-between
                if (p == head){
                    link(item, head);
                    head = item;
                } else if (p == tail) {
                    link(tail, item);
                    tail = item;
                } else {
                    link(p->prev, item);
                    link(item, p);
                }
                ++length;

                break;
            }
            else if (!p->next) {
                link(tail, item);
                tail = item;
                ++length;
                break;
            }
            p = p->next;
        }
    }

    void print_array() {
        Node* p = head;

        while (p)
            cout << p->value << " ", p = p->next;
        cout << endl;
    }

    void print_array_nonzero() {
        Node* p = head;

        while (p) {
            if (p->value != 0)
                cout << p->value << " ";
            p = p->next;
        }
        cout << endl;
    }

    const int& get_value(int _idx) {
        // assuming that given idx is in range
        Node* p = head;

        while(p) {
            if (p->idx == _idx)
                return p->value;
            p = p->next;
        }
        return 0;
    }

    void add(const ArrayLinkedList& other) {
        Node* first = this->head;
        Node* second = other.head;

        while (second && first) {
            first->value += second->value;

            first = first->next, second = second->next;
        }
    }
};

int main() {
    ArrayLinkedList list(10);
    list.set_value(50, 5);
    list.set_value(10, 1);
    list.set_value(60, 6);
    list.set_value(20, 2);

    ArrayLinkedList list2(10);
    list2.set_value(5, 5);
    list2.set_value(99, 0);

    list.add(list2);

    list.print_array();
    list.print_array_nonzero();

    return 0;
}