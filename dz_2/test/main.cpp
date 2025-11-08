#include <iostream>

// struct RGB{
// 	int red;
// 	int green;
// 	int blue;
// };

// int main(){
// 	// RGB a;
// 	// int r;
// 	// int g;
// 	// int b;
// 	// while (std::cin >> r >> g >> b){
// 	// 	a = {r,g,b};
// 	// 	std::cout << a.red << " " 
// 	// 	<< a.green << " " 
// 	// 	<< a.blue << " "
// 	// 	<< std::endl;
// 	// }
// 	return 0;
// }

// int main(){
// 	int a;
// 	if ((std::cin >> a)){
// 		std::cout << a;
// 	} else{
// 		std::cerr << "hi!";
// 	}
// 	return 0;
// }

// int main() {
// 	int** ar;

// 	ar = new int*[3];
// 	int* a = new int[2];
// 	int* b = new int[2];
// 	int* c = new int[2];

// 	int i = 0;
// 	for (i; i < 2; i++){
// 		a[i] = i;
// 	}
// 	for (i; i < 4; i++){
// 		b[i] = i;
// 	}
// 	for (i; i < 6; i++){
// 		c[i] = i;
// 	}
// 	ar[0] = a;
// 	ar[1] = b;
// 	ar[2] = c;

// 	delete ar;

// 	std::cout << a[1] << std::endl;

// 	return 0;
// }

class A {
protected:
	int q;
public:
	A(){
		std::cout << "q" << std::endl;
	};

	// A(int a):
	// q(a)
	// {};

	~A(){
		std::cout << q << std::endl;
	};
};

class B : public A {
	int l;
public:
	B(){
		std::cout << "l" << std::endl;
	};

	B(int a, int b):
	l(b)
	{
		q = a;
	};

	~B(){
		std::cout << l << std::endl;
	};
};

int main(){
	B h(2, 3);
	return 0;
}