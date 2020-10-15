#include <iostream>
#include <limits>
#include <vector>
#include "matrix-template.hpp"


class Node {
public:
    int levelOfNode;
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
    void insertKey(int newKey, int levelOfTree);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight();
    void prettyPrint();

private:
    Node* rootOfTree = nullptr;
    Node* currentRoot = nullptr;

    Node* GetNewNode(int data, int levelOfNode);

    void inOrderRecursive(Node* currentNode);
    int maxHeight(int left, int right);
    int findHeight(Node* currentRoot);

    void prettyPrintRecursive(Node* currentNode, Matrix<std::string>& prettyMatrix);
    int sizeOfVector;
    int heightOfTree;

    std::vector<int> inOrderVector;
};

BST::BST(void) {}

BST::~BST(void) {
    if(rootOfTree != nullptr) {
        delete rootOfTree;
    }
}


Node* BST::GetNewNode(int data, int levelOfNode) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = nullptr;

    newNode->levelOfNode = levelOfNode;
	return newNode;
}

void BST::insertKey(int newKey, int levelOfTree) {
    int data = newKey;

    if(rootOfTree == nullptr) {
		rootOfTree = currentRoot = GetNewNode(data, levelOfTree);
	}
	else if(data <= currentRoot->data) {
        levelOfTree += 1;
        if(currentRoot->left == nullptr) {
            currentRoot->left = GetNewNode(data, levelOfTree);
            currentRoot = rootOfTree;
        }
        else {
            currentRoot = currentRoot->left;
            insertKey(data, levelOfTree);
        }
	}
	else if(data > currentRoot->data) {
        levelOfTree += 1;
		if(currentRoot->right == nullptr) {
            currentRoot->right = GetNewNode(data, levelOfTree);
            currentRoot = rootOfTree;
        }
        else {
            currentRoot = currentRoot->right;
            insertKey(data, levelOfTree);
        }
	}
}


bool BST::hasKey(int searchKey) {
    
    if(currentRoot == nullptr) {
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
    if (currentRoot == nullptr)
        return 0;
    return maxHeight(findHeight(currentRoot->left),findHeight(currentRoot->right)) + 1;
}

int BST::getHeight() {
    currentRoot = rootOfTree;
    return findHeight(currentRoot);
}


void BST::inOrderRecursive(Node* currentNode) {
   if (currentNode != nullptr) {
        inOrderRecursive(currentNode->left);
        inOrderVector.push_back(currentNode->data);
        inOrderRecursive(currentNode->right);
   }
}

std::vector<int> BST::inOrder() {
    if (currentRoot != nullptr) {
        inOrderRecursive(currentRoot);
    }
    return inOrderVector;
}


void BST::prettyPrintRecursive(Node* currentNode, Matrix<std::string>& prettyMatrix) {
    if (currentNode != nullptr) {
        
        prettyPrintRecursive(currentNode->left, prettyMatrix);

        int currentHeight = currentNode->levelOfNode;
        
        for(int column = 0; column < sizeOfVector; column++) {
            if(inOrderVector.at(column) == currentNode->data) {
                prettyMatrix.at(currentHeight, column) = std::to_string(currentNode->data);
            }
        }

        prettyPrintRecursive(currentNode->right, prettyMatrix);
   }
}

void BST::prettyPrint() {
    heightOfTree = getHeight();
    sizeOfVector = inOrderVector.size();

    if(sizeOfVector > 0) {
        Matrix<std::string> prettyMatrix(heightOfTree, sizeOfVector, "");

        currentRoot = rootOfTree;
        if (currentRoot != nullptr || sizeOfVector != 0) {
            prettyPrintRecursive(currentRoot, prettyMatrix);
        }
        prettyPrintMatrix(prettyMatrix); // expanded matrix-template function for implementing prettyPrint function
    }
}


int main() {

    BST myNewBST;

    std::cout << "Enter the numbers to be stored: ";
    int readBuffer;

    while(!std::cin.fail()) {
        std::cin >> readBuffer;

        if(std::cin.fail()) {
            break;
        }
        else {
            myNewBST.insertKey(readBuffer, 0);
        }
    }

    std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    std::vector<int> dataVector = myNewBST.inOrder();

    std::cout << std::endl << "The numbers in sorted order: ";
    for(int i = 0; i < dataVector.size(); i++) {
        std::cout << dataVector.at(i) << " ";
    }
    std::cout << std::endl;

    myNewBST.prettyPrint();

    return 0;
}

