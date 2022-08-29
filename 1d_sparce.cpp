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

    void set_value(int val, int idx) {
        Node* item = new Node(val, idx);

        if (!length) {
            head = tail = item;
            ++length;
        }
        else {
            Node* p = head;
            while (p) {
                if (p->idx == item->idx)
                    p->value = item->value;
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
    }

    void print_array() {
        Node* p = head;

        int idx_to_print {0};
        while (p) {
            while (idx_to_print < p->idx)
                cout << 0 << " ", ++idx_to_print;
            cout << p->value << " ";

            ++idx_to_print;
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    ArrayLinkedList list;
    list.set_value(50, 5);
    list.set_value(10, 1);
    list.set_value(60, 6);
    list.set_value(20, 2);

    list.print_array();

    return 0;
}