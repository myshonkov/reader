#include <iostream>
#include <memory>

/*
class deleter
{
	operator()(int i) {

	}
};
*/

void deleter(int* i) {
	std::cout << "This is the function deliter " << std::endl;
	delete i;
}

class foo
{
public:
	int a;



	foo() {
		std::cout << "Create object foo" << std::endl;
		aaa = &a;
		a = 5;
	}
	foo(int i) {
		std::cout << "Create object foo(int i)" << std::endl;
		//std::unique_ptr<int, decltype(&deleter)>aaa(new int(5), deleter);
	}
	~foo() {
		std::cout << "Destructor object foo" << std::endl;
		//delete aaa;// вместо этого удаления нужно использовать умный указатель
	}
	void fooPrint() {
		//std::unique_ptr<int, decltype(&deleter)>aaa(new int(7), deleter);
		std::cout << "This is the function fooPrint: " << *aaa << std::endl;
	}
	
private:
	int* aaa;
	//std::unique_ptr<int, decltype(&deleter)>aaa;
};


/* ******************************************************************************* */

int main()
{
	std::cout << "Start" << std::endl;
	foo fff;
	fff.fooPrint();
	foo ffff(6);
	ffff.fooPrint();
}