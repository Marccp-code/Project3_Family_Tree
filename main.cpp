/*项目三——族谱管理系统，用二叉树实现族谱的表示，实现插入删除查找更改显示
还有特色功能，统计在世情况，标记成员死亡 ，平均寿命，预测色盲*/

//头文件部分
#include<iostream>
#include<string>
#include"FamilyTree.h"

using namespace std;

int main() {
	FamilyTree testcase;//族谱树类对象
	int file_choice;
	cout << "********************************************导入文件方式********************************************" << endl << endl;
	cout << "1.通过.txt文件            2.通过Excel(.csv)文件" << endl << endl;
	cin >> file_choice;
	cout << "正在将家谱树文件导入程序中......" << endl;//提示语
	if (file_choice == 1) {
		if (testcase.creatTreeFromFile() != success) //从文件读入原先族谱失败
		{
			cout << "导入失败，请输入任意键重启程序" << endl;//提示语

			return 0;//退出程序
		}

		//提示语，成功则继续执行
		cout << "我们已经导入了一棵家谱树到此程序中" << endl;
	}
	else {
		if (testcase.creatTreeFromExcel() != success) //从文件读入原先族谱失败
		{
			cout << "导入失败，请输入任意键重启程序" << endl;//提示语

			return 0;//退出程序
		}

		//提示语，成功则继续执行
		cout << "我们已经导入了一棵家谱树到此程序中" << endl;
	}
	cout << "每当一个功能使用完毕后，菜单会重新显示出来，您可以继续使用其他功能" << endl << endl;

	while (1)//用户重复输入选项，直到退出
	{
		int i;
		int judge;//用来判断是否为妻子的输入的变量
		string tempname = "无";//用户输入的名字，默认为无

		Node* insertcase = new Node;//创建一个用来插入的节点，申请内存
		Node* mymember;//调用查找功能返回的节点

		//插入时用户输入的成员参数
		int generation;
		string name;
		string motherName;
		bool sex;
		int birthYear;
		int weight;
		int colorGene;

		//菜单展示
		cout << "************************************************菜单************************************************" << endl << endl;
		cout << "1.显示该树               2.显示成员信息               3.添加新成员" << endl << endl;
		cout << "4.总体色盲情况           5.家谱中在世情况             6.家谱寿命情况" << endl << endl;//色盲人数与色盲率//在世人数//寿命总和与平均寿命
		cout << "7.将成员标记为去世       8.删除成员及其子树           9.色盲预测测试" << endl << endl;
		cout << "10.将新家谱写入txt文件   11.将新家谱写入Excel文件     12.退出程序" << endl << endl;
		cout << "****************************************************************************************************" << endl << endl;

		//输入选项
		cout << "请输入数字选择您想调用的功能:";
		cin >> i;

		switch (i)//判断功能
		{
		case 1://展示
			cout << "家谱树如下：" << endl << endl;
			testcase.display();
			break;
		case 2://查找
			cout << "请输入您想查询的成员的姓名" << endl << "***注意，我们严格区分大小写***" << endl;
			cin >> tempname;

			Node* toSearchGuy;

			while (1)
			{
				if (testcase.search(tempname) == NULL) //查找失败
				{
					cout << "找不到该成员的信息，请重新输入！" << endl;
					cin >> tempname;
				}
				else //成功
				{
					toSearchGuy = testcase.search(tempname);
					testcase.PrintNodeInformation(toSearchGuy);//打印节点信息
					break;
				}
			}
			break;
		case 3://插入功能
			cout << "请输入该成员的所有信息" << endl;
			cout << "*********************" << endl;

			cout << "代数：" << endl;
			cin >> generation;
			insertcase->generation = generation;

			cout << "名字：" << endl;
			cin >> name;
			insertcase->name = name;

			cout << "性别(女输入0,男输入非0数字即可)：" << endl;
			cin >> sex;
			insertcase->sex = sex;
				


			if (sex == 0) {//女性判断为妻子还是女儿
				cout << "是否为某人的妻子？如果是请输入1" << endl;
				cin >> judge;

				if (judge == 1) {//妻子
					insertcase->isWife = 1;
					while (1) {//找到丈夫
						cout << "请输入丈夫的姓名" << endl << "***注意，我们严格区分大小写***" << endl;
						cin >> tempname;
						Node* search_husband = testcase.search(tempname);

						if (search_husband == NULL) {//如果没有丈夫的名字
							cout << "没有在家谱树中找到该人！请重新输入!" << endl << endl;
						}
						else {
							insertcase->husbandName = tempname;
							break;
						}
					}
				}
				else {//为女儿
					insertcase->isWife = 0;
				}
			}

			while (1)//输入母亲姓名，如果insert对象是妻子则母亲不能在家谱树中，所以妻子的母亲只要输入一个姓名即可
			{
				cout << "母亲" << endl;
				cin >> motherName;
				Node* search_mum = testcase.search(motherName);

				if (search_mum == NULL && insertcase->isWife!=1) //若没有找到母亲名字且不为妻子
				{
					cout << "没有在家谱树中找到该人！请重新输入!" << endl << endl;
				}
				else
				{
					insertcase->motherName = motherName;
					break;
				}
			}

			cout << "生日：(0~2019)" << endl;
			cin >> birthYear;

			while (1)
			{
				if (birthYear > 2019 || birthYear < 0)//生日输入不合法
				{
					cout << "生日输入有误，请按照格式输入！回到主菜单。";
					break;
				}
				else
				{
					insertcase->birthYear = birthYear;
					break;
				}
			}

			cout << "体重：" << endl;
			cin >> weight;

			while (1)
			{
				if (weight > 3000 || weight < 0)//体重不合法
				{
					cout << "体重输入有误，请按照格式输入！回到主菜单。";
					break;
				}
				else
				{
					insertcase->weight = weight;
					break;
				}
			}

			cout << "红绿色盲基因情况：" << endl;
			cin >> colorGene;

			while (1)
			{
				if (colorGene > 2 || weight < 0)//色盲基因不合法
				{
					cout << "基因输入有误，请按照格式输入！回到主菜单。";
					break;
				}
				else
				{
					insertcase->colorGene = colorGene;
					break;
				}
			}

			insertcase->left = NULL;//左右子树标记为NULL
			insertcase->right = NULL;
			cout << "*********************" << endl;

			if (testcase.insert(insertcase) == success) {//插入成功
				int tempintnum;
				cout << "加入新成员成功！如果需要重新显示树请输入1，否则输入任意数字回车退出此功能" << endl;
				cin >> tempintnum;
				if (tempintnum == 1) {
					testcase.display();
				}
			}
			else {//插入失败
				cout << "添加失败，请重新调用此功能！" << endl;
			}
			break;
		case 4://展示红绿色盲情况
			cout << "该家族红绿色盲总体情况如下：" << endl;
			cout << "红绿色盲患者人数为： " << testcase.totalColorBlindness() << " 人" << endl;
			cout << "红绿色盲患病率为： " << testcase.ColorBlindnessRate() << "%" << endl;
			break;
		case 5://统计在世过世人员情况
			cout << "家谱树中共有： " << testcase.countAliveSize() << " 人在世" << endl;
			cout << "共有： " << testcase.size - testcase.countAliveSize() << " 人过世" << endl;
			break;
		case 6://统计平均寿命
			cout << "该家族平均寿命为： " << testcase.countAverageLifeSpan() << " 岁" << endl;
			break;
		case 7://标记成员死亡
			cout << "输入您要标记为去世的家族成员： " << endl;
			cin >> tempname;

			mymember = testcase.search(tempname);//找到该成员

			if (mymember->isDeadOrEx == 1) {//如果已经为死亡
				cout << "该成员已经死亡，不能再标记！" << endl;
				cout << "请重新调用此功能！" << endl;
				break;
			}

			if (testcase.markDeath(mymember) != success) {
				cout << "标记失败！" << endl;
			}
			else {
				cout << "标记成功！" << endl;
			}

			break;
		case 8://删除节点及其子树
			cout << "输入您要删去的家族成员： " << endl;
			cout << "********孩子会抱错，妻子不会娶错，所以不能删去妻子哦！！********" << endl;

			cin >> tempname;
			mymember = NULL;

			testcase.search(tempname, mymember);//查找该节点

			if (testcase.deleteMember(mymember) != success) {//删除失败
				cout << "删除失败！" << endl;
			}
			else {
				cout << "删除成功！" << endl;
			}
			break;
		case 9:
			//提示语
			cout << "*********************************************" << endl;
			cout << "少生优生幸福一生是我国计划生育的口号\n提前判断后代基因类型有助于计划生育工作的展开，为家庭的幸福美满做贡献！" << endl;
			cout << "*********************************************" << endl;

			cout << "请输入本家族预测对象（父母）名字：" << endl;
			mymember = NULL;

			cin >> tempname;
			testcase.search(tempname, mymember);//查找该预测节点

			if (mymember == NULL)//查找失败
			{
				cout << "没有此人！返回主菜单。" << endl;
				continue;
			}
			else
			{
				cout << "请输入配偶的红绿色盲基因类型（女性：0->AA   1->Aa  2->aa; 男性：0->A  1->a)  :" << endl;
				int partner;
				cin >> partner;//配偶基因类型，区分男女
				string predication;//预测结果语句

				if (mymember->sex == 0)//女性
				{
					switch (mymember->colorGene)
					{
					case 2://XaXa
						if (partner == 1)//XaY
							predication = "孩子有100%概率为色盲XaXa/XaY。";
						else if (partner == 0)//XAY
							predication = "	男孩子有100%概率为色盲XaY，女孩子全为携带者XAXa.";
						break;
					case 1://XAXa
						if (partner == 1)//XaY
							predication = "男孩50%概率为正常XAY，50%概率为色盲患者XaY；女孩50%概率为携带者XAXa，50%概率为色盲患者XaXa";
						else if (partner == 0)//XAY
							predication = "	男孩50%概率为正常XAY，50%概率为色盲患者XaY；女孩50%概率为携带者XAXa，50%概率为正常XAXA.";
						break;
					case 0://XAXA
						if (partner == 1)//XaY
							predication = "男孩子全为正常XAY,女孩子全为携带者XAXa.";
						else if (partner == 0)//XAY
							predication = "	孩子全为正常人XAXA,XAY";
						break;
					}
				}
				else if (mymember->sex == 1)//男性
				{
					switch (mymember->colorGene)
					{
					case 0://XAY
						if (partner == 0)//XAXA
							predication = "孩子有100%概率为正常人。";
						else if (partner == 1)//XAXa
							predication = "	男孩子有50%概率为色盲XaY，有50%概率为正常XAY；女孩子50%为携带者XAXa，50%为正常XAXA.";
						else if (partner == 2)//XaXa
							predication = "	男孩子有100%概率为色盲XaY，女孩子全为携带者XAXa.";
						break;
					case 1://XaY
						if (partner == 0)//XAXA
							predication = "男孩子全为正常人XAY；女孩子全为携带者XAXa";
						else if (partner == 1)//XAXa
							predication = "	男孩子有50%概率为色盲XaY，有50%概率为正常XAY；女孩子50%为携带者XAXa，50%为色盲XaXa";
						else if (partner == 2)//XaXa
							predication = "	孩子全为色盲患者XaY/XaXa.";
						break;
					}
				}
				cout << predication << endl << endl;
			}
			break;
		case 10://写入文件
			if (testcase.writeToFile() != success) {
				cout << "写入文件失败，请重新调用此功能！" << endl;
			}
			else {
				cout << "写入文件成功！" << endl;
			}
			break;
		case 11:
			if (testcase.writeToExcel() != success) {
				cout << "写入文件失败，请重新调用此功能！" << endl;
			}
			else {
				cout << "写入文件成功！" << endl;
			}
			break;
			break;
		case 12://退出程序
			cout << "感谢您使用此程序！" << endl;
			system("pause");
			return 0;
		default://选项输入不合法
			cout << "输入错误！！请重新输入！！" << endl;
			break;
		}
	}
	//system("pause");
}
