#include <iostream>
#include <vector>


/*
	todo:
		- Надо сделать автотест или хотя бы примеры заготовить для Кривчикова...
		- А есть ли алгоритм попиятнее, чем простой перебор?
*/


struct TreeNode{
	int value;
	TreeNode* right;
	TreeNode* left;

	TreeNode(int value):
		value(value),
		right(nullptr),
		left(nullptr)
	{}

	~TreeNode(){
		if (right)
			delete right;
		if (left)
			delete left;
	}
};


struct ListNode{
	int value;
	ListNode* next;

	ListNode(int value):
		value(value),
		next(nullptr)
	{}

	~ListNode(){
		delete next;
	}
};

ListNode* ReadList(){
	int input;
	std::cin >> input;

	ListNode* Head = new ListNode(input);

	ListNode* tmp = Head;

	while(std::cin >> input){
		tmp->next = new ListNode(input);
		tmp = tmp->next;
	}

	return Head;
}


void PrintList(ListNode* Head){
	std::cout << "\n";

	ListNode* i = Head;

	while (i != nullptr){
		std::cout << i->value << " >> ";

		i = i->next;
	}

	std::cout << "NULL" << std::endl;
}

TreeNode* ReadTree(std::vector<char>& vec, int& index);

TreeNode* ReadTree(){
	char input;

	std::vector<char> vec;
	while(true){
		std::cin >> input;
		if (input == 'e'){ break; }

		if (input == 'n'){
			vec.push_back('n');
		} else {
			vec.push_back(input);
		}
	}

	int index = 0;

	if (vec[index] != 110){
		TreeNode* Root = new TreeNode((int)vec[index] - 48);

		index++;
		Root->left = ReadTree(vec, index);
		index++;
		Root->right = ReadTree(vec, index);

		return Root;
	} else {
		return nullptr;
	}

	/*
	                                       -_-                              
	Все оказалось существенно проще...
	*/
}

//==================================================================//


TreeNode* ReadTree(std::vector<char>& vec, int& index){
	if (vec[index] != 110){
		TreeNode* Root = new TreeNode((int)vec[index] - 48);

		index++;
		Root->left = ReadTree(vec, index);
		index++;
		Root->right = ReadTree(vec, index);

		return Root;
	} else {
		return nullptr;
	}
}


void PrintTree(TreeNode* Root){

	if (Root){
		std::cout << Root->value << " >> " << Root << ": ";
		if(Root->left){
			std::cout << Root->left->value << " >> " << Root->left << ", ";
		} else{
			std::cout << "nullptr, ";
		}
		if(Root->right){
			std::cout << Root->right->value << " >> " << Root->right;
		} else{
			std::cout << "nullptr";
		}
		

		std::cout << std::endl;
		PrintTree(Root->left);
		PrintTree(Root->right);
	}
}

bool process(TreeNode* Root, ListNode* Head){

	// std::cout << Head->value << "\n";

	if ((Root == nullptr) && (Head != nullptr)){
		return (bool)0;
	}

	if (Head == nullptr){
		return (bool)1;
	} else{
		if (Root->value == Head->value){
			return (process(Root->left, Head->next) || process(Root->right, Head->next));
		}
	}

	return (bool)0;
}


int main(){
	TreeNode* Root = ReadTree();

	std::cout << "\n";
	PrintTree(Root);
	std::cout << "\n";

	ListNode* Head = ReadList();
	
	PrintList(Head);
	std::cout << "\n";



	std::cout << process(Root, Head) << std::endl;

	return 0;
}