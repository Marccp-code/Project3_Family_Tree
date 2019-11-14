/*�ṹ��Node����������FamilyTree������*/
#pragma once
//ͷ�ļ�����
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
enum ErrorCode { success, failure, overflow, underflow };//�����볣��

struct Node//��ͥ��Ա�ڵ�����
{
	string name;
	bool sex;//sex=0->female  sex=1->male
	int generation;
	int lifeSpan;//2019-birthYear

	string motherName;
	string husbandName;

	bool isWife;//isWife=0->Ů��  isWife=1->����
	bool isDeadOrEx;

	int birthYear;//0~3000


	int colorGene;// sex=0->Ů��->0:XAXA,1:XAXa,2:XaXa    sex=1->����->0:XAY,1:XaY
	int weight;//0~3000

	Node* left;//2.isWife=0->Ů�������->left is husband/NULL, right is his/her bros and siss
	Node* right;//isWife=1->����->left is her husband's next wife, right is her children

};

class FamilyTree//����������
{
private:
	int aliveSize;//���ŵ��˵�����

public:
	int size;
	Node* root;//���ڵ�

	FamilyTree()//���캯��
	{
		size = 0;
		aliveSize = 0;
		root = NULL;
	}
	~FamilyTree()//��������
	{
		deleteMember(root);
	}

	ErrorCode creatTreeFromExcel();
	ErrorCode writeToExcel();
	
	ErrorCode creatTreeFromFile();//���ļ�����һ����������
	ErrorCode writeToFile();//���ڴ��еļ�����д���ļ�
	ErrorCode insert(Node* newMember);//�����³�����Ա
	Node* search(string name);//����õ���member�ĸ��ڵ�ָ��member��ָ�벻���޸�
	void search(string name, Node*& member);//����õ���member�ĸ��ڵ�ָ��member��ָ��Ҫ�޸�
	ErrorCode PrintNodeInformation(Node* member);//��ӡ�ڵ���Ϣ
	ErrorCode deleteMember(Node*& member);//ɾ���ڵ�
	ErrorCode recorrect(Node* member, int part, string item);//�޸Ľڵ���Ϣstring��
	ErrorCode recorrect(Node* member, int part, int item);//�޸Ľڵ���Ϣint��
	ErrorCode markDeath(Node* member);//�������

	int totalColorBlindness();//ͳ��ɫä���
	float ColorBlindnessRate();//ɫä��
	int countAliveSize();//��������
	int FamilyTreeSize()//ͳ�Ƽ��׹��
	{
		return size;
	}
	int countAverageLifeSpan();//ͳ��ƽ������

	void display();//չʾ��������Ϣ

	friend void writeTree(FILE* fout, Node* root);//��Ԫ����д���ļ��ݹ�
	friend void searchTree(Node* root, Node*& member, string name);//��Ԫ���������ļ��ݹ�

};