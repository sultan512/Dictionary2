#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include "stdafx.h"
#include<conio.h>
#include<string>
#include<iomanip>
#include <cctype>
#include<iostream>

using namespace std;

class treeNode
{
private:
	treeNode *left, *right;
	string word, meaning, description;
public:
	treeNode(){}
	treeNode(string w, string m, string d);
	void setData(string w, string m, string d);
	string getWord();
	string getMeaning();
	string getDescription();
	void DisplayWordMeaning();
	void setLeft(treeNode *);
	treeNode* getLeft();
	void setRight(treeNode *);
	treeNode *getRight();
};

unsigned int DJBHash(string str);
treeNode* FindMin(treeNode * T);
bool Find(treeNode* root, string wrd);
void Edit(treeNode* root, string wrd, string newWrd, string mng, string des);
void insert(treeNode* root, string wrd, string mng, string des);
void printDictionary(treeNode* root);
treeNode* Delete(treeNode* root, string wrd);
void DeleteDictionary(treeNode*);
void header();
void Similar(treeNode* root, string wrd);
void menu(treeNode* root);
void SynchToFile(treeNode* root);
void Set_Def(treeNode *& root);
void Similar2(treeNode* root, string wrd);


#endif // TREENODE_H_INCLUDED
