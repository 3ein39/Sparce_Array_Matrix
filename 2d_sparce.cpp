#include<iostream>
#include <cassert>

using namespace std;

class Node {
public:
    int value;
    int col;
    Node* next{};
    Node* prev{};

    // default constructor
    Node() : next(nullptr), prev(nullptr) {}

    Node(int val, int col) {
        this->value = val;
        this->col = col;
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

    Node* embed_after(Node* node_before, int value, int idx) {
        Node* middle = new Node(value, idx);
        ++length;

        Node* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    Node* get_col(int col, bool is_create_if_missing) {
        Node* prev_index = head;

        while(prev_index->next && prev_index->next->col < col)
            prev_index = prev_index->next;

        bool found = prev_index->next && prev_index->next->col == col;

        if (found)
            return prev_index->next;

        if (!is_create_if_missing)
            return nullptr;

        return embed_after(prev_index, 0, col);
    }
public:
    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}

    ArrayLinkedList(int array_length) :
            array_length(array_length) {
        // Reading: https://en.wikipedia.org/wiki/Sentinel_node
        tail = head = new Node(0, -1);
        ++length;
    }

    void set_value(int val, int col) {
        get_col(col, true)->value = val;
    }

    void print_array() {
        Node* cur = head->next;

        for (int i = 0; i < array_length; ++i) {
            if (cur && cur->col == i) {
                cout << cur->value << " ";
                cur = cur->next;
            } else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_array_nonzero() {
        for (Node* cur = head->next; cur; cur = cur->next)
            cout << cur->value << " ";
        cout << "\n";
    }

    const int& get_value(int _idx) {
        Node* node = get_col(_idx, false);
        if (!node)
            return 0;
        return node->value;
    }

    void add(ArrayLinkedList &other) {
        assert(array_length == other.array_length);

        // Iterate on the other first, and add it to the current one
        for (Node* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            Node* this_idx = get_col(other_cur->col, true);  // **
            this_idx->value += other_cur->value;
        }
        // ** We can make this function more efficient, but let's keep simple
    }
};

class RowNode {
    int row {};
    ArrayLinkedList list;
    RowNode* next{};
    RowNode* prev{};

    RowNode() : next(nullptr), prev(nullptr) {}

    RowNode(int row, ArrayLinkedList list) {
        this->row = row;
        this->list = list;
    }
};

int main() {

    cout << "\n\n\nNO RTE\n";

    return 0;
}