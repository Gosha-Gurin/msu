#include <iostream>
// #include <vector>
#include <cmath>


struct NodeList{
	int value;
	NodeList* next;

	NodeList(int val, NodeList* ptr = nullptr):
		value(val),
		next(ptr)
	{}

	~NodeList(){
		delete next;
	}

	void AddElem(int value){
		NodeList* tmp = new NodeList(value);
		next = tmp;
	}
};





void PrintList(NodeList* Head){
	std::cout << "\n";

	NodeList* i = Head;

	while (i != nullptr){
		std::cout << i->value << " >> ";

		i = i->next;
	}



	std::cout << "NULL" << std::endl;
}


void Around(NodeList* Head, NodeList* Last){

	NodeList* tmp1 = Head->next;

	Head->next = nullptr;

	NodeList* tmp2 = nullptr;
	NodeList* tmp3 = nullptr;

	while(tmp2 != Last){
		tmp3 = tmp1->next;
		tmp1->next = tmp2;
		tmp2 = tmp1;
		tmp1 = tmp3;
	}
}


void Process(NodeList* Head){

	NodeList* Last = Head;
	NodeList* Mid = Head;

	int count = 0;

	//Находим Last, попутно считая сколько всего элеметнов в списке (надо для нахождения середины)
	while (Last->next != nullptr){
		Last = Last->next;
		count++;
	}

	for (int i = 0; i < floor(count/2); i++){
		Mid = Mid->next;
	}

	Around(Mid, Last);

	// PrintList(Last);
	// PrintList(Head);


	NodeList* tmp1 = Head;
	NodeList* tmp2 = Last;
	NodeList* tmp3;
	NodeList* tmp4;


	while (tmp2 != nullptr){
		tmp3 = tmp1->next;
		tmp4 = tmp2->next;
		tmp1->next = tmp2;
		tmp2->next = tmp3;

		tmp1 = tmp3;
		tmp2 = tmp4;
	}
}





int main(){

	int input = 0;
	std::cin >> input;
	NodeList* Head = new NodeList(input);
	NodeList* tmp1 = Head;

	while (std::cin >> input){
		NodeList* tmp2 = new NodeList(input);
		tmp1->next = tmp2;
		tmp1 = tmp2;
	}

	Process(Head);

	PrintList(Head);

	return 0;
}