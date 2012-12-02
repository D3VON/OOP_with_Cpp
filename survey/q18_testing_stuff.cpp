#include <string.h>
#include <stdio.h>

class String {

	public:
		String(const char *s)
		{
			buf = new char[strlen(s) + 1];
			strcpy(buf,s);
		}
		~String()
		{
			delete []buf;
		}

		char *getString(){
			return buf;
		}


	private:
		char *buf;

};

int main(int argc, char *argv[])
{
	String s1("hello");
	printf("%s\n", s1.getString());
	
	String s2 = s1;
	printf("%s\n", s2.getString());


	return 0;
}
