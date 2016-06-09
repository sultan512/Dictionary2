// Dictionary-VS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"treeNode.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;

unsigned char ld = 222;

int _tmain(int argc, _TCHAR* argv[])
{
	system("color 30");
	/**string arrayW[] = { "sultan", "above", "exertive", "agen", "unconform", "fosterling", "dome", "hallier", "arsenal", "0" };
	string arrayM[] = { "any absolute ruler or despot", "high up; far above the ground", "Having power or a tendency to exert using exertion", "See Again", "Unlike", "A foster child",
		"A building a house an edifice used chiefly in poetry", "A kind of net for catching birds",
		"a collection or supply of weapons or munitions", "0" };
	string arrayD[] = { "Noun", "Adverb", "Adjective", "Verb", "Adjective", "Noun", "Noun", "Noun", "Noun", "0" };
	fstream dict("Dictionary.txt", ios::out | ios::in);
	if (!dict)
	{			
		cerr << "File could not be opened.\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; arrayW[i] != "0"; i++)
	{
		dict << arrayW[i] << '<' << arrayM[i] << '<' << arrayD[i] << endl;
	}

	treeNode * root = new treeNode(arrayW[0], arrayM[0], arrayD[0]);

	for (int i = 1; arrayW[i] != "0"; i++)
	{
		insert(root, arrayW[i], arrayM[i], arrayD[i]);
	}**/

	//treeNode * root = new treeNode();
	//Set_Def(root);

	int size = 0;

	ifstream W("Word.txt");
	ifstream M("Meaning.txt");
	ifstream D("Description.txt");

	string arrayW[20], arrayD[20], arrayM[20];

	for (int i = 0; !W.eof(); i++)
	{
		getline(W, arrayW[i]);
		getline(M, arrayM[i]);
		getline(D, arrayD[i]);
		size++;
	}

	arrayW[size-1] = "0";
	arrayM[size-1] = "0";
	arrayD[size-1] = "0";

	treeNode* root = new treeNode(arrayW[0], arrayM[0], arrayD[0]);

	for (int i = 1; arrayW[i] != "0"; i++)
	{
		insert(root, arrayW[i], arrayM[i], arrayD[i]);
	}
	W.close();
	M.close();
	D.close();

	header();
	cout << "\n\n\n\t\t\t\tLoading Dictionary\n\n\t\t\t\t";
	cout << "    Please Wait\n\n\t\t\t\t";
	for (int i = 0; i < 18; i++)
	{
		cout << ld;
		Sleep(500);
	}
	system("cls");

	menu(root);
	//SynchToFile(root);
	DeleteDictionary(root);
	return 0;
}

