#include <iostream>
#include <fstream>
#include <string>

class Address {
private:
    std::string city;
    std::string street;
    int home;
    int apartment;

public:
    Address(const std::string& city, const std::string& street, int home, int apartment) : city(city), street(street), home(home), apartment(apartment) {}

    std::string getCity() const {
        return city;
    }

    std::string getOutputAddress() const {
        return city + ", " + street + ", " + std::to_string(home) + ", " + std::to_string(apartment);
    }
};

class Node {
public:
    Address data;
    Node* left;
    Node* right;

    Node(const Address& data) : data(data), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, const Address& data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data.getCity() < node->data.getCity()) {
            node->left = insert(node->left, data);
        }
        else {
            node->right = insert(node->right, data);
        }

        return node;
    }

    void inorderTraversal(Node* node, std::ofstream& outFile) {
        if (node != nullptr) {
            inorderTraversal(node->left, outFile);
            outFile << node->data.getOutputAddress() << std::endl;
            inorderTraversal(node->right, outFile);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(const Address& data) {
        root = insert(root, data);
    }

    void inorderTraversal(std::ofstream& outFile) {
        inorderTraversal(root, outFile);
    }
};

int main() {
    std::ifstream inFile("in.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    int n;
    inFile >> n;

    BST bst;

    for (int i = 0; i < n; ++i) {
        std::string city, street;
        int home, apartment;
        inFile >> city >> street >> home >> apartment;
        Address address(city, street, home, apartment);
        bst.insert(address);
    }

    inFile.close();

    std::ofstream outFile("out.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    outFile << n << std::endl;
    bst.inorderTraversal(outFile);

    outFile.close();

    return 0;
}
