//头文件部分
#include"FamilyTree.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

//函数实现
void writeTree(FILE* fout, Node* root)//写入文件递归函数
{
	if (root == NULL)//返回条件
	{
		return;
	}
	else
	{
		//格式化左对齐写入txt文本文件
		fprintf(fout, "%-12s%-15d%-25d%-20d%-25s%-31s%-15d%-17d%-25d%-28d%-21d\n", root->name.c_str(), root->sex, root->generation, root->lifeSpan, root->motherName.c_str(), root->husbandName.c_str(), root->isWife, root->isDeadOrEx, root->birthYear, root->colorGene, root->weight);//name
		//写入左子树
		writeTree(fout, root->left);
		//写入右子树
		writeTree(fout, root->right);

	}
}
ErrorCode FamilyTree::writeToFile()
{
	FILE* fout;

	fopen_s(&fout, "FamilyTreeOutput.txt", "w+");//写入模式打开文件

	if (fout == NULL)//打开失败
	{
		cout << "文件不能打开" << endl;
		return failure;
	}
	else
	{
		//写入表头
		fprintf(fout, "name	sex	generation         lifeSpan        motherName    husbandName               isWife    isDead    birthYear             colorGene                weight\n");
		//调用递归写入函数
		writeTree(fout, root);
	}

	fclose(fout);//关闭文件

	return success;
}
ErrorCode FamilyTree::creatTreeFromFile()
{
	ifstream fin;
	fin.open("FamilyTreeInput.txt", ios::in);//读取形式打开文件

	if (!fin.is_open())//打开失败
	{
		cout << "文件不能打开" << endl;
		return failure;
	}
	else//打开成功
	{
		string sexName;
		char buffer[200];

		fin.getline(buffer, 190);

		while (!fin.eof())//循环建树
		{
			Node* newMember = new Node;

			//用输入参数构建节点
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
			newMember->left = NULL;
			newMember->right = NULL;

			insert(newMember);//插入构建好的节点
		}


		fin.close();//关闭文件
		return success;
	}
}
void searchTree(Node* root, Node*& member, string name)//递归搜索成员
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

Node* FamilyTree::search(string name)//查找并返回节点
{
	Node* member = NULL;
	searchTree(root, member, name);
	return member;
}
void FamilyTree::search(string name, Node*& member)//查找并把结果付给节点参数
{
	member = NULL;
	searchTree(root, member, name);
}
ErrorCode FamilyTree::insert(Node* newMember)//插入并返回成功与否
{
	if (root == NULL)
	{
		root = newMember;
		if (newMember->isDeadOrEx == 0) {
			this->aliveSize++;
		}
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
		if (newMember->isDeadOrEx == 0) {
			this->aliveSize++;
		}
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
		if (newMember->isDeadOrEx == 0) {
			this->aliveSize++;
		}
		size++;
		return success;
	}
}
void deleteTree(Node* root, int* countPtr)//递归删除树
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
ErrorCode FamilyTree::deleteMember(Node*& member)//删除节点
{
	if (member == NULL)//无此人
	{
		return failure;
	}
	else
	{
		int count = 0;
		int* countPtr = &count;

		Node* tempnode = search(member->motherName);//找到母亲或姐姐或哥哥
		deleteTree(member, countPtr);
		tempnode->right = NULL;//把母亲（或姐姐哥哥）的右子树标记为NULL

		size -= count;
	}
	return success;
}
ErrorCode FamilyTree::PrintNodeInformation(Node* member)//打印节点信息
{
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		cout << "*********************" << endl;
		cout << "代数：第" << member->generation << "代" << endl;
		cout << "名字：" << member->name << endl;
		cout << "性别：";//<< (member->sex == 1) ? "男" : "女"
		if (member->sex == 1) {
			cout << "男";
		}
		else {
			cout << "女";
		}
		cout << endl;

		cout << "生日：" << member->birthYear << "年" << endl;
		cout << "体重：" << member->weight << " kg" << endl;

		cout << "红绿色盲基因情况：";//分为男女
		if (member->sex == 1) {
			if (member->colorGene == 1) {
				cout << "XaY，是红绿色盲患者" << endl;
			}
			else {
				cout << "XAY，不是红绿色盲患者" << endl;
			}
		}
		else {
			if (member->colorGene == 1) {
				cout << "XaXa，是红绿色盲患者" << endl;
			}
			else if (member->colorGene == 2) {
				cout << "XAXa，不是红绿色盲患者" << endl;
			}
			else {
				cout << "XAXA，不是红绿色盲患者" << endl;
			}
		}
		cout << "红绿色盲基因情况：" << member->colorGene << endl; // sex=0->female->0:AA,1:aa,2:Aa    sex=1->male->0:A,1:a
		cout << "*********************" << endl;
		return success;
	}
}
ErrorCode FamilyTree::markDeath(Node* member)//标记死亡
{
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		member->isDeadOrEx = 1;
		aliveSize--;
		return success;
	}
}

ErrorCode FamilyTree::recorrect(Node* member, int part, string item)//更改节点string信息
{
	switch (part)//更改的部分
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

ErrorCode FamilyTree::recorrect(Node* member, int part, int item)//更改节点int信息
{
	switch (part)//更改部分
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

int FamilyTree::countAliveSize()//统计在世数目
{
	return this->aliveSize;
}
void countTotalLife(Node* root, int* totalLifeSpan)//统计总寿命（已死亡
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
int FamilyTree::countAverageLifeSpan()//统计平均寿命，为已死亡人的寿命总和除以已死亡人数
{
	int i = 0;
	int alredyDeadSize = size - aliveSize;

	int* totalLifeSpan = &i;

	countTotalLife(root, totalLifeSpan);
	return (*totalLifeSpan) / alredyDeadSize;
}
void countColorBlindness(Node* root, int* countPtr)//计算总色盲人数递归函数
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
int FamilyTree::totalColorBlindness()//计算总色盲人数
{
	int count = 0;
	int* countPtr = &count;
	countColorBlindness(root, countPtr);
	return count;
}
float FamilyTree::ColorBlindnessRate()//色盲率
{
	return totalColorBlindness() / size;
}


void printTree(Node* root)//打印家谱树
{
	if (root == NULL)
	{
		return;
	}
	else if (root->isWife)
	{
		cout << setw((root->generation) * 4) << "-" << root->name << endl;
		printTree(root->right);
		printTree(root->left);
	}
	else
	{
		cout << setw(((root->generation) - 1) * 4 + (root->name).length()) << root->name << endl;
		printTree(root->left);
		printTree(root->right);
	}
}
void FamilyTree::display()//展示家谱树
{
	printTree(root);
}