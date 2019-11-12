#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
enum ErrorCode { success, failure, overflow, underflow };

struct Node
{
	string name;
	bool sex;//sex=0->female  sex=1->male
	int generation;
	int lifeSpan;//2019-birthYear

	string motherName;
	string husbandName;

	bool isWife;//isWife=0->daughter  isWife=1->wife
	bool isDeadOrEx;

	int birthYear;


	int colorGene;// sex=0->female->0:AA,1:aa,2:Aa    sex=1->male->0:A,1:a
	int weight;

	Node* left;//2.isWife=0->daughter or son->left is husband/NULL, right is his/her bros and siss
	Node* right;//isWife=1->wife->left is her husband's next wife, right is her children

	//void PrintNodeInformation();
};

class FamilyTree
{
private:
	int size;
	int aliveSize;//assume today is 2019
	Node* root;

public:

	FamilyTree()
	{
		size = 0;
		aliveSize = 0;
		root = NULL;
	}
	~FamilyTree()
	{
		deleteMember(root);
	}

	ErrorCode creatTreeFromFile();//here to creat a tree from a file
	ErrorCode writeToFile();//write our tree to file
	ErrorCode insert(Node* newMember);
	Node* search(string name);//����õ���member�ĸ��ڵ�ָ��member��ָ�벻���޸�
	void search(string name, Node*& member);//����õ���member�ĸ��ڵ�ָ��member��ָ��Ҫ�޸�
	ErrorCode PrintNodeInformation(Node* member);
	ErrorCode deleteMember(Node*& member);

	//����ķ���������main����search,���ص�һ��node* �ٵ���recorrect��������mian�����switch����,��ʾ�޸���һ����,itemΪ�޸ĺ������
	ErrorCode recorrect(Node* member, int part, string item);
	ErrorCode recorrect(Node* member, int part, int item);
	ErrorCode markDeath(Node* member);

	int totalColorBlindness();
	float ColorBlindnessRate();
	int countAliveSize();
	int FamilyTreeSize()
	{
		return size;
	}
	int countAverageLifeSpan();//ͳ��ƽ������

	void display();

	friend void writeTree(FILE* fout, Node* root);
	friend void searchTree(Node* root, Node*& member, string name);//recursive function

};