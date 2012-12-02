//LinkedListDeeperObfuscation


//Indirection
//Consider using a pointer to the pointer in the parent to the node, rather than //a pointer to the parent.
//Initialization would then be like:
struct Node {
  Node **ptr_ptr_parent;
  Node *right_child, *left_child;
  //...
};
void add_right_child(Node *parent) {
  Node *child = malloc(...);
  parent->right_child = child;
  child->ptr_ptr_parent  = &parent->right_child;
  //...
}
//Can simplify. For example, to delete a node that has no children:
*n->ptr_ptr_parent = 0;
//To delete a node that has a right child only:
*n->ptr_ptr_parent = n->right;
//Works even for the root node:
root = (Node *) malloc(sizeof(Node));
root->ptr_ptr_parent = &root;
//...
*n->ptr_ptr_parent = 0; // Changes root variable if this is root node.

//Here’s another example where indirection can simplify code:
insert(Node **ppn, int value) {
  if (*ppn == 0) {
    *ppn = new Node(ppn, value);
  } else {
    if (value < (*ppn)->value) {
      insert(&(*ppn)->left, v);
    } else if ((*ppn)->value < value) {
      insert(&(*ppn)->right, v)
    } else {
      // Duplicate.
    }
  }
}
//...
// No need to check for empty container.
root = 0; // Start with empty tree.
insert(&root, v);



//Basic, singly linked list.
struct Node {
  int value;
  Node *next;
};
Node *head;

void push_front(Node *n) {
  n->next = head;
  head = n;
}
void push_back1(Node *n) {
  if (head == 0) {
    head = n;
  } else {
    Node *end = head;
    while (end->next != 0) {
      end = end->next;
    }
    end->next = n;
  }
  n->next = 0;
}


void push_back2(Node *n) {
  Node **tp = &head;
  while (*tp != 0) {
    tp = &(*tp)->next;
  }
  *tp = n;
  n->next = 0;
}
//Note that the second version might be harder to understand for some programmers, so it’s a balancing act.

//Let’s add a tail pointer to improve the efficiency of appending.
struct Node {
  int value;
  Node *next;
};
Node *head, *tail;

void push_front(Node *n) {
  n->next = head;
  head = n;
  if (tail == 0) { tail = n; } 
}
void push_back(Node *n) {
  n->next = 0;
  if (tail == 0) {
    head = tail = n;
  } else {
    tail->next = n;
    tail = n;
  }
}

//We can simplify the push_back() function somewhat.
struct Node {
  int value;
  Node *next;
};
Node *head, **tail_pp = &head;

void push_front(Node *n) {
  n->next = head;
  if (head == 0) {
    tail_pp = &n->next;
  }
  head = n;
}
void push_back(Node *n) {
  n->next = 0;
  *tail_pp = n;
  tail_pp = &n->next;
  if (head == 0) {
    head = n;
  } 
}

//How would these be written?
struct Node {
  int value;
  Node *next;
};
Node *head;

void remove_node(Node *n) {
  //...
}

void insert_before(int v, Node *position) {
  //...
}

//Doubly-Linked Lists

Head and tail pointer, not circular:
struct Node {
  int value;
  Node *next, *prev;
};
Node *head, *tail;

void push_front(Node *n) {
  n->next = head;
  n->prev = 0;
  head = next;
  if (tail == 0) {
    tail = n;
  }
}
void push_back(Node *n) {
  n->prev = tail;
  n->next = 0;
  tail = n;
  if (head == 0) {
    head = n;
  }
}

//Iteration through the list can be bi-directional.
struct Node {
  int value;
  Node *next, *prev;
};
Node *head, *tail;

void forwards() {
  for (Node *n = head; n != 0; n = n->next) {
    // Do something with node.
  }
}
void backwards() {
  for (Node *n = tail; n != 0; n = n->prev) {
    // Do something with node.
  }
}

//Removing a given node and inserting at a given position:
struct Node {
  int value;
  Node *next, *prev;
};
Node *head, *tail;

void remove_node(Node *n) {
  if (head == tail = n) {
    head = tail = 0;
  } else if (head == n) {
    head = head->next;
    head->prev = 0;
  } else if (tail == n) {
    tail = tail->prev;
    tail->next = 0;
  } else {
    n->next->prev = n->prev;
    n->prev->next = n->next;
  }
}
void insert_before(Node *pos, Node *n) {
  if (pos == head) {
    n->next = pos;
    pos->prev = n;
    n->prev = 0;
    head = n;
  } else {
    n->next = pos;
    n->prev = pos->prev;
    pos->prev->next = n;
    pos->prev = n;
  }
}

//Doubly-Linked, Circular Lists

//Head pointer, circular:
struct Node {
  int value;
  Node *next, *prev;
};
Node *head;

void push_front(Node *n) {
  if (head == 0) {
    n->next = n->prev = n;
  } else {
    insert_before(head->next, n);
  }
  head = n; 
}
void push_back(Node *n) {
 if (head == 0) {
    n->next = n->prev = n;
  } else {
    insert_before(head, n);
  }
  head = n;
}

//Removing a given node and inserting at a given position:
struct Node {
  int value;
  Node *next, *prev;
};
Node *head;

void remove_node(Node *n) {
  if (n->next == n) {
    assert(head == n);
    head = 0;
  } else {
    if (head == n) {
      head = head->next;
    }
    n->next->prev = n->prev;
    n->prev->next = n->next;
  }
}
void insert_before(Node *pos, Node *n) {
  if (pos == 0) {
    head = n;
    n->next = n->prev = n;
  } else {
    if (pos == head) {
       head = n;
    }
    n->next = pos;
    n->prev = pos->prev;
    pos->prev->next = n;
    pos->prev = n;
  }
}

//Iteration: (Interactive)
struct Node {
  int value;
  Node *next, *prev;
};
Node *head;

void forwards() {
  if (head != 0) {
    for (Node *n = head; n->next != head; n = n->next) {
      // Do something with node.
    }
    // Do something with last node: head->prev.
  }
}
void backwards() {
  if (head != 0) {
    for (Node *n = head->prev; n != head; n = n->prev) {
      // Do something with n.
    }
    // Do something with last node: head.
  }
}

//Doubly-Linked, Circular Lists with Sentinel

//Head pointer, circular:
struct Link {
  Link *next, *prev;
};
struct Node {
  Link link;
  int value;
}
Link head = {&head, &head};

void push_front(Node *n) {
  insert_before(head.next, n);
}
void push_back(Node *n) {
  insert_before(&head, n);
}
void insert_before(Node *pos, Node *n) {
  n->next = pos;
  n->prev = pos->prev;
  pos->prev->next = n;
  pos->prev = n;
}
void remove_node(Node *n) {
  n->next->prev = n->prev;
  n->prev->next = n->next;
}

//Iteration:
// Forwards
for (Link *l = head.next; l != &head; l = l->next) {
  // Do something with (Node *) l.
}
// Backwards
for (Link *l = head.prev; l != &head; l = l->prev) {
  // Do something with (Node *) l.
}

//With These...
//Increment becomes:
inc(Iterator *it) {
  it->node = it->node.link->next;
}
//End becomes:
Iterator end() {
  it.node = &head;
  return it;
}
//Begin becomes:
Iterator begin() {
  it.node = head.next;
  return it;
}

// aka dereferencing?
//Deleting nodes becomes:
n.link->prev->next = n.link->next;
n.link->next->prev = n.link->prev;

