#include <iostream>

using namespace std;

inline void set_val(void *addr, int val, int off) {
    *(int *) ((char *) addr + off) = val;
}

struct MyClass1 {
    char *str;
    char letter;
    int val;
};

struct MyClass2 {
    char letter;
    int val;
};

#define xyzzy_offset(o, f) ((char *) &o.f - (char *) &o)

int main () {
    struct MyClass1 obj1;
    struct MyClass2 obj2;
    obj1.val = 0;
    obj2.val = 0;
    set_val(&obj1, 1234, xyzzy_offset(obj1, val));
    set_val(&obj2, 5678, xyzzy_offset(obj2, val));
    cout << obj1.val << endl;
    cout << obj2.val << endl;
}
