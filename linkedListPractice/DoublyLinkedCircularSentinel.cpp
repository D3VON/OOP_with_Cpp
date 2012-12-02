#include "DoublyLinkedCircularSentinel.hpp"
#include <stdio.h>
#include <stdlib.h>     /* declares malloc() */
using namespace std;
//Doubly-Linked, Circular Lists with Sentinel

Link head = {&head, &head};

void push_front(Node *n) {
  insert_before(head.next, n);
}

void push_back(Node *n) {
  insert_before(&head, n);
}

void insert_before(Link *pos, Node *n) {
  n->link.next = pos;
  n->link.prev = pos->prev;
  pos->prev->next = &(n->link);
  pos->prev = &(n->link);
}

void remove_node(Node *n) {
  n->link.next->prev = n->link.prev;
  n->link.prev->next = n->link.next;
}

struct Iterator
{
  Link *link;
};

//Increment becomes:
void inc(Iterator *it) {
  it->link = it->link->next;
}

//End becomes:
Iterator end() {
  Iterator it;
  it.link = &head;
  return it;
}

// Link head = {&head, &head};

//Begin becomes:
Iterator begin() {
  Iterator it;
  it.link = head.next;
  return it;
}


int main(int argc, char *argv[])
{
	printf("Hello, world\n");

  Node *a = (Node*)malloc(sizeof(Node*));
  a->value = 100;
  printf("list starts with: %d\n", a->value);
  insert_before(&head, a);
  printf("list starts with: %d\n", a->value);

  Node *b = (Node*)malloc(sizeof(Node*));
  b->value = 200;
  insert_before(&head, b);
  Node *c = (Node*)malloc(sizeof(Node*));
  c->value = 300;
  insert_before(&head, c);
  Node *d = (Node*)malloc(sizeof(Node*));
  d->value = 400;
  insert_before(&head, d);
  Node *e = (Node*)malloc(sizeof(Node*));
  e->value = 500;
  insert_before(&head, e);


  Iterator it = begin();


  //Traversal without iterator:
  // Forwards
  printf("--------traversing forwards ----------\n");
  for (Link *l = head.next; l != &head; l = l->next) {
    // Do something with (Link *) l.
    Node* n = (Node*)l; // superfluous; see deref on next line:
    printf(">>>>>>>>> %d\n", ((Node*)l)->value);
  }

  // Backwards
  printf("--------traversing backwards ----------\n");
  for (Link *l = head.prev; l != &head; l = l->prev) {
    // Do something with (Link *) l.
    Node* n = (Node*)l;
    printf("<<<<<<<<< %d\n", n->value);
  }

  //Traversal without iterator:
  // Forwards
  printf("--------deleting from beginning to end ----------\n");
  for (Link *l = head.next; l != &head; l = l->next) {
    // Do something with (Link *) l.
    Node* n = (Node*)l;
    n->link.prev->next = n->link.next;
    n->link.next->prev = n->link.prev;
  }

  //Traversal without iterator:
  // Forwards
  printf("--------traversing forwards ----------\n");
  for (Link *l = head.next; l != &head; l = l->next) {
    // Do something with (Link *) l.
    Node* n = (Node*)l;
    printf(">>>>>>>>> %d\n", n->value);
  }
	
	return 0;
}
