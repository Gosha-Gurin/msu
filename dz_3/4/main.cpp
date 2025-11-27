#include <iostream>
#include <vector>
// #include <cmath>


struct NodeList{
	int value;
	NodeList* next;
	NodeList* rand;

	NodeList(int val):
		value(val),
		next(nullptr),
		rand(nullptr)
	{}

	~NodeList(){
		delete next;
		delete rand;
	}

	// void AddElem(int value){
	// 	next = new NodeList(value);
	// }
};


void PrintList(NodeList* Head){
	NodeList* tmp = Head;

	while (tmp != nullptr){
		std::cout << tmp->value << "; Value of random ptr: ";
		if (tmp->rand == nullptr){
			std::cout << "NULL" << std::endl;
		} else {
			std::cout << tmp->rand->value << std::endl;
		}
		tmp = tmp->next;
	}
}


NodeList* ReadList(){
	std::vector<int> vec;

	int val;
	int rand;

	std::cin >> val >> rand;
	vec.push_back(rand);
	NodeList* Head = new NodeList(val);

	NodeList* tmp1 = Head;

	while (std::cin >> val >> rand){
		vec.push_back(rand);
		NodeList* tmp2 = new NodeList(val);
		tmp1->next = tmp2;
		tmp1 = tmp2;
	}

	tmp1 = Head;
	NodeList* tmp2 = Head;

	for (int i = 0; i < vec.size(); i++){
		if (vec[i] == 0){
			tmp1->rand = nullptr;
		} else {
			for (int j = 0; j < vec[i]-1; j++){
				tmp2 = tmp2->next;
			}
			tmp1->rand = tmp2;
		}
		tmp1 = tmp1->next;
		tmp2 = Head;
	}

	return Head;
}




NodeList* ListCopy(NodeList* Head){
	NodeList* CopyHead = new NodeList(Head->value);

	NodeList* tmp1 = CopyHead;
	NodeList* tmp2 = Head->next;
	NodeList* tmp3 = Head;
	NodeList* tmp4 = Head;

	while(tmp2 != nullptr){
		NodeList* tmp = new NodeList(tmp2->value);
		tmp1->next = tmp;
		tmp1 = tmp;
		tmp2 = tmp2->next;
	}

	tmp1 = CopyHead;
	tmp2 = CopyHead;
	tmp3 = Head;
	tmp4 = Head;

	// std::cout << "\n";
	// PrintList(CopyHead);
	// std::cout << "\n";
	// PrintList(Head);

	while(tmp1 != nullptr){

		if(tmp4->rand == nullptr){
			tmp1->rand = nullptr;

			tmp1 = tmp1->next;
			tmp2 = CopyHead;

			tmp4 = tmp4->next;
			tmp3 = Head;
		} else{
			while(tmp3 != tmp4->rand){
				tmp2 = tmp2->next;
				tmp3 = tmp3->next;
			}

			tmp1->rand = tmp2;

			tmp1 = tmp1->next;
			tmp2 = CopyHead;

			tmp4 = tmp4->next;
			tmp3 = Head;
		}
	}

	PrintList(CopyHead);

	return CopyHead;
}




int main(){

	NodeList* Head = ReadList();

	ListCopy(Head);

	// PrintList(Head);

	NodeList* Copy;

	return 0;
}