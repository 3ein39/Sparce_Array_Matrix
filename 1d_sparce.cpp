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
};

int main() {



    return 0;
}