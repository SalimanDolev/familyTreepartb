#include "FamilyTree.hpp"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include "Node.cpp"
#define W "W"
#define M "M"
#define COUNT 10

using namespace std;
using namespace family;

static int depth = 1;
 

///////////////////////////////////////////////////////////////////////////////
/////////////////////Add father to node////////////////////////////////////////

Tree& Tree::addFather(string childName, string fatherName){
    if(root != nullptr){
        Node *tmp = Tree::findNode(this->root,childName);
        if(tmp == nullptr) throw out_of_range ("One of the people is not on the tree");
        if(tmp->getFather() == nullptr){
            Node father = Node(fatherName);
            tmp->setFather(father.getName());
            tmp->getFather()->setGender("M");
            tmp->getFather()->setRank(tmp->getRank()+1);
            tmp->getFather()->setRelation(family::Tree::relation(fatherName));
            tmp->getFather()->setChildName(tmp->getName());
        }
        else throw out_of_range("Father already exists");
    }
    else {
        root->setFather(fatherName);
    }
    return (*this);
}
///////////////////////////////////////////////////////////////////////////////
/////////////////////Add mother to node////////////////////////////////////////
        
Tree& Tree::addMother(string childName, string motherName){
     if(root != nullptr){
        Node *tmp = findNode(this->root,childName);
        if(tmp == nullptr) throw out_of_range ("One of the people is not on the tree");
        if(tmp->getMother() == nullptr){
            Node mother = Node(motherName);
            tmp->setMother(mother.getName());
            tmp->getMother()->setGender("W");
            tmp->getMother()->setRank(tmp->getRank() +1);
            tmp->getMother()->setRelation(family::Tree::relation(motherName));
            tmp->getMother()->setChildName(tmp->getName());
        }
        else throw out_of_range("Mother already exists");
    }
     else {
         root->setMother(motherName);
        }
    return (*this);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////  Display and print function////////////////
void Tree::display(){
    print(this->root, 0);
}

void Tree::print(Node *current, int space )
  {
       // Base case  
    if (current == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first
    if(current->getMother() != nullptr){  
    print(current->getMother(), space);  
    }
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<current->getName()<<"\n";  
  
    // Process left child
    if(current->getFather()!=nullptr){  
    print(current->getFather(), space); 
    }
  }
////////////////////////////////////////////////////////////////////////////////
///////////////////////////Relation function////////////////////////////////////

string Tree::relation(string name){
    string relations []= {"father" , "mother", "grandmother", "grandfather","great-"};
    depth = 1;
    Node *tmp = Tree::findNode((*this).root , name);
    if ( tmp != nullptr){

        if(tmp->getRank() == 0 ) return "me";
        if(tmp->getRank() == 1 && tmp->getGender().compare("M") == 0) return relations[0];
        if(tmp->getRank() == 1 && tmp->getGender().compare("W") == 0) return relations[1];
        if(tmp->getRank() == 2 && tmp->getGender().compare("W") == 0) return relations[2];
        if(tmp->getRank() == 2 && tmp->getGender().compare("M") == 0) return relations[3];
        if(tmp->getRank()>2){
            string str;
            if(tmp->getGender().compare("W") == 0){
                for (int i = 0; i < tmp->getRank()-2; i++)
                {
                    str = str +relations[4];
                }
                str = str + relations[2];
                return str;
            }
            if(tmp->getGender().compare("M") == 0){
                for (int i = 0; i < tmp->getRank()-2; i++)
                {
                    str = str + relations[4];
                }
                str = str + relations[3];
                return str;
            
            }
        }
        return "unrelated";
        }
    return "unrelated";
}
///////////////////////////////////////////////////////////////////////////////
//////////////////////////Find relation fumction///////////////////////////////
Node *findRelation(Node *node,string name){
    if(node != nullptr){
        if(node->getRelation() == name){
            return node;
        }
        Node *tempF = findRelation(node->getFather(),name);
        if (tempF != nullptr) {
            return tempF;
        }
        Node *tempM = findRelation(node->getMother(),name);
        if (tempM != nullptr) {
            return tempM;
        }
    }
    return nullptr;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////Find relation of node///////////////////////////////

string Tree::find(string name){
    Node *tmp = findRelation(this->root,name);
    if(tmp != nullptr){
        if (tmp->getRelation() == name){
            return tmp->getName();
        }
        else{
            throw out_of_range("The tree cannot handle the "+ name + " relation");
        }
    }else{
        throw out_of_range("The tree cannot handle the "+ name + " relation");
    }
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////////Remove function//////////////////////////////
void Tree::deleteNodeTree(Node *root) {

    if (root != nullptr) {

        deleteNodeTree(root->getFather());
        deleteNodeTree(root->getMother());
        
        delete (root);
        if (root->getFather() != nullptr)
            root->setFnull();
        if (root->getMother() != nullptr)
            root->setMnull();
    }
}
void Tree::remove(string name){
    // getting the specific node to delete
    Node *temp = findNode(this->root,name);
    if(temp == this->root) throw out_of_range ("cant erase the root");

    if (temp != nullptr) {
        // getting the child so after we can point him to null
        Node *child = findNode(this->root,temp->getChildName());

        // comparing addresses to know who to delete - mother or father
        if (child->getFather() == temp) {
            child->setFnull();
        } else {
            child->setMnull();
        }

        deleteNodeTree(temp);
    }
    if(temp == nullptr) throw out_of_range ("not on the tree");
}


///////////////////////////////////////////////////////////////////////////////
/////////////////////Find node with root and name function/////////////////////
Node *Tree::findNode(Node *node,string name){
    if(node != nullptr){
        if(node->getName() == name){
            return node;
        }
        Node *tempF = findNode(node->getFather(),name);
        if (tempF != nullptr) {
            return tempF;
        }
        Node *tempM = findNode(node->getMother(),name);
        if (tempM != nullptr) {
            return tempM;
        }
    }
    return nullptr;
}
///////////////////////////////////////////////////////////////////////////////

Tree::~Tree() {
    deleteNodeTree(root);
}
