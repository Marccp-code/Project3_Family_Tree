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

		if(root->sex==1)
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
	fout = fopen("D:\FamilyTreeOutput.txt", "w+");
	if (fout == NULL)
	{
		cout << "文件不能打开" << endl;
		return failed;
	}
	else
	{
		writeTree(fout, root);

	}	
	fclose(fout);
}

void searchTree(Node* root, Node* member, string name)//recursive function
{
	if (root == NULL)
	{
		member = NULL;
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
	Node* member;
	searchTree(root, member, name);
	return member;
}
void deleteTree(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		deleteTree(root->left);
		deleteTree(root->right);
		delete(root);
	}
}
ErrorCode FamilyTree::deleteMember(Node* member)
{
	//Node* member = search(name);
	if (member == NULL)
	{
		return failed;
	}
	else
	{
		deleteTree(member);
	}
	return success;
}
ErrorCode FamilyTree::PrintNodeInformation(Node* member)
{
	//Node* member = search(name);
	if (member == NULL)
	{
		return failed;
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
		return failed;
	}
	else
	{
		member->isDeadOrEx = 1;
		return success;
	}
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
		*totalLifeSpan += root->lifeSpan;
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