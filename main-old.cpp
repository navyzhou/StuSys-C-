#include "stuInfo.h"

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

        Account(string account, string pwd)
        {
            this -> account = account;
            this -> pwd = pwd;
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
        char sno[20];  // ѧ��
        char sname[20]; // ����
        char cname[20]; // �༶
        char sex[4]; // �Ա�
        int age; // ����
        char tel[15]; // �绰����

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
        void showCopy(); // ��ʾ��Ȩ
        bool login(); // �û���¼
        void menu(); // ���˵�
        void initData(); // ��ʼ������
        void addStuInfo(); // ���ѧ����Ϣ
        void showStuInfo(StuInfo stu); // ��ʾ����ѧ����Ϣ
        void searchStuInfo(); // ��ʾ���ѧ����Ϣ
        bool save(StuInfo stu); // ���浽�ļ�
        void viewStuInfo(); // ���ѧ����Ϣ
};

vector<StuInfo> stuInfos;

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
            initData(); // ��ȡ���е�ѧ����Ϣ
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
    fstream file(FILENAME, ios::in | ios::binary);
    if (file.is_open()) { // �򿪳ɹ�
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
        if ( save(stu) ) {
            stuInfos.push_back(stu);
            cout << "\n\tѧ����Ϣ��ӳɹ�..." << endl;
        } else {
            cout << "\n\tѧ����Ϣ���ʧ��..." << endl;
        }
    }
    cout << "\n\n\t<�밴�س�����>" << endl;
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
    cout << "\n\tѧ��" << "\t ����" << "\t   �༶" << "\t       �Ա�" << "\t����" << "\t    �绰" << endl;
    stu.show();
}

void Controller::viewStuInfo()
{
    system("cls");
    showCopy();
	cout << "\n\n\t**************************  ���ѧ����Ϣ  **************************" << endl;

    if (stuInfos.size() <= 0)
    {
        cout << "\n\t����ѧ����Ϣ...";
    }
    else
    {
        cout << "\n\n\t************************** ���� " << stuInfos.size() << " ��ѧ�� **************************" << endl;
        cout << "\n\n\tѧ��" << "\t ����" << "\t   �༶" << "\t        �Ա�" << "\t����" << "\t  �绰" << endl;
        for(int i=0,len=stuInfos.size(); i<len; i++)
        {
            stuInfos[i].show();
        }
    }
    cout << "\n\n\t<�밴�س�����>" << endl;
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
