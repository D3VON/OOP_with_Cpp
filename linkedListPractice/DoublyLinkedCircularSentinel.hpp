#ifndef DOUBLYLINKEDCIRCULARSENTINEL_HPP
#define DOUBLYLINKEDCIRCULARSENTINEL_HPP

//Head pointer, circular:
struct Link {
  Link *next, *prev;
};

struct Node {
  Link link;
  Person::Person *p;
  int value;
};

void push_front(Node *n);
void push_back(Node *n);
void insert_before(Link *pos, Node *n);
void remove_node(Node *n);


#endif