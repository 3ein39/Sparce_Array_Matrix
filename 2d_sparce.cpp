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

class ColumnLinkedList {
public:
    ColumnNode* head{};
    ColumnNode* tail{};
    int length = 0;         // total number of nodes
    int cols {};    // total number of col elements

    void link(ColumnNode* first, ColumnNode* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    ColumnNode* embed_after(ColumnNode* node_before, int value, int col) {
        ColumnNode* middle = new ColumnNode(value, col);
        ++length;

        ColumnNode* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    ColumnNode* get_col(int col, bool is_create_if_missing) {
        ColumnNode* prev_col = head;

        while(prev_col->next && prev_col->next->column < col)
            prev_col = prev_col->next;

        bool found = prev_col->next && prev_col->next->column == col;

        if (found)
            return prev_col->next;

        if (!is_create_if_missing)
            return nullptr;

        return embed_after(prev_col, 0, col);
    }

    // default constructor
    ColumnLinkedList() : head(nullptr), tail(nullptr) {}

    ColumnLinkedList(int col_length) :
            cols(col_length) {
        // Reading: https://en.wikipedia.org/wiki/Sentinel_node
        tail = head = new ColumnNode(0, -1);
        ++length;
    }

    void set_value(int val, int col) {
        get_col(col, true)->value = val;
    }

    void print_row() {
        ColumnNode* cur = head->next;

        for (int i = 0; i < cols; ++i) {
            if (cur && cur->column == i) {
                cout << cur->value << " ";
                cur = cur->next;
            } else
                cout << "0 ";
        }
        cout << "\n";
    }

    void print_row_nonzero() {
        for (ColumnNode* cur = head->next; cur; cur = cur->next)
            cout << cur->value << " ";
        cout << "\n";
    }

    const int& get_value(int col) {
        ColumnNode* node = get_col(col, false);
        if (!node)
            return 0;
        return node->value;
    }

    void add(ColumnLinkedList &other) {
        assert(cols == other.cols);

        // Iterate on the other first, and add it to the current one
        for (ColumnNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            ColumnNode* this_idx = get_col(other_cur->column, true);  // **
            this_idx->value += other_cur->value;
        }
        // ** We can make this function more efficient, but let's keep simple
    }
};

class RowNode {
public:
    int row {};
    ColumnLinkedList col_list;

    RowNode* next{};
    RowNode* prev{};

    RowNode() : next(nullptr), prev(nullptr) {}

    RowNode(int row, int cols) : row(row), col_list(cols) {}
};

class SparseMatrix {
private:
    RowNode* head{};
    RowNode* tail{};
    int length {};
    int rows {};
    int cols {};

    void link(RowNode* first, RowNode* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    RowNode* embed_after(RowNode* node_before, int row) {
        RowNode* middle = new RowNode(row, cols);
        ++length;

        RowNode* node_after = node_before->next;
        link(node_before, middle);

        if (!node_after)
            tail = middle;
        else
            link(middle, node_after);

        return middle;
    }

    RowNode* get_row(int row, bool is_create_if_missing) {
        // similar logic to insert sorted
        RowNode* prev_row = head;

        while(prev_row->next && prev_row->next->row < row)
            prev_row = prev_row->next;

        bool found = prev_row->next && prev_row->next->row == row;

        if (found)
            return prev_row->next;

        if (!is_create_if_missing)
            return nullptr;

        return embed_after(prev_row, row);
    }

public:
    SparseMatrix() : head(nullptr), tail(nullptr) {}

    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {
        // Dummy node of row = -1, to make coding shorter!
        tail = head = new RowNode(-1, cols);
        ++length;
    }

    void set_value(int value, int row, int col) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);

        RowNode* node = get_row(row, true);
        node->col_list.set_value(value, col);
    }

    int get_value(int row, int col) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);

        RowNode* node = get_row(row, false);
        if (!node)		// no such row
            return 0;
        return node->col_list.get_value(col);
    }

    void print_matrix() {
        cout << "\nPrint Matrix: " << rows << " x " << cols << "\n";
        RowNode* cur = head->next;
        for (int r = 0; r < rows; ++r) {
            if (cur && cur->row == r) {
                cur->col_list.print_row();
                cur = cur->next;
            } else {
                for (int j = 0; j < cols; ++j)
                    cout << "0 ";
                cout << "\n";
            }
        }
    }

    void print_matrix_nonzero() {
        cout << "\nPrint Matrix: " << rows << " x " << cols << "\n";
        for (RowNode* cur = head->next; cur; cur = cur->next)
            cur->col_list.print_row_nonzero();
    }

    void add(SparseMatrix &other) {
        assert(rows == other.rows && cols == other.cols);
        // Iterate on the other first, and add it to the current one
        for (RowNode* other_cur = other.head->next; other_cur; other_cur = other_cur->next) {
            RowNode* this_row = get_row(other_cur->row, true);  // **
            this_row->col_list.add(other_cur->col_list);
        }
        // ** We can make this function more efficient, but let's keep simple
    }
};


void test_sparse() {
    SparseMatrix mat(10, 10);
    mat.set_value(5, 3, 5);
    mat.set_value(7, 3, 7);
    mat.set_value(2, 3, 2);
    mat.set_value(0, 3, 2);
    mat.set_value(6, 5, 6);
    mat.set_value(4, 5, 4);
    mat.set_value(3, 7, 3);
    mat.set_value(1, 7, 1);
    //mat.set_value(1, 70, 1);
    mat.print_matrix();
    mat.print_matrix_nonzero();

    SparseMatrix mat2(10, 10);
    mat2.set_value(5, 1, 9);
    mat2.set_value(6, 3, 8);
    mat2.set_value(9, 9, 9);
    mat.add(mat2);
    mat.print_matrix_nonzero();
}

int main() {
    test_sparse();

    cout << "\n\n\nNO RTE\n";

    return 0;
}