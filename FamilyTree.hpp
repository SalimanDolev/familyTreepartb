#include <stdio.h>
#include <iostream>
using namespace std;
#include "Node.cpp"


namespace family{
    class Tree{
        private:
            Node *root;

        public:
        // empty constructor
        Tree(){
            this->root = new Node("empty");
            this->root->setRelation("me");
        }

        //constructor with variables
        Tree(string childName){
                this->root = new Node(childName);
                this->root->setRelation("me");
        }

        //functions
        Tree& addFather(string childName, string fatherName);
        Tree& addMother(string childName, string motherName);
        void display();
        string relation(string name);
        string find(string name);
        void remove (string name);
        /////////////////////////////////////////////////////////
        Node* findNode(Node* root,string name);
        void print(Node* current, int depth );
        ~Tree();
        void deleteNodeTree(Node *root);
    };
};