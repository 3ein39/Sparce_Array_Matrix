#include<iostream>
using namespace std;

class Node {
private:
    int value;
    int idx;
    Node* next{};
    Node* prev{};
public:
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

public:
    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}
};

int main() {



    return 0;
}