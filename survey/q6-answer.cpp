#include <iostream>
#include <assert.h>

using namespace std;

struct Node {
    int val;
    struct Node *prev, *next;
};
Node *head;

inline void insert_before(Node *pos, int val) {
    Node *n = new Node;
    n->val = val;
    n->prev = n->next = 0;
    if (pos == 0) {
        // Can we put an assertion here?
        head = n;
        head->next = head->prev = head;
    } else {
        // Can we put an assertion here?
        n->next = pos;
        n->prev = pos->prev;
        pos->prev->next = n;
        pos->prev = n;
    }
}

void print(Node *list) {
    if (list != 0) {
        cout << list->val << endl;
        for (Node *n = list->next; n != list; n = n->next) {
            cout << n->val << endl;
        }
    }
}

inline int nxt_idx(int i) {
    return (i + 1)%1000000;
}
inline int prev_idx(int i) {
    // Can't subtract one.
    return (i + 999999)%1000000;
}

int main() {
    Node *nodes = malloc(1000000*sizeof(Node));
    for (int i = 0; i < 1000000; i++) {
        nodes[i].val = i + 1;
        nodes[i].next = &nodes[nxt_idx(i)];
        nodes[i].prev = &nodes[prev_idx(i)];
    }
    print(head);
}
