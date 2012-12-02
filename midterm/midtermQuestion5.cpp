#include <stdio.h>
#include <typeinfo>


class Base {
	public:
		Base(){}
};

class Action
{
	public:
		void apply(Base *);
};

class Registry {
	public:
		void registr(const type_info &, Action *);
	  void apply(Base *);
	private:
		//...
};

class MyClass1 : public Base {

};

class Action1 : public Action {
	public:
		void apply(Base *);
};

Registry registry; // a singleton obj.

int main(int argc, char *argv[])
{
	MyClass1 obj;
	static Action1 act;
	registry.registr(/*  stuff here  */, &act);
	registry.apply(&obj); // calls Action1::apply(&obj)
	
	return 0;
}
