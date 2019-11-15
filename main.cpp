/*��Ŀ���������׹���ϵͳ���ö�����ʵ�����׵ı�ʾ��ʵ�ֲ���ɾ�����Ҹ�����ʾ
������ɫ���ܣ�ͳ�������������ǳ�Ա���� ��ƽ��������Ԥ��ɫä*/

//ͷ�ļ�����
#include<iostream>
#include<string>
#include"FamilyTree.h"

using namespace std;

int main() {
	FamilyTree testcase;//�����������
	int file_choice;
	cout << "********************************************�����ļ���ʽ********************************************" << endl << endl;
	cout << "1.ͨ��.txt�ļ�            2.ͨ��Excel(.csv)�ļ�" << endl << endl;
	cin >> file_choice;
	cout << "���ڽ��������ļ����������......" << endl;//��ʾ��
	if (file_choice == 1) {
		if (testcase.creatTreeFromFile() != success) //���ļ�����ԭ������ʧ��
		{
			cout << "����ʧ�ܣ��������������������" << endl;//��ʾ��

			return 0;//�˳�����
		}

		//��ʾ��ɹ������ִ��
		cout << "�����Ѿ�������һ�ü��������˳�����" << endl;
	}
	else {
		if (testcase.creatTreeFromExcel() != success) //���ļ�����ԭ������ʧ��
		{
			cout << "����ʧ�ܣ��������������������" << endl;//��ʾ��

			return 0;//�˳�����
		}

		//��ʾ��ɹ������ִ��
		cout << "�����Ѿ�������һ�ü��������˳�����" << endl;
	}
	cout << "ÿ��һ������ʹ����Ϻ󣬲˵���������ʾ�����������Լ���ʹ����������" << endl << endl;

	while (1)//�û��ظ�����ѡ�ֱ���˳�
	{
		int i;
		int judge;//�����ж��Ƿ�Ϊ���ӵ�����ı���
		string tempname = "��";//�û���������֣�Ĭ��Ϊ��

		Node* insertcase = new Node;//����һ����������Ľڵ㣬�����ڴ�
		Node* mymember;//���ò��ҹ��ܷ��صĽڵ�

		//����ʱ�û�����ĳ�Ա����
		int generation;
		string name;
		string motherName;
		bool sex;
		int birthYear;
		int weight;
		int colorGene;

		//�˵�չʾ
		cout << "************************************************�˵�************************************************" << endl << endl;
		cout << "1.��ʾ����               2.��ʾ��Ա��Ϣ               3.����³�Ա" << endl << endl;
		cout << "4.����ɫä���           5.�������������             6.�����������" << endl << endl;//ɫä������ɫä��//��������//�����ܺ���ƽ������
		cout << "7.����Ա���Ϊȥ��       8.ɾ����Ա��������           9.ɫäԤ�����" << endl << endl;
		cout << "10.���¼���д��txt�ļ�   11.���¼���д��Excel�ļ�     12.�˳�����" << endl << endl;
		cout << "****************************************************************************************************" << endl << endl;

		//����ѡ��
		cout << "����������ѡ��������õĹ���:";
		cin >> i;

		switch (i)//�жϹ���
		{
		case 1://չʾ
			cout << "���������£�" << endl << endl;
			testcase.display();
			break;
		case 2://����
			cout << "�����������ѯ�ĳ�Ա������" << endl << "***ע�⣬�����ϸ����ִ�Сд***" << endl;
			cin >> tempname;

			Node* toSearchGuy;

			while (1)
			{
				if (testcase.search(tempname) == NULL) //����ʧ��
				{
					cout << "�Ҳ����ó�Ա����Ϣ�����������룡" << endl;
					cin >> tempname;
				}
				else //�ɹ�
				{
					toSearchGuy = testcase.search(tempname);
					testcase.PrintNodeInformation(toSearchGuy);//��ӡ�ڵ���Ϣ
					break;
				}
			}
			break;
		case 3://���빦��
			cout << "������ó�Ա��������Ϣ" << endl;
			cout << "*********************" << endl;

			cout << "������" << endl;
			cin >> generation;
			insertcase->generation = generation;

			cout << "���֣�" << endl;
			cin >> name;
			insertcase->name = name;

			cout << "�Ա�(Ů����0,�������0���ּ���)��" << endl;
			cin >> sex;
			insertcase->sex = sex;



			if (sex == 0) {//Ů���ж�Ϊ���ӻ���Ů��
				cout << "�Ƿ�Ϊĳ�˵����ӣ������������1" << endl;
				cin >> judge;

				if (judge == 1) {//����
					insertcase->isWife = 1;
					while (1) {//�ҵ��ɷ�
						cout << "�������ɷ������" << endl << "***ע�⣬�����ϸ����ִ�Сд***" << endl;
						cin >> tempname;
						Node* search_husband = testcase.search(tempname);

						if (search_husband == NULL) {//���û���ɷ������
							cout << "û���ڼ��������ҵ����ˣ�����������!" << endl << endl;
						}
						else {
							insertcase->husbandName = tempname;
							break;
						}
					}
				}
				else {//ΪŮ��
					insertcase->isWife = 0;
				}
			}

			while (1)//����ĸ�����������insert������������ĸ�ײ����ڼ������У��������ӵ�ĸ��ֻҪ����һ����������
			{
				cout << "ĸ��" << endl;
				cin >> motherName;
				Node* search_mum = testcase.search(motherName);

				if (search_mum == NULL && insertcase->isWife != 1) //��û���ҵ�ĸ�������Ҳ�Ϊ����
				{
					cout << "û���ڼ��������ҵ����ˣ�����������!" << endl << endl;
				}
				else
				{
					insertcase->motherName = motherName;
					break;
				}
			}

			cout << "���գ�(0~2019)" << endl;
			cin >> birthYear;

			while (1)
			{
				if (birthYear > 2019 || birthYear < 0)//�������벻�Ϸ�
				{
					cout << "�������������밴�ո�ʽ���룡�ص����˵���";
					break;
				}
				else
				{
					insertcase->birthYear = birthYear;
					break;
				}
			}

			cout << "���أ�" << endl;
			cin >> weight;

			while (1)
			{
				if (weight > 3000 || weight < 0)//���ز��Ϸ�
				{
					cout << "�������������밴�ո�ʽ���룡�ص����˵���";
					break;
				}
				else
				{
					insertcase->weight = weight;
					break;
				}
			}

			cout << "����ɫä���������" << endl;
			cin >> colorGene;

			while (1)
			{
				if (colorGene > 2 || weight < 0)//ɫä���򲻺Ϸ�
				{
					cout << "�������������밴�ո�ʽ���룡�ص����˵���";
					break;
				}
				else
				{
					insertcase->colorGene = colorGene;
					break;
				}
			}

			insertcase->left = NULL;//�����������ΪNULL
			insertcase->right = NULL;
			cout << "*********************" << endl;

			if (testcase.insert(insertcase) == success) {//����ɹ�
				int tempintnum;
				cout << "�����³�Ա�ɹ��������Ҫ������ʾ��������1�����������������ֻس��˳��˹���" << endl;
				cin >> tempintnum;
				if (tempintnum == 1) {
					testcase.display();
				}
			}
			else {//����ʧ��
				cout << "���ʧ�ܣ������µ��ô˹��ܣ�" << endl;
			}
			break;
		case 4://չʾ����ɫä���
			cout << "�ü������ɫä����������£�" << endl;
			cout << "����ɫä��������Ϊ�� " << testcase.totalColorBlindness() << " ��" << endl;
			cout << "����ɫä������Ϊ�� " << testcase.ColorBlindnessRate() << "%" << endl;
			break;
		case 5://ͳ������������Ա���
			cout << "�������й��У� " << testcase.countAliveSize() << " ������" << endl;
			cout << "���У� " << testcase.size - testcase.countAliveSize() << " �˹���" << endl;
			break;
		case 6://ͳ��ƽ������
			cout << "�ü���ƽ������Ϊ�� " << testcase.countAverageLifeSpan() << " ��" << endl;
			break;
		case 7://��ǳ�Ա����
			cout << "������Ҫ���Ϊȥ���ļ����Ա�� " << endl;
			cin >> tempname;

			mymember = testcase.search(tempname);//�ҵ��ó�Ա

			if (mymember->isDeadOrEx == 1) {//����Ѿ�Ϊ����
				cout << "�ó�Ա�Ѿ������������ٱ�ǣ�" << endl;
				cout << "�����µ��ô˹��ܣ�" << endl;
				break;
			}

			if (testcase.markDeath(mymember) != success) {
				cout << "���ʧ�ܣ�" << endl;
			}
			else {
				cout << "��ǳɹ���" << endl;
			}

			break;
		case 8://ɾ���ڵ㼰������
			cout << "������Ҫɾȥ�ļ����Ա�� " << endl;
			cout << "********���ӻᱧ�����Ӳ���Ȣ�����Բ���ɾȥ����Ŷ����********" << endl;

			cin >> tempname;
			mymember = NULL;

			testcase.search(tempname, mymember);//���Ҹýڵ�

			if (testcase.deleteMember(mymember) != success) {//ɾ��ʧ��
				cout << "ɾ��ʧ�ܣ�" << endl;
			}
			else {
				cout << "ɾ���ɹ���" << endl;
			}
			break;
		case 9:
			//��ʾ��
			cout << "*********************************************" << endl;
			cout << "���������Ҹ�һ�����ҹ��ƻ������Ŀں�\n��ǰ�жϺ���������������ڼƻ�����������չ����Ϊ��ͥ���Ҹ����������ף�" << endl;
			cout << "*********************************************" << endl;

			cout << "�����뱾����Ԥ����󣨸�ĸ�����֣�" << endl;
			mymember = NULL;

			cin >> tempname;
			testcase.search(tempname, mymember);//���Ҹ�Ԥ��ڵ�

			if (mymember == NULL)//����ʧ��
			{
				cout << "û�д��ˣ��������˵���" << endl;
				continue;
			}
			else
			{
				cout << "��������ż�ĺ���ɫä�������ͣ�Ů�ԣ�0->AA   1->Aa  2->aa; ���ԣ�0->A  1->a)  :" << endl;
				int partner;
				cin >> partner;//��ż�������ͣ�������Ů
				string predication;//Ԥ�������

				if (mymember->sex == 0)//Ů��
				{
					switch (mymember->colorGene)
					{
					case 2://XaXa
						if (partner == 1)//XaY
							predication = "������100%����ΪɫäXaXa/XaY��";
						else if (partner == 0)//XAY
							predication = "	�к�����100%����ΪɫäXaY��Ů����ȫΪЯ����XAXa.";
						break;
					case 1://XAXa
						if (partner == 1)//XaY
							predication = "�к�50%����Ϊ����XAY��50%����Ϊɫä����XaY��Ů��50%����ΪЯ����XAXa��50%����Ϊɫä����XaXa";
						else if (partner == 0)//XAY
							predication = "	�к�50%����Ϊ����XAY��50%����Ϊɫä����XaY��Ů��50%����ΪЯ����XAXa��50%����Ϊ����XAXA.";
						break;
					case 0://XAXA
						if (partner == 1)//XaY
							predication = "�к���ȫΪ����XAY,Ů����ȫΪЯ����XAXa.";
						else if (partner == 0)//XAY
							predication = "	����ȫΪ������XAXA,XAY";
						break;
					}
				}
				else if (mymember->sex == 1)//����
				{
					switch (mymember->colorGene)
					{
					case 0://XAY
						if (partner == 0)//XAXA
							predication = "������100%����Ϊ�����ˡ�";
						else if (partner == 1)//XAXa
							predication = "	�к�����50%����ΪɫäXaY����50%����Ϊ����XAY��Ů����50%ΪЯ����XAXa��50%Ϊ����XAXA.";
						else if (partner == 2)//XaXa
							predication = "	�к�����100%����ΪɫäXaY��Ů����ȫΪЯ����XAXa.";
						break;
					case 1://XaY
						if (partner == 0)//XAXA
							predication = "�к���ȫΪ������XAY��Ů����ȫΪЯ����XAXa";
						else if (partner == 1)//XAXa
							predication = "	�к�����50%����ΪɫäXaY����50%����Ϊ����XAY��Ů����50%ΪЯ����XAXa��50%ΪɫäXaXa";
						else if (partner == 2)//XaXa
							predication = "	����ȫΪɫä����XaY/XaXa.";
						break;
					}
				}
				cout << predication << endl << endl;
			}
			break;
		case 10://д���ļ�
			if (testcase.writeToFile() != success) {
				cout << "д���ļ�ʧ�ܣ������µ��ô˹��ܣ�" << endl;
			}
			else {
				cout << "д���ļ��ɹ���" << endl;
			}
			break;
		case 11:
			if (testcase.writeToExcel() != success) {
				cout << "д��Excel�ļ�ʧ�ܣ������µ��ô˹��ܣ�" << endl;
			}
			else {
				cout << "д���ļ��ɹ���" << endl;
			}
			break;
			break;
		case 12://�˳�����
			cout << "��л��ʹ�ô˳���" << endl;
			system("pause");
			return 0;
		default://ѡ�����벻�Ϸ�
			cout << "������󣡣����������룡��" << endl;
			break;
		}
	}
	//system("pause");
}