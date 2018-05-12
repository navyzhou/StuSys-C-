#include <iostream>
#include <string>
#include "windows.h"
#include <iostream>
#include <fstream>
#include "stuInfo.h"
#include <conio.h>

using namespace std;

/* �˺���
class Account
{
    private:
        string account;  // �˺�
        string pwd; // ����
    public:
        Account()
        {
            account = "yc";
            pwd = "123";
        }

        ~Account(); // ��������
        Account(string newAccount, string newPwd);
        void show();
        int login(string account, string pwd);  // ����������
};

Account::Account(string newAccount, string newPwd){
    account = newAccount;
    pwd = newPwd;
}

void inline Account::show() // ��ʽ��������������
{
    cout << account << "\t" << pwd << endl;
}
int Account::login(string account, string pwd)  // ��Ա������ʵ��
{
}
*/

// ѧ����
class StuInfo
{
    public:
        string sno;  // ѧ��
        string sname; // ����
        string cname; // �༶
        string sex; // �Ա�
        int age; // ����
        string tel; // �绰����

    public:
        StuInfo(string sno, string sname, string cname, string sex , int age, string tel)
        {
            this -> sno = sno;
            this -> sname = sname;
            this -> cname = cname;
            this -> sex = sex;
            this -> age = age;
            this -> tel = tel;
        }

        StuInfo()
        {

        }

        void show()
        {
            cout << "\n\t" << sno << "\t" << sname << "\t" << cname << "\t" << sex << "\t" << age << "\t" << tel << endl;
        }

        bool save()  // ���浽�����ļ�
        {
            ofstream out(FILENAME,ios::out | ios::app);
            if (out.is_open())
            {
                out << sno << "\t" << sname << "\t" << cname << "\t" << sex << "\t" << age << "\t" << tel << "\r\n";
                out.close();
                return true;
            } else {
                return false;
            }
        }
};

class Controller
{
    public:
        void showCopy(); // ��ʾ��Ȩ
        bool login(); // �û���¼
        void menu(); // ���˵�
        void initData(); // ��ʼ������
        void addStuInfo(); // ���ѧ����Ϣ
        void showStuInfo(StuInfo stu); // ��ʾ����ѧ����Ϣ
        void showStuInfos(StuInfo stus[]); // ��ʾ���ѧ����Ϣ
};

//��ʾ��Ȩ��Ϣ
void Controller::showCopy()
{
	cout << "\n\n\t**************************��ӭʹ��XXXXϵͳ**************************";
	cout << "\n\n\t**************************Դ����Ϣ��Ȩ����**************************";
}

bool Controller::login()  // ��Ա������ʵ��
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
        cout << "\n\n\t�����������˺�:";
        //��ȡ�û�������˺�
        cin >> account;

        cout << "\n\t��������������:";

        //��ȡ�û����������
        while( (ch = getch()) != 13 ){ //�س����ļ�ֵ      //����ֻ�������ֺ���ĸ????
            if( ch == 8){ //Backspace  ����
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

        pwd[index]='\0'; //���������ݽ����ı�־

        //�ж��û�������˺ź������Ƿ���ȷ
        if( account == "yc" && strcmp(pwd,"123") == 0){
            return true;
        }else{
            if(count==3){
                cout << "\n\n\t�Բ���������Ȩ�ޣ�ϵͳ���Զ��˳�....\n\t";
                exit(0);
            } else {
                cout << "\n\n\t�˺Ż����������ȷ�Ϻ���������<������ " << (3-count) << " ������ᣬ�س������>!!!" << endl;
            }
        }
	}while(count > 0);

	return false;
}

void Controller::initData()
{
    ofstream in(FILENAME);
    if (in.is_open) { // ����򿪳ɹ�

    }
}

void Controller::menu()
{
    int option=0, count=0;

again1:system("cls"); //����
    count=0;
    showCopy();
    cout << "\n\n\t**************************     ���˵�     **************************\n";
    cout << "\n\t************************** 1.���ѧ����Ϣ **************************";
    cout << "\n\t************************** 2.��ѯѧ����Ϣ **************************";
    cout << "\n\t************************** 3.���ѧ����Ϣ **************************";
    cout << "\n\t************************** 4.�޸�ѧ����Ϣ **************************";
    cout << "\n\t************************** 5.ɾ��ѧ����Ϣ **************************";
    cout << "\n\t************************** 6.�˳�ϵͳ     **************************";

    do{
        if(count!=0){ //˵���û����ǵ�һ�����룬�������û�
            cout << "\n\n\t�Բ���û�и�ѡ�������ѡ��(1-6):";
        }else{
            cout << "\n\n\t��ѡ�����Ĳ���(1-6):";
        }

        //��ȡ�û���ѡ��
        cin >> option;
        count++;
    }while(option<=0 || option>6);

    //����û���������ȷ��ֵ
    switch(option){
        /*case 1:view();break;
        case 2:search();break;*/
        case 3: addStuInfo();break;
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

    cout << "\n\n\t**************************  ���ѧ����Ϣ  **************************";
	cout << "\n\n\t*************************����������ѧ����Ϣ**************************\n";
	cout << "\n\t������ѧ��ѧ�ţ�";
	cin >> stu.sno;

	cout << "\n\t������ѧ��������";
    cin >> stu.sname;

	cout << "\n\t���������ڰ༶��";
	cin >> stu.cname;

	cout << "\n\t������ѧ���Ա�";
	cin >> stu.sex;

	cout << "\n\t������ѧ�����䣺";
	cin >> stu.age;

	cout << "\n\t��������ϵ��ʽ��";
	cin >> stu.tel;

    cout << "\n\t��Ҫ��ӵ�ѧ����Ϣ���£���ȷ�ϣ�" << endl;
	showStuInfo(stu);

	result=MessageBox(NULL,"��ȷ��Ҫ��Ӵ�������?","ȷ����ʾ",MB_YESNO|MB_ICONWARNING);
    if(result==6)
    {
        if ( stu.save() ) {
            cout << "\n\tѧ����Ϣ��ӳɹ�..." << endl;
        } else {
            cout << "\n\tѧ����Ϣ���ʧ��..." << endl;
        }
    }
    getch();
    getch();
}

void Controller::showStuInfo(StuInfo stu)
{
    cout << "\n\tѧ��" << "\t   ����" << "\t  �༶" << "\t   �Ա�" << "\t   ����" << "\t   �绰" << endl;
    stu.show();
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
