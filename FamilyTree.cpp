#include"FamilyTree.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>


void writeTree(FILE* fout, Node* root)//recursive function
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		char* genbuf;
		itoa(root->generation, genbuf, 10);//这个函数头文件为stdlib，把int转为char*

		char* birthbuf;
		itoa(root->birthYear, birthbuf, 10);

		fprintf(fout, root->name.c_str());

		fprintf(fout, "   ");

		fprintf(fout, genbuf);

		if (root->sex == 1)
			fprintf(fout, "MALE");
		else
			fprintf(fout, "FEMALE");

		fprintf(fout, "   ");

		fprintf(fout, birthbuf);
		fprintf(fout, "\n");


		writeTree(fout, root->left);
		writeTree(fout, root->right);
	}
}
ErrorCode FamilyTree::writeToFile()
{

	FILE* fout;
	fout = fopen("FamilyTreeOutput.txt", "w+");
	if (fout == NULL)
	{
		cout << "文件不能打开" << endl;
		return failure;
	}
	else
	{
		writeTree(fout, root);

	}
	fclose(fout);
	return success;
}
ErrorCode FamilyTree::creatTreeFromFile()
{
	ifstream fin("FamilyTreeInput.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "文件不能打开" << endl;
		return failure;
	}
	else
	{
		string sexName;

		while (!fin.eof())
		{
			Node* newMember = new Node;
			fin >> newMember->name >> sexName >> newMember->generation >> newMember->lifeSpan >> newMember->motherName;
			fin >> newMember->husbandName >> newMember->isWife >> newMember->isDeadOrEx >> newMember->birthYear;
			fin >> newMember->colorGene >> newMember->weight;

			if (sexName[0] == 'M')
			{
				newMember->sex = 1;
			}
			else
			{
				newMember->sex = 0;
			}
			insert(newMember);
		}
		

		fin.close();

	}

	
}
void searchTree(Node* root, Node* & member, string name)//recursive function
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->name == name)
		{
			member = root;
			return;
		}
		else
		{
			searchTree(root->left, member, name);
			searchTree(root->right, member, name);
		}
	}
}

Node* FamilyTree::search(string name)
{
	Node* member = NULL;
	searchTree(root, member, name);
	return member;
}
void FamilyTree::search(string name, Node* & member)
{
	member = NULL;
	searchTree(root, member, name);
}
ErrorCode FamilyTree::insert(Node* newMember)
{
	if (root == NULL)
	{
		root = newMember;
		size++;
		return success;
	}
	if (newMember->isWife)
	{
		Node* temp = search(newMember->husbandName);
		if (temp == NULL)
		{
			return failure;
		}
		while (temp->left != NULL)
		{
			temp = temp->left;
		}
		temp->left = newMember;
		size++;
		return success;
	}
	else
	{
		Node* temp = search(newMember->motherName);
		if (temp == NULL)
		{
			return failure;
		}
		while (temp->right != NULL)
		{
			temp = temp->right;
		}
		temp->right = newMember;
		size++;
		return success;
	}
}
void deleteTree(Node* root, int * countPtr)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		deleteTree(root->left, countPtr);
		deleteTree(root->right, countPtr);
		delete(root);
		(*countPtr)++;
	}
}
ErrorCode FamilyTree::deleteMember(Node* & member)
{
	//Node* member = search(name);
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		int count = 0;
		int * countPtr = &count;
		deleteTree(member, countPtr);
		member = NULL;
		size -= count;
	}
	return success;
}
ErrorCode FamilyTree::PrintNodeInformation(Node* member)
{
	//Node* member = search(name);
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		cout << "*********************" << endl;
		cout << "代数：" << member->generation << endl;
		cout << "名字：" << member->name << endl;
		cout << "性别：" << (member->sex == 1) ? "男\n" : "女\n";

		cout << "生日：" << member->birthYear << endl;
		cout << "体重：" << member->weight << endl;
		cout << "红绿色盲基因情况：" << member->colorGene << endl;
		cout << "*********************" << endl;
	}
}
ErrorCode FamilyTree::markDeath(Node* member)
{
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		member->isDeadOrEx = 1;
		return success;
	}
}

ErrorCode FamilyTree::recorrect(Node* member, int part, string item)
{
	
	switch (part)
	{
		case 1:
			member->name = item;
			break;
		case 5:
			member->motherName = item;
			break;
		case 6:
			member->husbandName = item;
			break;
		default:
			return failure;
	}
	return success;
		

}

ErrorCode FamilyTree::recorrect(Node* member, int part, int item)
{

	switch (part)
	{
		case 2:
			member->sex = item;
			break;
		case 3:
			member->generation = item;
			break;
		case 4:
			member->lifeSpan = item;
			break;
		case 7:
			member->isWife = item;
			break;
		case 8:
			member->isDeadOrEx = item;
			break;
		case 9:
			member->birthYear = item;
			break;
		case 10:
			member->colorGene = item;
			break;
		case 11:
			member->weight = item;
			break;
		default:
			return failure;
	}
	return success;


}

int FamilyTree::countAliveSize()
{
	return this->aliveSize;
}
void countTotalLife(Node* root, int* totalLifeSpan)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->isDeadOrEx == 1)
		{
			*totalLifeSpan += root->lifeSpan;
		}
		countTotalLife(root->left, totalLifeSpan);
		countTotalLife(root->right, totalLifeSpan);
	}
}
int FamilyTree::countAverageLifeSpan()
{
	int alredyDeadSize = size - aliveSize;
	int* totalLifeSpan;
	*(totalLifeSpan) = 0;
	countTotalLife(root, totalLifeSpan);
	return (*totalLifeSpan) / alredyDeadSize;
}
void countColorBlindness(Node *root, int * countPtr)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->colorGene == 1 && !(root->isWife))
		{
			(*countPtr)++;
		}
		countColorBlindness(root->left, countPtr);
		countColorBlindness(root->right, countPtr);


	}
}
int FamilyTree::totalColorBlindness()
{
	int count = 0;
	int* countPtr = &count;
	countColorBlindness(root, countPtr);
	return count;
}

float FamilyTree::ColorBlindnessRate()
{
	return totalColorBlindness() / size;
}

/*
void printTree(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	else if (root->isWife)
	{
		cout << "W-" << root->name << endl;
		cout << " ";
		printTree(root->left);

		printTree(root->right);
	}
	else
	{
		cout << root->name << endl;
	}
}
void FamilyTree::display()
{
	printTree(root);
}
*/