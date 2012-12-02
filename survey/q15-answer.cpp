#include <iostream>


class Base {
    public:
        virtual ~Base() {}
        virtual void print(std::ostream &os) const = 0;
};

std::ostream &
operator<<(std::ostream &os, const Base &b) {
    b.print(os);
}

class IntDerived : public Base {
    public:
        IntDerived(int v) : val(v) { }
        virtual void print(std::ostream &os) const;
    private:
        int val;
};

void
IntDerived::print(std::ostream &os) const {
    os << val;
}

class DoubleDerived : public Base {
    public:
        DoubleDerived(double v) : val(v) { }
        virtual void print(std::ostream &os) const;
    private:
        double val;
};

void
DoubleDerived::print(std::ostream &os) const {
    os << val;
}

int main() {
    
    IntDerived i(1234);
    DoubleDerived d(3.14);

    Base &b1(i), &b2(d);

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
}
