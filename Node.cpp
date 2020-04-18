#pragma once
#include <iostream>
#include "string.h"
using namespace std;


class Node{
private:
    string gender; 
    string m_name;
    Node* m_father;
    Node* m_mother;
    int rank;
    string m_relation;
    string child_name;
public:
    Node():m_name("empty"),gender(""),rank(0),m_father(nullptr),m_mother(nullptr),m_relation("empty"),child_name("empty"){}

    Node(string name){
        this->m_name = name;
        this->m_father = nullptr;
        this->m_mother = nullptr;
        this->gender = "";
        this->rank =0;
        this->m_relation= "empty";
        this->child_name = "empty";

    }

    void setChildName(string name){
        this->child_name = name;
    }
    string getChildName(){
        return this->child_name;
    }

    void setFnull(){
        this->m_father = nullptr;
    }

    void setMnull(){
        this->m_mother = nullptr;
    }

    ~Node(){};

    void setRelation(string relation){
        this->m_relation = relation;
    }
    string getRelation(){
        return this->m_relation;
    }

    void setRank(int num){
        this->rank = num;
    }
    int getRank(){
        return this->rank;
    }

    string getName(){
        return this->m_name;
    }
    Node* getFather(){
        return this->m_father;
    }

    Node* getMother(){
        return this->m_mother;
    }
    void setFather(Node father){
        this->m_father = new Node(father);
    }
    void setMother(Node mother){
        this->m_mother = new Node(mother);
    }
    string getGender(){
        return this->gender;
    }

    void setGender(string g){
        this->gender = g;
    }

};