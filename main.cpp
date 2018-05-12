#include "stuInfo.h"

using namespace std;

/* 账号类
class Account
{
    private:
        string account;  // 账号
        string pwd; // 密码
    public:
        Account()
        {
            account = "yc";
            pwd = "123";
        }

        Account(string account, string pwd)
        {
            this -> account = account;
            this -> pwd = pwd;
        }

        ~Account(); // 析构函数
        Account(string newAccount, string newPwd);
        void show();
        int login(string account, string pwd);  // 函数的声明
};

Account::Account(string newAccount, string newPwd){
    account = newAccount;
    pwd = newPwd;
}

void inline Account::show() // 显式声明的内联函数
{
    cout << account << "\t" << pwd << endl;
}
int Account::login(string account, string pwd)  // 成员函数的实现
{
}
*/

// 学生类
class StuInfo
{
    private:
        char sno[20];  // 学号
        char sname[20]; // 姓名
        char cname[20]; // 班级
        char sex[4]; // 性别
        int age; // 年龄
        char tel[15]; // 电话号码

    public:
        StuInfo()
        {

        }

        StuInfo(char sno[], char sname[], char cname[], char sex[], int age, char tel[])
        {
            setSno(sno);
            setSname(sname);
            setCname(cname);
            setSex(sex);
            setAge(age);
            setTel(tel);
        }

        void setSno(char sno[])
        {
            strcpy(this->sno,sno);
        }

        void setSname(char sname[])
        {
          strcpy(this->sname,sname);
        }

        void setCname(char cname[])
        {
            strcpy(this->cname,cname);
        }

        void setSex(char sex[])
        {
            strcpy(this->sex,sex);
        }

        void setAge(int age)
        {
            this->age = age;
        }

        void setTel(char tel[])
        {
            strcpy(this->tel,tel);
        }

        void show()
        {
            cout << "\n\t" << sno << "\t" << sname << "\t" << cname << "\t" << sex << "\t" << age << "\t" << tel << endl;
        }

        char* getSno()
        {
            return this->sno;
        }
};

class Controller
{
    public:
        void showCopy(); // 显示版权
        bool login(); // 用户登录
        void menu(); // 主菜单
        void initData(); // 初始化数据
        void addStuInfo(); // 添加学生信息
        void showStuInfo(StuInfo stu); // 显示单个学生信息
        void searchStuInfo(); // 显示多个学生信息
        bool save(StuInfo stu); // 保存到文件
        void viewStuInfo(); // 浏览学生信息
        void updateStuInfo(); // 修改学生信息
        void deleteStuInfo(); // 删除学生信息
        bool rewrite(); // 重写数据文件
};

vector<StuInfo> stuInfos;

//显示版权信息
void Controller::showCopy()
{
	cout << "\n\n\t**************************欢迎使用XXXX系统**************************";
	cout << "\n\n\t**************************源辰信息版权所有**************************";
}

bool Controller::login()  // 成员函数的实现
{
    system("cls");
    int index = 0, count = 0;
    string account;
    char pwd[20];
    char ch;
	showCopy();

	do{
	    index = 0;
        count ++;
        cout << "\n\n\t请输入您的账号:";
        //获取用户输入的账号
        cin >> account;

        cout << "\n\t请输入您的密码:";

        //获取用户输入的密码
        while( (ch = getch()) != 13 ){ //回车键的键值      //密码只能是数字和字母????
            if( ch == 8){ //Backspace  回退
                if(index<=0){
                    index=0;
                }else{
                    cout << "\b \b";
                    index--;
                }
            }else{
                pwd[index++] = ch;
                cout << '*';
            }
        }

        pwd[index]='\0'; //数组中数据结束的标志

        //判断用户输入的账号和密码是否正确
        if( account == "yc" && strcmp(pwd,"123") == 0){
            initData(); // 读取所有的学生信息
            return true;
        }else{
            if(count==3){
                cout << "\n\n\t对不起，您暂无权限，系统将自动退出....\n\t";
                exit(0);
            } else {
                cout << "\n\n\t账号或密码错误，请确认后重新输入<您还有 " << (3-count) << " 输入机会，回车后继续>!!!" << endl;
            }
        }
	}while(count > 0);

	return false;
}

void Controller::initData()
{
    fstream file(FILENAME, ios::in | ios::binary);
    if (file.is_open()) { // 打开成功
        StuInfo stu;
        while(true)
        {
            file.read((char *)&stu, sizeof(StuInfo));
            if(!file)
                break;
            stuInfos.push_back(stu);
        }
        file.close();
    }
}

void Controller::menu()
{
    int option=0, count=0;

again1:system("cls"); //清屏
    count=0;
    showCopy();
    cout << "\n\n\t**************************     主菜单     **************************\n";
    cout << "\n\t************************** 1.浏览学生信息 **************************";
    cout << "\n\t************************** 2.查询学生信息 **************************";
    cout << "\n\t************************** 3.添加学生信息 **************************";
    cout << "\n\t************************** 4.修改学生信息 **************************";
    cout << "\n\t************************** 5.删除学生信息 **************************";
    cout << "\n\t************************** 6.退出系统     **************************";

    do{
        if(count!=0){ //说明用户不是第一次输入，则提醒用户
            cout << "\n\n\t对不起，没有该选项，请重新选择(1-6):";
        }else{
            cout << "\n\n\t请选择您的操作(1-6):";
        }

        //获取用户的选择
        cin >> option;
        count++;
    }while(option<=0 || option>6);

    //如果用户输入了正确的值
    switch(option){
        case 1: viewStuInfo(); break;
        case 2: searchStuInfo(); break;
        case 3: addStuInfo(); break;
        case 4: updateStuInfo(); break;
        case 5: deleteStuInfo(); break;
        case 6: exit(0);break;
    }
    goto again1;
}

void Controller::addStuInfo()
{
    system("cls");
    int result;
    char sno[20];  // 学号
    char sname[20]; // 姓名
    char cname[20]; // 班级
    char sex[4]; // 性别
    int age; // 年龄
    char tel[15]; // 电话号码

    cout << "\n\n\t**************************  添加学生信息  **************************";
	cout << "\n\n\t*************************请输入以下学生信息**************************\n";

	cout << "\n\t请输入学生学号：";
	cin >> sno;

	cout << "\n\t请输入学生姓名：";
    cin >> sname;

	cout << "\n\t请输入所在班级：";
	cin >> cname;

	cout << "\n\t请输入学生性别：";
	cin >> sex;

	cout << "\n\t请输入学生年龄：";
	cin >> age;

	cout << "\n\t请输入联系方式：";
	cin >> tel;

	StuInfo stu(sno, sname, cname, sex, age, tel);

    cout << "\n\t您要添加的学生信息如下，请确认：" << endl;
	showStuInfo(stu);

	result=MessageBox(NULL,"您确定要添加此数据吗?","确认提示",MB_YESNO|MB_ICONWARNING);
    if(result==6)
    {
        if ( save(stu) ) {
            stuInfos.push_back(stu);
            cout << "\n\t学生信息添加成功..." << endl;
        } else {
            cout << "\n\t学生信息添加失败..." << endl;
        }
    }
    cout << "\n\n\t<请按回车返回>" << endl;
    getch();
}

bool Controller::save(StuInfo stu)
{
    fstream out(FILENAME,ios::out | ios::app | ios::binary);
    if (out.is_open())
    {
        out.write((char *)&stu, sizeof(StuInfo));
        out.close();
        return true;
    } else {
        return false;
    }
}

bool Controller::rewrite()
{
    int len=stuInfos.size();
    if (len <=0) // 说明没有学生信息，则清空文件中的内容
    {
        ofstream file(FILENAME, ios::out | ios::trunc);
        file.close();
    }
    else
    {
        fstream out(FILENAME,ios::out | ios::binary);
        if (out.is_open())
        {
            for(int i=0,len=stuInfos.size(); i<len; i++)
            {
                out.write((char *)&stuInfos[i], sizeof(StuInfo));
            }
            out.close();
            return true;
        } else {
            return false;
        }
    }

    return false;
}

void Controller::showStuInfo(StuInfo stu)
{
    cout << "\n\t学号" << "\t 姓名" << "\t   班级" << "\t       性别" << "\t年龄" << "\t    电话" << endl;
    stu.show();
}

void Controller::viewStuInfo()
{
    system("cls");
    showCopy();
	cout << "\n\n\t**************************  浏览学生信息  **************************" << endl;

    if (stuInfos.size() <= 0)
    {
        cout << "\n\t暂无学生信息...";
    }
    else
    {
        cout << "\n\n\t************************** 共有 " << stuInfos.size() << " 个学生 **************************" << endl;
        cout << "\n\n\t学号" << "\t 姓名" << "\t   班级" << "\t        性别" << "\t年龄" << "\t  电话" << endl;
        for(int i=0,len=stuInfos.size(); i<len; i++)
        {
            stuInfos[i].show();
        }
    }
    cout << "\n\n\t<请按回车返回>" << endl;
    getch();
}

void Controller::searchStuInfo()
{
	system("cls");

	showCopy();
	cout << "\n\n\t**************************  查询学生信息  **************************";
	if (stuInfos.size() <= 0)
    {
        cout << "\n\t暂无学生信息...";
    }
    else
    {
        char sno[20]; //存放用户要查找的商品编号
        cout << "\n\n\t请输入您要查询的学生学号：";
		cin >> sno;
        cout << "\n\n\t学号" << "\t 姓名" << "\t   班级" << "\t        性别" << "\t年龄" << "\t  电话" << endl;

        int count = 0; // 记录满足条件的学生个数
        int length = strlen(sno); // \0
        int temp = 0, j=0;
        char arr[20];

        for(int i=0,len=stuInfos.size(); i<len; i++)  // 循环所有学生信息
        {
            strcpy(arr,stuInfos[i].getSno());
            temp = strlen(arr);

            length = length > temp ? temp : length;
            /*if (strcmp(sno,stuInfos[i].getSno()) == 0)
            {
                count++;
                stuInfos[i].show();
            }*/
            for (j=0; j<length; j++)
            {
                if(arr[j] != sno[j])
                {
                    break;
                }
            }
            if (j >= length)  // 说明满足条件
            {
                count++;
                stuInfos[i].show();
            }
        }

        if (count>0)
        {
            cout << "\n\n\t************************ 共有 " << count << " 个基本满足条件 ************************" << endl;
        }
        else
        {
            cout << "\n\t没有您要查找的学生信息...";
        }

    }
    cout << "\n\n\t<请按回车返回>" << endl;
    getch();
}

void Controller::updateStuInfo()
{
    system("cls");

	showCopy();
	cout << "\n\n\t**************************  修改学生信息  **************************";
	if (stuInfos.empty())
    {
        cout << "\n\t暂无学生信息...";
    }
    else
    {
        char sno[20];  // 学号
        cout << "\n\n\t请输入您要修改的学生学号：";
		cin >> sno;
		//StuInfo stu;

		int i, len = stuInfos.size();

		for(i=0; i<len; i++)
		{
            if (strcmp(sno,stuInfos[i].getSno()) == 0)
            {
                cout << "\n\t您要输入的学生信息如下：";
                cout << "\n\n\t学号" << "\t 姓名" << "\t   班级" << "\t        性别" << "\t年龄" << "\t  电话" << endl;
                stuInfos[i].show();
                break;
            }
		}

		if ( i >= len )
		{
            cout << "\n\t对不起！没有您要删除的学生信息...";
		}
		else
		{
		    char sname[20]; // 姓名
            char cname[20]; // 班级
            char sex[4]; // 性别
            int age; // 年龄
            char tel[15]; // 电话号码

            cout << "\n\t请输入学生姓名：";
            cin >> sname;

            cout << "\n\t请输入所在班级：";
            cin >> cname;

            cout << "\n\t请输入学生性别：";
            cin >> sex;

            cout << "\n\t请输入学生年龄：";
            cin >> age;

            cout << "\n\t请输入联系方式：";
            cin >> tel;

		    int result=MessageBox(NULL,"您确定要修改此学生信息吗?","确认提示",MB_YESNO|MB_ICONWARNING);
            if(result==6) // 说明确定
            {
                stuInfos[i].setSname(sname);
                stuInfos[i].setCname(cname);
                stuInfos[i].setSex(sex);
                stuInfos[i].setAge(age);
                stuInfos[i].setTel(tel);

                //stuInfos[i].set = stu;


                // 重写数据文件
                if(rewrite())
                {
                   cout << "\n\n\t学生信息修改成功..." << endl;
                }
                else
                {
                    cout << "\n\n\t学生信息修改失败..." << endl;
                }
            }
		}
    }

    cout << "\n\n\t<请按回车返回>" << endl;
    getch();
}

void Controller::deleteStuInfo()
{
    system("cls");

	showCopy();
	cout << "\n\n\t**************************  删除学生信息  **************************";

    if (stuInfos.empty())
    {
        cout << "\n\t暂无学生信息...";
    }
    else
    {
        char sno[20]; //存放用户要查找的商品编号
        cout << "\n\n\t请输入您要删除的学生学号：";
		cin >> sno;

		int i, len = stuInfos.size();

		for(i=0; i<len; i++)
		{
            if (strcmp(sno,stuInfos[i].getSno()) == 0)
            {
                cout << "\n\n\t学号" << "\t 姓名" << "\t   班级" << "\t        性别" << "\t年龄" << "\t  电话" << endl;
                stuInfos[i].show();
                break;
            }
		}

		if (i>=len)
		{
            cout << "\n\t对不起！没有您要删除的学生信息...";
		}
		else
		{
            int result=MessageBox(NULL,"您确定要删除此学生信息吗?","确认提示",MB_YESNO|MB_ICONWARNING);
            if(result==6) // 说明确定
            {
                stuInfos.erase(stuInfos.begin()+i);
                // 重写数据文件
                if(rewrite())
                {
                   cout << "\n\n\t学生信息删除成功..." << endl;
                }
                else
                {
                    cout << "\n\n\t学生信息删除失败..." << endl;
                }
            }
        }
    }
    cout << "\n\n\t<请按回车返回>" << endl;
    getch();
}

int main()
{
    Controller controll;
    if (controll.login() )
    {
        controll.menu();
    } 
	else{
		cout << "\n\n\t对不起，您暂无权限，系统将自动退出....\n\t";
        exit(0);
	}
    return 0;
}
