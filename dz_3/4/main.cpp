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
		std::cout << tmp->value << " -> " << tmp << "; Value of random ptr: ";
		if (tmp->rand == nullptr){
			std::cout << "NULL -> 0x0" << std::endl;
		} else {
			std::cout << tmp->rand->value << " -> " << tmp->rand << std::endl;
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
		if (vec[i] <= 0){
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




// NodeList* ListCopy(NodeList* Head){
// 	NodeList* CopyHead = new NodeList(Head->value);

// 	NodeList* tmp1 = CopyHead;
// 	NodeList* tmp2 = Head->next;
// 	NodeList* tmp3 = Head;
// 	NodeList* tmp4 = Head;

// 	while(tmp2 != nullptr){
// 		NodeList* tmp = new NodeList(tmp2->value);
// 		tmp1->next = tmp;
// 		tmp1 = tmp;
// 		tmp2 = tmp2->next;
// 	}

// 	tmp1 = CopyHead;
// 	tmp2 = CopyHead;
// 	tmp3 = Head;
// 	tmp4 = Head;

// 	// std::cout << "\n";
// 	// PrintList(CopyHead);
// 	// std::cout << "\n";
// 	// PrintList(Head);

// 	while(tmp1 != nullptr){

// 		if(tmp4->rand == nullptr){
// 			tmp1->rand = nullptr;

// 			tmp1 = tmp1->next;
// 			tmp2 = CopyHead;

// 			tmp4 = tmp4->next;
// 			tmp3 = Head;
// 		} else{
// 			while(tmp3 != tmp4->rand){
// 				tmp2 = tmp2->next;
// 				tmp3 = tmp3->next;
// 			}

// 			tmp1->rand = tmp2;

// 			tmp1 = tmp1->next;
// 			tmp2 = CopyHead;

// 			tmp4 = tmp4->next;
// 			tmp3 = Head;
// 		}
// 	}

// 	PrintList(CopyHead);

// 	return CopyHead;
// }

NodeList* ListCopy(NodeList* Head){
	// NodeList* CopyTMP = new NodeList(Head->value);

	// NodeList* tmp1 = CopyTMP;
	// NodeList* tmp2 = Head->next;
	// NodeList* tmp3 = Head;
	// NodeList* tmp4 = Head;

	// while(tmp2 != nullptr){
	// 	NodeList* tmp = new NodeList(tmp2->value);
	// 	tmp1->next = tmp2;
	// 	tmp1 = tmp;
	// 	tmp2 = tmp2->next;
	// }

	// PrintList(CopyTMP);

	NodeList* CopyHead = new NodeList(Head->value);

	NodeList* tmp1 = CopyHead;
	NodeList* tmp2 = Head->next;

	while(tmp2 != nullptr){
		NodeList* tmp = new NodeList(tmp2->value);
		tmp1->next = tmp;
		tmp1 = tmp;
		tmp2 = tmp2->next;
	}

	
	tmp1 = Head;
	tmp2 = CopyHead;

	NodeList* tmp3 = CopyHead->next;

	//Сшивание Head и CopyHead
	while(tmp1->next != nullptr){
		tmp2->next = tmp1->next;
		tmp1->next = tmp2;


		tmp1 = tmp2->next;
		tmp2 = tmp3;
		tmp3 = tmp2->next;
	}

	tmp1->next = tmp2;


	tmp1 = Head;


	//Задаем rand
	while(tmp1 != nullptr){

		if(tmp1->rand == nullptr){
			tmp1->next->rand = nullptr;
		} else{
			tmp1->next->rand = tmp1->rand->next;
		}

		tmp1 = tmp1->next->next;
	}

	tmp1 = Head;
	tmp2 = CopyHead;


	//Обратная склейка
	while(tmp2->next != nullptr){
		// std::cout << tmp1->value << "\n";

		tmp1->next = tmp2->next;
		tmp2->next = tmp2->next->next;

		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}

	tmp1->next = nullptr;
	tmp2->next = nullptr;

	// std::cout << "\n";

	// PrintList(Head);

	// std::cout << "\n";

	// PrintList(CopyHead);

	return CopyHead;
}




int main(){

	NodeList* Head = ReadList();

	NodeList* Copy = ListCopy(Head);

	std::cout << "\n";

	PrintList(Head);

	std::cout << "\n";

	PrintList(Copy);


	// delete ;

	return 0;
}