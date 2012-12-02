#include <iostream>
#include <assert.h>

using namespace std;

struct Node {
    int val;
    struct Node *prev, *next;
};
Node *head;

void insert_before(Node *pos, int val) {
    Node *n = (Node *) malloc(sizeof(Node));
    assert(n != 0);
    n->val = val;
    n->prev = n->next = 0;
    if (pos == 0) {
        // Can we put an assertion here?
        assert(head == 0);
        head = n;
        head->next = head->prev = head;
    } else {
        assert(head != 0);
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

int main() {
    insert_before(0, 1);
    insert_before(head, 2);
    insert_before(head->next, 3);
    print(head);
}
// Note that this code is not very robust,
// and I think it has some bugs in it.
