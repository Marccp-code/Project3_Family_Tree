#include<iostream>
#include<string>
#include"FamilyTree.h"

using namespace std;

int main() {
	FamilyTree testcase;
	cout << "���ڽ��������ļ����������......" << endl;
	for (int i = 0; i < 1000000; i++) {

	}
	//չʾ�˵�
	if (testcase.creatTreeFromFile() != success) {
		cout << "����ʧ�ܣ��������������������" << endl;
		//system("pause");
		return 0;
	}
	cout << "�����Ѿ�������һ�ü��������˳�����" << endl;
	cout << "ÿ��һ������ʹ����Ϻ󣬲˵���������ʾ�����������Լ���ʹ����������" << endl << endl;
	while (1) {
		int i;
		int judge;
		string tempname = "��";
		Node *insertcase = new Node;
		Node *mymember;
		int generation;
		string name;
		string motherName;
		bool sex;
		int birthYear;
		int weight;
		int colorGene;
		cout << "************************************************�˵�************************************************" << endl << endl;
		cout << "1.��ʾ����            2.��ʾ��Ա��Ϣ            3.����³�Ա" << endl << endl;
		cout << "4.����ɫä���        5.�������������          6.�����������" << endl << endl;//ɫä������ɫä��//��������//�����ܺ���ƽ������
		cout << "7.����Ա���Ϊȥ��	   8.ɾ����Ա��������" << endl << endl;
		cout << "****************************************************************************************************" << endl << endl;
		cout << "����������ѡ��������õĹ���:";
		cin >> i;
		switch (i)
		{
		case 1:
			cout << "���������£�" << endl << endl;
			testcase.display();
			break;
		case 2:
			cout << "�����������ѯ�ĳ�Ա������" << endl << "***ע�⣬�����ϸ����ִ�Сд***" << endl;
			cin >> tempname;
			Node* toSearchGuy;
			while (1) {
				if (testcase.search(tempname) == NULL) {
					cout << "�Ҳ����ó�Ա����Ϣ�����������룡" << endl;
					cin >> tempname;
				}
				else {
					toSearchGuy = testcase.search(tempname);
					testcase.PrintNodeInformation(toSearchGuy);
					break;
				}
			}
			break;
		case 3:

			cout << "������ó�Ա��������Ϣ" << endl;
			cout << "*********************" << endl;
			cout << "������" << endl;
			cin >> generation;
			insertcase->generation = generation;
			cout << "���֣�" << endl;
			cin >> name;
			insertcase->name;
			cout << "ĸ��" << endl;
			cin >> motherName;
			insertcase->motherName = motherName;
			cout << "�Ա�" << endl;
			cin >> sex;
			insertcase->sex = sex;
			if (sex == 0) {
				cout << "�Ƿ�Ϊĳ�˵����ӣ������������1" << endl;
				cin >> judge;
				if (judge == 1) {
					insertcase->isWife = 1;
					cout << "�������ɷ������" << endl << "***ע�⣬�����ϸ����ִ�Сд***" << endl;
					cin >> tempname;
					insertcase->husbandName = tempname;
				}
			}
			cout << "���գ�" << endl;
			cin >> birthYear;
			insertcase->birthYear = birthYear;
			cout << "���أ�" << endl;
			cin >> weight;
			insertcase->weight = weight;
			cout << "����ɫä���������" << endl;
			cin >> colorGene;
			insertcase->colorGene = colorGene;
			insertcase->left = NULL;
			insertcase->right = NULL;
			cout << "*********************" << endl;
			if (testcase.insert(insertcase) == success) {
				int tempintnum;
				cout << "�����³�Ա�ɹ��������Ҫ������ʾ��������1�����������������ֻس��˳��˹���" << endl;
				cin >> tempintnum;
				if (tempintnum == 1) {
					testcase.display();
				}
			}
			break;
		case 4:
			cout << "�ü������ɫä����������£�" << endl;
			cout << "����ɫä��������Ϊ�� " << testcase.totalColorBlindness() << " ��" << endl;
			cout << "����ɫä������Ϊ�� " << testcase.ColorBlindnessRate() << "%" << endl;
			break;
		case 5:
			cout << "�������й��У� " << testcase.countAliveSize() << " ������" << endl;
			cout << "���У� " << testcase.size - testcase.countAliveSize() << " �˹���" << endl;
			break;
		case 6:
			cout << "�ü���ƽ������Ϊ�� " << testcase.countAverageLifeSpan() << " ��" << endl;
			break;
		case 7:
			cout << "������Ҫ���Ϊȥ���ļ����Ա�� " << endl;
			cin >> tempname;
			mymember = testcase.search(tempname);
			;
			if (testcase.markDeath(mymember) != success) {
				cout << "���ʧ�ܣ�" << endl;
			}
			else {
				cout << "��ǳɹ���" << endl;
			}
			break;
		case 8:
			cout << "������Ҫɾȥ�ļ����Ա�� " << endl;
			mymember = NULL;
			testcase.search(tempname, mymember);
			if (testcase.deleteMember(mymember) != success) {
				cout << "ɾ��ʧ�ܣ�" << endl;
			}
			else {
				cout << "ɾ���ɹ���" << endl;
			}
			break;
		default:
			break;
		}
	}
	//system("pause");
}