#include <stdio.h>

class A
{
public:
    A(int i) : val(i) {}

    const A& operator = (const A& a)
    {
        this->val = a.val;
        return *this;
    }

    void setVal(int i) { val = i; }
    int getVal() { return val; }

private:
    int val;
};

int main() {
    A a(1), b(2) ,c(3);

    a = b = c;

    a.setVal(5);

    printf("A:%d\n", a.getVal());
    printf("B:%d\n", b.getVal());
    printf("C:%d\n", c.getVal());
}