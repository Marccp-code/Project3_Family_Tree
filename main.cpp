#include<iostream>
#include<string>
#include"FamilyTree.h"

using namespace std;

int main() {
	FamilyTree testcase;
	cout<<"正在将家谱树文件导入程序中......"<<endl;
	for (int i = 0; i < 1000000; i++) {
		
	}
	//展示菜单
	if (testcase.creatTreeFromFile() != success) {
		cout << "导入失败，请输入任意键重启程序" << endl;
		system("pause");
		return 0;
	}
	cout << "我们已经导入了一棵家谱树到此程序中" << endl ;
	cout << "每当一个功能使用完毕后，菜单会重新显示出来，您可以继续使用其他功能" << endl << endl;
	while (1) {
		int i;
		string tempname;
		Node *insertcase;
		Node *mymember;
		cout << "************************菜单************************" << endl << endl;
		cout << "1.显示该树            2.显示成员信息            3.添加新成员" << endl << endl;
		cout << "4.总体色盲情况        5.家谱中在世情况          6.家谱寿命情况" << endl << endl;//色盲人数与色盲率//在世人数//寿命总和与平均寿命
		cout << "7.将成员标记为去世	   8.删除成员及其子树" << endl << endl;
		cout << "****************************************************" << endl << endl;
		cout << "请输入数字选择您想调用的功能:" ;
		cin >> i;
		switch (i)
		{
		case 1:
			cout << "家谱树如下："<<endl<<endl;
			testcase.display();
			break;
		case 2:
			cout << "请输入您想查询的成员的姓名"<<endl<<"***注意，我们严格区分大小写***" << endl;
			cin >> tempname;
			Node* toSearchGuy;
			while (1) {
				if (testcase.search(tempname) == NULL) {
					cout << "找不到该成员的信息，请重新输入！" << endl;
				}
				else {
					toSearchGuy = testcase.search(tempname);
					testcase.PrintNodeInformation(toSearchGuy);
				}
			}
			break;
		case 3:
			cout<<"请输入该成员的所有信息"<<endl; 
			cout << "*********************" << endl;
			cout << "代数：" << endl; cin >> insertcase->generation;
			cout << "名字：" << endl; cin >> insertcase->name;
			cout << "母亲" << endl; cin >> insertcase->motherName;
			cout << "性别：" << endl; cin >> insertcase->sex;
			cout << "生日：" << endl; cin >> insertcase->birthYear;
			cout << "体重：" << endl; cin >> insertcase->weight;
			cout << "红绿色盲基因情况：" << endl; cin >> insertcase->colorGene;
			cout << "*********************" << endl;
			if (testcase.insert(insertcase) == success) {
				int tempintnum;
				cout << "加入新成员成功！如果需要重新显示树请输入1，否则输入任意数字回车退出此功能" << endl;
				cin >> tempintnum;
				if (tempintnum == 1) {
					testcase.display();
				}
			}
			break;
		case 4:
			cout << "该家族红绿色盲总体情况如下：" << endl;
			cout << "红绿色盲患者人数为： "<<testcase.totalColorBlindness() <<" 人"<< endl;
			cout << "红绿色盲患病率为： " << testcase.ColorBlindnessRate() << "%" << endl;
			break;
		case 5:
			cout << "家谱树中共有： " << testcase.countAliveSize() << " 人在世" << endl;
			cout << "共有： " << testcase.size-testcase.countAliveSize() << " 人过世" << endl;
			break;
		case 6:
			cout << "该家族平均寿命为： " << testcase.countAverageLifeSpan << " 岁" << endl;
			break;
		case 7:
			cout << "输入您要标记为去世的家族成员： " <<endl;
			cin >> tempname;
			mymember = testcase.search(tempname);
			;
			if (testcase.markDeath(mymember) != success) {
				cout << "标记失败！" << endl;
			}
			else {
				cout << "标记成功！" << endl;
			}
			break;
		case 8:
			cout << "输入您要删去的家族成员： " << endl;
			mymember = NULL;
			testcase.search(tempname, mymember);
			if (testcase.deleteMember(mymember) != success) {
				cout << "删除失败！" << endl;
			}
			else {
				cout << "删除成功！" << endl;
			}
			break;
		default:
			break;
		}
	}
	system("pause");
}