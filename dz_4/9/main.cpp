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
			std::cout << Root->left->value << " >> " << Root->left << "; ";
		} else{
			std::cout << "n ";
		}
		if(Root->right){
			std::cout << Root->right->value <<  " >> " << Root->right;
		} else{
			std::cout << "n";
		}

		std::cout << std::endl;
		PrintTree(Root->left);
		PrintTree(Root->right);
	}
}

TreeNode* Process(TreeNode* Root, TreeNode* Left, TreeNode* Right){
  	if (Root == Left || Root == Right){ return Root; }

    TreeNode* p = Process(Root->left, Left, Right);
    TreeNode* q = Process(Root->right, Left, Right);

    if (p != nullptr && q != nullptr)
        return Root;

    return (p != nullptr ? p : q);
}


int main(){
	TreeNode* Root = ReadTree();

	std::cout << "\n";
	PrintTree(Root);
	std::cout << "\n";





	std::cout << Process(Root, Root->left->right, Root->left->left)->value << std::endl;

	return 0;
}