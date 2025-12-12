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

 
TreeNode* ReadTree(std::vector<char>& vec, int& index, int& p, int& q, TreeNode*& pPtr, TreeNode*& qPtr);

TreeNode* ReadTree(TreeNode*& pPtr, TreeNode*& qPtr){
	char input;

	int p, q;

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

	std::cin >> p >> q;

	int index = 0;

	if (vec[index] != 110){
		TreeNode* Root = new TreeNode((int)vec[index] - 48);

		if (index == p){
			pPtr = Root;
		}

		if (index == q){
			qPtr = Root;
		}

		index++;
		Root->left = ReadTree(vec, index, p, q, pPtr, qPtr);
		index++;
		Root->right = ReadTree(vec, index, p, q, pPtr, qPtr);

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


TreeNode* ReadTree(std::vector<char>& vec, int& index, int& p, int& q, TreeNode*& pPtr, TreeNode*& qPtr){
	if (vec[index] != 110){
		TreeNode* Root = new TreeNode((int)vec[index] - 48);

		if (index == p){
			pPtr = Root;
		}

		if (index == q){
			qPtr = Root;
		}

		index++;
		Root->left = ReadTree(vec, index, p, q, pPtr, qPtr);
		index++;
		Root->right = ReadTree(vec, index, p, q, pPtr, qPtr);

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

TreeNode* Process(TreeNode* Root, TreeNode* p, TreeNode* q){
	if (Root == nullptr){
		// std::cout << "1: nullptr\n";
		return nullptr;
		}

  	if (Root == p || Root == q){
  		// std::cout << "2: " << Root->value << "\n";
  	  	return Root;
  	}
    TreeNode* Left = Process(Root->left, p, q);
    TreeNode* Right = Process(Root->right, p, q);

    if (Left != nullptr && Right != nullptr){
    	// std::cout << "3: " << Root->value<< "\n";
        return Root;
    }

    if (Left != nullptr){
    	// std::cout << "4: " << Left->value<< "\n";
    	return Left;
    } else {
    	// std::cout << "5: " << Right->value<< "\n";
    	return Right;
    }
}


int main(){
	TreeNode* tmp1;
	TreeNode* tmp2;

	TreeNode* Root = ReadTree(tmp1, tmp2);

	std::cout << "\n" << "Дерево: " << "\n";
	PrintTree(Root);
	std::cout << "\n";
	std::cout << "tmp: "<< tmp1->value << " >> " << tmp1 << "; " << tmp2->value << " >> " << tmp2 << "\n" << std::endl;



	std::cout << Process(Root, tmp1, tmp2)->value << " >> " << Process(Root, tmp1, tmp2) << std::endl;

	delete Root;

	return 0;
}