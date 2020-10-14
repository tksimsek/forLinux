#include <iostream>
#include <vector>
#include <limits>


class Node {
public:
    int data;
	Node* left;
	Node* right;
    
    Node() { left = right = nullptr; }
    ~Node() {
        if (left != nullptr) {delete left;}
        if (right != nullptr) {delete right;}
    }
};


class BST {
public:
    BST();
    ~BST();
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight();

private:
    Node* rootOfTree = NULL;
    Node* currentRoot = NULL;

    Node* GetNewNode(int data);

    void inOrderRecursive(Node* currentNode);
    int maxHeight(int left, int right);
    int findHeight(Node* currentRoot);
    
    std::vector<int> inOrderVector;
    std::vector<Node*> memoryAddressVector;
};

BST::BST(void) {}

BST::~BST(void) {
    /*
   for(int i = 0; i < memoryAddressVector.size(); i++) {
        delete memoryAddressVector.at(i);
    }*/

    if(currentRoot != NULL) {
        delete currentRoot;
    }
}

Node* BST::GetNewNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = NULL;

	return newNode;
}

void BST::insertKey(int newKey) {
    int data = newKey;

    if(rootOfTree == NULL) {
		rootOfTree = currentRoot = GetNewNode(data);
        memoryAddressVector.push_back(currentRoot);
	}
	else if(data <= currentRoot->data) {
        if(currentRoot->left == NULL) {
            currentRoot->left = GetNewNode(data);
            memoryAddressVector.push_back(currentRoot->left);
            currentRoot = rootOfTree;
        }
        else {
            currentRoot = currentRoot->left;
            insertKey(data);
        }
	}
	else if(data > currentRoot->data) {
		if(currentRoot->right == NULL) {
            currentRoot->right = GetNewNode(data);
            memoryAddressVector.push_back(currentRoot->right);
            currentRoot = rootOfTree;
        }
        else {
            currentRoot = currentRoot->right;
            insertKey(data);
        }
	}
}

bool BST::hasKey(int searchKey) {
    
    if(currentRoot == NULL) {
        currentRoot = rootOfTree;
		return false;
	}
	else if(currentRoot->data == searchKey) {
        currentRoot = rootOfTree;
		return true;
	}
    else if(searchKey <= currentRoot->data) {
        currentRoot = currentRoot->left;
		return hasKey(searchKey);
	}
	else {
        currentRoot = currentRoot->right;
		return hasKey(searchKey);
	}
}


int BST::maxHeight(int left, int right) {
    if(left > right)
        return left;
    return right;
}

int BST::findHeight(Node* currentRoot) {
    if (currentRoot == NULL)
        return 0;
    return maxHeight(findHeight(currentRoot->left),findHeight(currentRoot->right)) + 1;
}


int BST::getHeight() {
    currentRoot = rootOfTree;
    return findHeight(currentRoot);
}

void BST::inOrderRecursive(Node* currentNode) {
   if (currentNode != NULL) {
        inOrderRecursive(currentNode->left);
        inOrderVector.push_back(currentNode->data);
        inOrderRecursive(currentNode->right);
   }
}

std::vector<int> BST::inOrder() {
    if (currentRoot != NULL) {
        inOrderRecursive(currentRoot);
    }
    return inOrderVector;
}


int main() {

    BST myNewBST;

    std::cout << "Enter the numbers to be stored (end with a letter): ";
    int readBuffer;

    while(!std::cin.fail()) {
        std::cin >> readBuffer;

        if(std::cin.fail()) {
            break;
        }
        else {
            myNewBST.insertKey(readBuffer);
        }
    }

    std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Which number do you want to look up? ";
    std::cin >> readBuffer;

    std::cout << readBuffer << " is in the tree: ";
    if(myNewBST.hasKey(readBuffer)) {
        std::cout << "yes" << std::endl;
    }
    else {
        std::cout << "no" << std::endl;
    }

    std::vector<int> dataVector = myNewBST.inOrder();

    std::cout << "The numbers in sorted order: ";
    for(int i = 0; i < dataVector.size(); i++) {
        std::cout << dataVector.at(i) << " ";
    }

    std::cout << std::endl << "Height of the tree: " << myNewBST.getHeight() << std::endl;

    return 0;
}
