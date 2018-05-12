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
    public:
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

        void show()
        {
            cout << "\n\t" << sno << "\t" << sname << "\t" << cname << "\t" << sex << "\t" << age << "\t" << tel << endl;
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
       /* case 4:update();break;
        case 5:removes();break;
        case 6:sal();break;
        case 7:exit(0);break;*/
    }
    goto again1;
}

void Controller::addStuInfo()
{
    system("cls");
    StuInfo stu;
    int result;

    cout << "\n\n\t**************************  添加学生信息  **************************";
	cout << "\n\n\t*************************请输入以下学生信息**************************\n";
	cout << "\n\t请输入学生学号：";
	cin >> stu.sno;

	cout << "\n\t请输入学生姓名：";
    cin >> stu.sname;

	cout << "\n\t请输入所在班级：";
	cin >> stu.cname;

	cout << "\n\t请输入学生性别：";
	cin >> stu.sex;

	cout << "\n\t请输入学生年龄：";
	cin >> stu.age;

	cout << "\n\t请输入联系方式：";
	cin >> stu.tel;

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

}

int main()
{
    Controller controll;
    if (controll.login() )
    {
        controll.menu();
    }
    return 0;
}
