#include <iostream>

using namespace std;

class IMammals
{
public:
	virtual void walk() = 0;
};

class Cats : public IMammals
{
public:
	void walk()
	{
		cout << "Cat is walking" << endl;
	}
};

class Dogs : public IMammals
{
public:
	void walk()
	{
		cout << "Dog is walking" << endl;
	}
};

int main(void)
{
	Cats aCat;
	Dogs aDog;
	IMammals *ptrMammals = NULL;

	ptrMammals = &aCat;
	ptrMammals->walk();

	ptrMammals = &aDog;
	ptrMammals->walk();

	system("pause");
	return 0;
}
