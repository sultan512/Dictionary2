
#include "stdafx.h"
#include "treeNode.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <ctime>
#include <fstream>

#pragma warning(disable : 4996)

using namespace std;

treeNode::treeNode(string w, string m, string d)
{
	word = w;
	meaning = m;
	description = d;
	left = NULL;
	right = NULL;
}

void treeNode::setData(string w, string m, string d)
{
	word = w;
	meaning = m;
	description = d;
}

void treeNode::DisplayWordMeaning()
{
	cout << "Word        : " << word << "\n" << "Meaning     : " << meaning << "\n" << "Description : " << description << endl;
	cout << "___________________________________________________________________" << endl;
}

string treeNode::getWord()
{
	return word;
}
string treeNode::getMeaning()
{
	return meaning;
}

string treeNode::getDescription()
{
	return description;
}

void treeNode::setLeft(treeNode *l)
{
	left = l;
}

void treeNode::setRight(treeNode *r)
{
	right = r;
}

treeNode* treeNode::getRight()
{
	return right;
}

treeNode* treeNode::getLeft()
{
	return left;
}

unsigned int DJBHash(string str)
{
	unsigned int hash = 5381;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

treeNode* FindMin(treeNode * T)
{
	if (T == NULL)
		return NULL;
	else if (T->getLeft() == NULL)
		return T;
	else
		return FindMin(T->getLeft());
}

bool Find(treeNode* root, string wrd)
{
	treeNode *q;
	q = root;
	if (q == NULL)
	{
		cout << "Word Not Found.\n";
		cout << "\nDid you mean:\n\n";
		Similar2(root, wrd);
		return 0;
	}
	else if (DJBHash(wrd) == DJBHash(q->getWord()))
	{
		q->DisplayWordMeaning();
		return 1;
	}
	else if (DJBHash(wrd) < DJBHash(q->getWord()))
		Find(q->getLeft(), wrd);
	else if (DJBHash(wrd) > DJBHash(q->getWord()))
		Find(q->getRight(), wrd);
}

void Edit(treeNode* root, string wrd, string newWrd, string mng, string des)
{
	if (root != NULL)
	{
		Edit(root->getLeft(), wrd, newWrd, mng, des);
		Edit(root->getRight(), wrd, newWrd, mng, des);
		if (wrd == root->getWord())
		{
			root->setData(newWrd, mng, des);
		}
	}
}

void insert(treeNode* root, string wrd, string mng, string des)
{
	unsigned int d = 0;
	treeNode* Newnode = new treeNode(wrd, mng, des);
	treeNode *p, *q;
	p = q = root;
	d = DJBHash(wrd);
	while (d != DJBHash(p->getWord()) && q != NULL)
	{
		p = q;
		if (d < DJBHash(p->getWord()))
		{
			q = p->getLeft();
		}
		else
		{
			q = p->getRight();
		}
	}
	if (d == DJBHash(p->getWord()))
	{
		cout << endl << "duplicate value :" << p->getWord() << endl;

	}
	else if (d < DJBHash(p->getWord()))
	{
		p->setLeft(Newnode);
	}
	else if (d > DJBHash(p->getWord()))
	{
		p->setRight(Newnode);
	}
}

void printDictionary(treeNode* root)
{
	if (root != NULL)
	{
		root->DisplayWordMeaning();
		printDictionary(root->getLeft());
		printDictionary(root->getRight());
	}
}

void DeleteDictionary(treeNode* root)
{
	if (root != NULL)
	{
		DeleteDictionary(root->getLeft());
		DeleteDictionary(root->getRight());
		delete root;
	}
}
treeNode* Delete(treeNode* root, string wrd)
{
	if (root == NULL) return root;
	else if (DJBHash(wrd) < DJBHash(root->getWord())) root->setLeft(Delete(root->getLeft(), wrd));
	else if (DJBHash(wrd) > DJBHash(root->getWord())) root->setRight(Delete(root->getRight(), wrd));
	else {
		// Case 1: No Child
		if (root->getLeft() == NULL && root->getRight() == NULL){
			delete root;
			root = NULL;
			// Case 2: one child
		}
		else if (root->getLeft() == NULL){
			treeNode *temp = root;
			root = root->getRight();
			delete temp;
		}
		else if (root->getRight() == NULL){
			treeNode *temp = root;
			root = root->getLeft();
			delete temp;
		}
		else{
			treeNode *temp = FindMin(root->getRight());
			root->setData(temp->getWord(), temp->getMeaning(), temp->getDescription());
			root->setRight(Delete(root->getRight(), temp->getWord()));
		}
	}
	return root;
}

void header()
{
	unsigned char l2 = 177;
	for (int i = 0; i < 30; i++)
		cout << l2;
	cout << " Sultan's Dictionary ";
	for (int i = 0; i < 29; i++)
		cout << l2;
	time_t timev;
	time(&timev);
	cout << "\n\t\t\t\t\t\t\t" << ctime(&timev);
	cout << endl << endl;
}

void Similar2(treeNode* root, string wrd)
{
	ifstream W("Word.txt");
	char ch_wrd[1024], key[15];
	string k;
	strncpy(ch_wrd, wrd.c_str(), sizeof(ch_wrd));
	ch_wrd[sizeof(ch_wrd) - 1] = 0;
	while (!W.eof())
	{
		getline(W, k, '\n');
		strncpy(key, k.c_str(), sizeof(key));
		key[sizeof(key) - 1] = 0;
		if (strncmp(ch_wrd, key, 2) == 0)
			cout << k << endl;
	}
	cout << endl;
	W.close();
}

void Similar(treeNode* root, string wrd)
{
	/**if (root != NULL)
	{
		string key = root->getWord();
		if (wrd[0] == key[0] && wrd[1] == key[1])
			root->DisplayWordMeaning();
		Similar(root->getLeft(), wrd);
		Similar(root->getRight(), wrd);
	}
	else return;**/
	treeNode *current, *pre;
	string str;
	if (root == NULL)
		return;
	current = root;
	while (current != NULL)
	{
		if (current->getLeft() == NULL)
		{
			str = current->getWord();
			if (wrd.substr(2) == str.substr(2))
				current->DisplayWordMeaning();
			current = current->getRight();
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->getLeft();
			while (pre->getRight() != NULL && pre->getRight() != current)
				pre = pre->getRight();

			/* Make current as right child of its inorder predecessor */
			if (pre->getRight() == NULL)
			{
				pre->setRight(current);
				current = current->getLeft();
			}

			/* Revert the changes made in if part to restore the original
			tree i.e., fix the right child of predecssor */
			else
			{
				pre->setRight(NULL);
				str = current->getWord();
				if (wrd.substr(2) == str.substr(2))
					current->DisplayWordMeaning();
				current = current->getRight();
			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */
}

void Set_Def(treeNode * &root)
{
	string arrayW[] = { "sultan", "above", "exertive", "agen", "unconform", "fosterling", "dome", "hallier", "arsenal", "subtle", "0" };
	string arrayM[] = { "any absolute ruler or despot", "high up; far above the ground", "Having power or a tendency to exert using exertion", "See Again", "Unlike", "A foster child",
		"A building a house an edifice used chiefly in poetry", "A kind of net for catching birds", "So delicate or precise",
		"a collection or supply of weapons or munitions", "0" };
	string arrayD[] = { "Noun", "Adverb", "Adjective", "Verb", "Adjective", "Noun", "Noun", "Noun", "Noun", "Adjective", "0" };
	ofstream W("Word.txt");
	ofstream M("Meaning.txt");
	ofstream D("Description.txt");
	if (!W || !M || !D)
	{
		cerr << "File could not be opened.\n";
	}

	for (int i = 0; arrayW[i] != "0"; i++)
	{
		W << arrayW[i] << '\n';
		M << arrayM[i] << '\n';
		D << arrayD[i] << endl;
	}

	root = new treeNode(arrayW[0], arrayM[0], arrayD[0]);

	for (int i = 1; arrayW[i] != "0"; i++)
	{
		insert(root, arrayW[i], arrayM[i], arrayD[i]);
	}
	W.close();
	M.close();
	D.close();
}

void SynchToFile(treeNode* root)
{
	treeNode *current, *pre;
	ofstream W("Word.txt");
	ofstream M("Meaning.txt");
	ofstream D("Description.txt");

	if (!W || !M || !D)
	{
		cerr << "File could not be opened.\n";
		system("pause");
		system("cls");
		menu(root);
	}
	if (root == NULL)
		return;
	current = root;
	while (current != NULL)
	{
		if (current->getLeft() == NULL)
		{
			W << current->getWord() << endl;
			M << current->getMeaning() << endl;
			D << current->getDescription() << endl;
			current = current->getRight();
		}
		else
		{
			/* Find the inorder predecessor of current */
			pre = current->getLeft();
			while (pre->getRight() != NULL && pre->getRight() != current)
				pre = pre->getRight();

			/* Make current as right child of its inorder predecessor */
			if (pre->getRight() == NULL)
			{
				pre->setRight(current);
				current = current->getLeft();
			}

			/* Revert the changes made in if part to restore the original
			tree i.e., fix the right child of predecssor */
			else
			{
				pre->setRight(NULL); 
				W << current->getWord() << endl;
				M << current->getMeaning() << endl;
				D << current->getDescription() << endl;
				current = current->getRight();
			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */
	W.close();
	M.close();
	D.close();
}

void menu(treeNode* root)
{
	string key, key2, m, d;
	header();
	cout << "Enter i to insert " << endl;
	cout << "Enter e to edit " << endl;
	cout << "Enter d to delete" << endl;
	cout << "Enter s to show dictionary " << endl;
	cout << "Enter f to find word" << endl;
	cout << "Enter sd to set default" << endl;
	cout << "Enter exit to exit" << endl;
	cout << "Option: ";
	getline(cin, key);
	system("cls");

	if (key == "e")
	{
		header();
		cout << "Edit Menu:\n";
		cout << "\tEnter to replace: ";
		getline(cin, key);
		if (!Find(root, key))
		{
			system("pause");
			system("cls");
			menu(root);
		}
		else
		{
			cout << "\tEnter replacement: ";
			getline(cin, key2);
			cout << "\tEnter meaning: ";
			getline(cin, m);
			cout << "\tEnter Part of speech: ";
			getline(cin, d);
			Edit(root, key, key2, m, d);
		}
	}
	else if (key == "i")
	{
		header();
		cout << "Insert Menu:\n";
		cout << "\tEnter New Word: ";
		getline(cin, key2);
		cout << "\tEnter it's meaning: ";
		getline(cin, m);
		cout << "\tEnter Part of Speech: ";
		getline(cin, d);
		insert(root, key2, m, d);
	}
	else if (key == "d")
	{
		header();
		cout << "Delete Menu:\n";
		cout << "\tEnter Value To delete: ";
		getline(cin, key2);
		if (Delete(root, key2) == NULL)
			cout << "Word not Found\n";
		else
			cout << "\tSuccessfully Deleted: " << key2 << endl;
	}
	else if (key == "s")
	{
		header();
		printDictionary(root);
	}
	else if (key == "f")
	{
		header();
		cout << "Search Menu:\n";
		cout << "\tEnter Word to Search: ";
		getline(cin, key2);
		Find(root, key2);
	}
	else if (key == "exit")
	{
		header();
		SynchToFile(root);
		exit(0);
	}
	else if (key == "sd")
	{
		header();
		Set_Def(root);
		cout << "Dictionary Set to Default!\n\n";
	}
	else
	{
		header();
		cerr << "Wrong Option Entered.\n";
	}
	SynchToFile(root);
	system("pause");
	system("cls");
	menu(root);
}
