#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
enum ErrorCode { success, failed, overflow, underflow };

struct Node
{
	string name;
	bool sex;//sex=0->female  sex=1->male
	int generation;
	int lifeSpan;//2019-birthYear

	string motherName;
	string husbandNmae;

	bool isWife;//isWife=0->daughter  isWife=1->wife
	bool isDeadOrEx;

	int birthYear;
	

	int colorGene;// sex=0->female->0,1,2    sex=1->male->0,1
	int weight;

	Node* left;//sex=1->male->left is his wife(s) , right is his brothers and sisters
	Node* right;//sex=0->female->1.isWife=1->wife->left is her husband's next wife, right is her children
								//2.isWife=0->daughter->left is NULL, right is her bros and siss
	//void PrintNodeInformation();
};

class FamilyTree
{
private:
	int size;
	int aliveSize;//assume today is 2019
	Node* root;

public:
	
	FamilyTree() {}
	~FamilyTree()
	{
		
	}
	ErrorCode creatTreeFromFile();//here to creat a tree from a file
	ErrorCode writeToFile();//write our tree to file
	ErrorCode insert(Node* newMember);
	Node* search(string name);
	ErrorCode PrintNodeInformation(Node* member);
	ErrorCode deleteMember(Node* member);

	//这里的方法是先在main里面search,返回到一个node* 再调用recorrect函数，在mian里面给switch代号,表示修改哪一部分
	ErrorCode recorrect(Node* member, int part);
	ErrorCode markDeath(Node* member);

	int countColorBlindness();
	int countAliveSize();
	int countFamilyTreeSize();
	int countAverageLifeSpan();//统计平均寿命

	friend void writeTree(ofstream ofile, Node* root);
	friend void searchTree(Node* root, Node* member, string name);//recursive function

};
