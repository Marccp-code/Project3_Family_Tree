//ͷ�ļ�����
#include"FamilyTree.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

//����ʵ��
void writeTree(FILE* fout, Node* root)//д���ļ��ݹ麯��
{
	if (root == NULL)//��������
	{
		return;
	}
	else
	{
		//��ʽ�������д��txt�ı��ļ�
		fprintf(fout, "%-12s%-15d%-25d%-20d%-25s%-31s%-15d%-17d%-25d%-28d%-21d\n", root->name.c_str(), root->sex, root->generation, root->lifeSpan, root->motherName.c_str(), root->husbandName.c_str(), root->isWife, root->isDeadOrEx, root->birthYear, root->colorGene, root->weight);//name
		//д��������
		writeTree(fout, root->left);
		//д��������
		writeTree(fout, root->right);

	}
}
void writeExcel(FILE* fout, Node* root)//д��Excel�ļ��ݹ麯��
{
	if (root == NULL)//��������
	{
		return;
	}
	else
	{
		//��ʽ�������д��excel�ļ��м��ԣ�����
		fprintf(fout, "%s%s%d%s%d%s%d%s%s%s%s%s%d%s%d%s%d%s%d%s%d\n", root->name.c_str(), ",", root->sex, ",", root->generation, ",", root->lifeSpan, ",", root->motherName.c_str(), ",", root->husbandName.c_str(), ",", root->isWife, ",", root->isDeadOrEx, ",", root->birthYear, ",", root->colorGene, ",", root->weight);//name
		//д��������
		writeExcel(fout, root->left);
		//д��������
		writeExcel(fout, root->right);

	}
}
ErrorCode FamilyTree::writeToFile()
{
	FILE* fout;

	fopen_s(&fout, "FamilyTreeOutput.txt", "w+");//д��ģʽ���ļ�

	if (fout == NULL)//��ʧ��
	{
		cout << "�ļ����ܴ�" << endl;
		return failure;
	}
	else
	{
		//д���ͷ
		fprintf(fout, "name	sex	generation         lifeSpan        motherName    husbandName               isWife    isDead    birthYear             colorGene                weight\n");
		//���õݹ�д�뺯��
		writeTree(fout, root);
	}

	fclose(fout);//�ر��ļ�

	return success;
}
ErrorCode FamilyTree::writeToExcel()
{
	FILE* fout;

	fopen_s(&fout, "FamilyTreeOutput.csv", "w+");//д��ģʽ���ļ�

	if (fout == NULL)//��ʧ��
	{
		cout << "�ļ����ܴ�" << endl;
		return failure;
	}
	else
	{
		//д���ͷ
		fprintf(fout, "name,sex,generation,lifeSpan,motherName,husbandName,isWife,isDead,birthYear,colorGene,weight\n");
		//���õݹ�д�뺯��
		writeExcel(fout, root);
	}

	fclose(fout);//�ر��ļ�

	return success;
}
ErrorCode FamilyTree::creatTreeFromFile()
{
	ifstream fin;
	fin.open("FamilyTreeInput.txt", ios::in);//��ȡ��ʽ���ļ�

	if (!fin.is_open())//��ʧ��
	{
		cout << "�ļ����ܴ�" << endl;
		return failure;
	}
	else//�򿪳ɹ�
	{
		string sexName;
		char buffer[200];

		fin.getline(buffer, 190);

		while (!fin.eof())//ѭ������
		{
			Node* newMember = new Node;

			//��������������ڵ�
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

			insert(newMember);//���빹���õĽڵ�
		}


		fin.close();//�ر��ļ�
		return success;
	}
}
ErrorCode FamilyTree::creatTreeFromExcel()//��excel��񴴽�������
{
	ifstream fin;
	fin.open("FamilyTreeInput.csv", ios::in);//��ȡ��ʽ���ļ�

	if (!fin.is_open())//��ʧ��
	{
		cout << "�ļ����ܴ�" << endl;
		return failure;
	}
	else//�򿪳ɹ�
	{
		string temp;
		getline(fin, temp);

		while (!fin.eof())//ѭ������
		{
			Node* newMember = new Node;

			//��������������ڵ�
			getline(fin, temp);
			char* token;
			char s[2] = ",";
			string information[11];
			int count = 0;

			/* ��ȡ��һ�����ַ��� */
			token = strtok((char*)temp.c_str(), s);

			/* ������ȡ���������ַ��� */
			while (token != NULL) {
				//cout << token << endl;
				information[count++] = token;
				token = strtok(NULL, s);
			}
			newMember->name = information[0];
			newMember->sex = (information[1][0] == 'M') ? 1 : 0;//sex=0->female  sex=1->male
			newMember->generation = atoi(information[2].c_str());
			newMember->lifeSpan = atoi(information[3].c_str());//2019-birthYear

			newMember->motherName = information[4];
			newMember->husbandName = information[5];

			newMember->isWife = atoi(information[6].c_str());//isWife=0->Ů��  isWife=1->����
			newMember->isDeadOrEx = atoi(information[7].c_str());

			newMember->birthYear = atoi(information[8].c_str());//0~3000


			newMember->colorGene = atoi(information[9].c_str());// sex=0->Ů��->0:XAXA,1:XAXa,2:XaXa    sex=1->����->0:XAY,1:XaY
			newMember->weight = atoi(information[10].c_str());//0~3000
			newMember->left = NULL;
			newMember->right = NULL;

			insert(newMember);//���빹���õĽڵ�
		}


		fin.close();//�ر��ļ�
		return success;
	}
}
void searchTree(Node* root, Node*& member, string name)//�ݹ�������Ա
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

Node* FamilyTree::search(string name)//���Ҳ����ؽڵ�
{
	Node* member = NULL;
	searchTree(root, member, name);
	return member;
}
void FamilyTree::search(string name, Node*& member)//���Ҳ��ѽ�������ڵ����
{
	member = NULL;
	searchTree(root, member, name);
}
ErrorCode FamilyTree::insert(Node* newMember)//���벢���سɹ����
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
void deleteTree(Node* root, int* countPtr)//�ݹ�ɾ����
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
ErrorCode FamilyTree::deleteMember(Node*& member)//ɾ���ڵ�
{
	if (member == NULL)//�޴���
	{
		return failure;
	}
	else
	{
		int count = 0;
		int* countPtr = &count;

		Node* tempnode = search(member->motherName);//�ҵ�ĸ�׻������
		deleteTree(member, countPtr);
		if (tempnode != NULL)
			tempnode->right = NULL;//��ĸ�ף������磩�����������ΪNULL

		size -= count;
	}
	return success;
}
ErrorCode FamilyTree::PrintNodeInformation(Node* member)//��ӡ�ڵ���Ϣ
{
	if (member == NULL)
	{
		return failure;
	}
	else
	{
		cout << "*********************" << endl;
		cout << "��������" << member->generation << "��" << endl;
		cout << "���֣�" << member->name << endl;
		cout << "�Ա�";//<< (member->sex == 1) ? "��" : "Ů"
		if (member->sex == 1) {
			cout << "��";
		}
		else {
			cout << "Ů";
		}
		cout << endl;

		cout << "���գ�" << member->birthYear << "��" << endl;
		cout << "���أ�" << member->weight << " kg" << endl;

		cout << "����ɫä���������";//��Ϊ��Ů
		if (member->sex == 1) {
			if (member->colorGene == 1) {
				cout << "XaY���Ǻ���ɫä����" << endl;
			}
			else {
				cout << "XAY�����Ǻ���ɫä����" << endl;
			}
		}
		else {
			if (member->colorGene == 1) {
				cout << "XaXa���Ǻ���ɫä����" << endl;
			}
			else if (member->colorGene == 2) {
				cout << "XAXa�����Ǻ���ɫä����" << endl;
			}
			else {
				cout << "XAXA�����Ǻ���ɫä����" << endl;
			}
		}
		cout << "����ɫä���������" << member->colorGene << endl; // sex=0->female->0:AA,1:aa,2:Aa    sex=1->male->0:A,1:a
		cout << "*********************" << endl;
		return success;
	}
}
ErrorCode FamilyTree::markDeath(Node* member)//�������
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

ErrorCode FamilyTree::recorrect(Node* member, int part, string item)//���Ľڵ�string��Ϣ
{
	switch (part)//���ĵĲ���
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

ErrorCode FamilyTree::recorrect(Node* member, int part, int item)//���Ľڵ�int��Ϣ
{
	switch (part)//���Ĳ���
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

int FamilyTree::countAliveSize()//ͳ��������Ŀ
{
	return this->aliveSize;
}
void countTotalLife(Node* root, int* totalLifeSpan)//ͳ����������������
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
int FamilyTree::countAverageLifeSpan()//ͳ��ƽ��������Ϊ�������˵������ܺͳ�������������
{
	int i = 0;
	int alredyDeadSize = size - aliveSize;

	int* totalLifeSpan = &i;

	countTotalLife(root, totalLifeSpan);
	return (*totalLifeSpan) / alredyDeadSize;
}
void countColorBlindness(Node* root, int* countPtr)//������ɫä�����ݹ麯��
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (root->colorGene == 1)
		{
			(*countPtr)++;
		}
		countColorBlindness(root->left, countPtr);
		countColorBlindness(root->right, countPtr);


	}
}
int FamilyTree::totalColorBlindness()//������ɫä����
{
	int count = 0;
	int* countPtr = &count;
	countColorBlindness(root, countPtr);
	return count;
}
float FamilyTree::ColorBlindnessRate()//ɫä��
{
	return totalColorBlindness() / size;
}


void printTree(Node* root)//��ӡ������
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
void FamilyTree::display()//չʾ������
{
	printTree(root);
}