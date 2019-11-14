/*结构体Node的声明，类FamilyTree的声明*/
#pragma once
//头文件部分
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
enum ErrorCode { success, failure, overflow, underflow };//错误码常量

struct Node//家庭成员节点声明
{
	string name;
	bool sex;//sex=0->female  sex=1->male
	int generation;
	int lifeSpan;//2019-birthYear

	string motherName;
	string husbandName;

	bool isWife;//isWife=0->女儿  isWife=1->妻子
	bool isDeadOrEx;

	int birthYear;//0~3000


	int colorGene;// sex=0->女性->0:XAXA,1:XAXa,2:XaXa    sex=1->男性->0:XAY,1:XaY
	int weight;//0~3000

	Node* left;//2.isWife=0->女儿或儿子->left is husband/NULL, right is his/her bros and siss
	Node* right;//isWife=1->妻子->left is her husband's next wife, right is her children

};

class FamilyTree//族谱树的类
{
private:
	int aliveSize;//活着的人的数量

public:
	int size;
	Node* root;//根节点

	FamilyTree()//构造函数
	{
		size = 0;
		aliveSize = 0;
		root = NULL;
	}
	~FamilyTree()//析构函数
	{
		deleteMember(root);
	}

	ErrorCode creatTreeFromExcel();
	ErrorCode writeToExcel();
	
	ErrorCode creatTreeFromFile();//从文件读入一棵树做家谱
	ErrorCode writeToFile();//把内存中的家谱树写进文件
	ErrorCode insert(Node* newMember);//插入新出生成员
	Node* search(string name);//如果得到的member的父节点指向member的指针不用修改
	void search(string name, Node*& member);//如果得到的member的父节点指向member的指针要修改
	ErrorCode PrintNodeInformation(Node* member);//打印节点信息
	ErrorCode deleteMember(Node*& member);//删除节点
	ErrorCode recorrect(Node* member, int part, string item);//修改节点信息string类
	ErrorCode recorrect(Node* member, int part, int item);//修改节点信息int类
	ErrorCode markDeath(Node* member);//标记死亡

	int totalColorBlindness();//统计色盲情况
	float ColorBlindnessRate();//色盲率
	int countAliveSize();//在世人数
	int FamilyTreeSize()//统计家谱规格
	{
		return size;
	}
	int countAverageLifeSpan();//统计平均寿命

	void display();//展示本家谱信息

	friend void writeTree(FILE* fout, Node* root);//友元函数写入文件递归
	friend void searchTree(Node* root, Node*& member, string name);//友元函数查找文件递归

};