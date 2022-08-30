#include<iostream>
#include <cassert>

using namespace std;

class ColumnNode {
public:
    int value;
    int column;
    ColumnNode* next{};
    ColumnNode* prev{};

    // default constructor
    ColumnNode() : next(nullptr), prev(nullptr) {}

    ColumnNode(int val, int col) {
        this->value = val;
        this->column = col;
    }
};

class ArrayLinkedList {
public:
    Node* head{};
    Node* tail{};
    int length = 0;         // total number of nodes
    int col_length {};    // total number of col elements

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

    // default constructor
    ArrayLinkedList() : head(nullptr), tail(nullptr) {}

    ArrayLinkedList(int col_length) :
            col_length(col_length) {
        // Reading: https://en.wikipedia.org/wiki/Sentinel_node
        tail = head = new Node(0, -1);
        ++length;
    }

    void set_value(int val, int col) {
        get_col(col, true)->value = val;
    }

    void print_col() {
        Node* cur = head->next;

        for (int i = 0; i < col_length; ++i) {
            if (cur && cur->col == i) {
                cout << cur->value << " ";
                cur = cur->next;
            } else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_col_nonzero() {
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
        assert(col_length == other.col_length);

        // Iterate on the other first, and add it to the current one
        for (Node* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            Node* this_idx = get_col(other_cur->col, true);  // **
            this_idx->value += other_cur->value;
        }
        // ** We can make this function more efficient, but let's keep simple
    }
};

class RowNode {
public:
    int row {};
    ArrayLinkedList list;
    RowNode* next{};
    RowNode* prev{};

    RowNode() : next(nullptr), prev(nullptr) {}

    RowNode(int row) {
        this->row = row;
    }
};

class SparceMatrix {
private:
    RowNode* head{};
    RowNode* tail{};
    ArrayLinkedList list;
    int row_length {};

    void link(RowNode* first, RowNode* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    RowNode* embed_after(RowNode* node_before, int row) {
        RowNode* middle = new RowNode(row);
        ++row_length;

        RowNode* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    RowNode* get_row(int row, bool is_create_if_missing) {
        RowNode* prev_index = head;

        while(prev_index->next && prev_index->next->row < row)
            prev_index = prev_index->next;

        bool found = prev_index->next && prev_index->next->row == row;

        if (found)
            return prev_index->next;

        if (!is_create_if_missing)
            return nullptr;

        return embed_after(prev_index, 0);
    }

public:
    SparceMatrix() : head(nullptr), tail(nullptr) {}

    SparceMatrix(int rows, int cols) {
        row_length = rows;
        list.col_length = cols;
    }

    void print_matrix() {
        for (int i = 0; i < row_length; ++i) {
            list.print_col();
            cout << endl;
        }
    }

};

int main() {
    SparceMatrix mat(10, 10);

    mat.print_matrix();

    cout << "\n\n\nNO RTE\n";

    return 0;
}