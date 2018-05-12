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
    private:
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
        void showCopy(); // ��ʾ��Ȩ
        bool login(); // �û���¼
        void menu(); // ���˵�
        void initData(); // ��ʼ������
        void addStuInfo(); // ���ѧ����Ϣ
        void showStuInfo(StuInfo stu); // ��ʾ����ѧ����Ϣ
        void searchStuInfo(); // ��ʾ���ѧ����Ϣ
        bool save(StuInfo stu); // ���浽�ļ�
        void viewStuInfo(); // ���ѧ����Ϣ
        void updateStuInfo(); // �޸�ѧ����Ϣ
        void deleteStuInfo(); // ɾ��ѧ����Ϣ
        bool rewrite(); // ��д�����ļ�
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
    char sno[20];  // ѧ��
    char sname[20]; // ����
    char cname[20]; // �༶
    char sex[4]; // �Ա�
    int age; // ����
    char tel[15]; // �绰����

    cout << "\n\n\t**************************  ���ѧ����Ϣ  **************************";
	cout << "\n\n\t*************************����������ѧ����Ϣ**************************\n";

	cout << "\n\t������ѧ��ѧ�ţ�";
	cin >> sno;

	cout << "\n\t������ѧ��������";
    cin >> sname;

	cout << "\n\t���������ڰ༶��";
	cin >> cname;

	cout << "\n\t������ѧ���Ա�";
	cin >> sex;

	cout << "\n\t������ѧ�����䣺";
	cin >> age;

	cout << "\n\t��������ϵ��ʽ��";
	cin >> tel;

	StuInfo stu(sno, sname, cname, sex, age, tel);

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

bool Controller::rewrite()
{
    int len=stuInfos.size();
    if (len <=0) // ˵��û��ѧ����Ϣ��������ļ��е�����
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
	system("cls");

	showCopy();
	cout << "\n\n\t**************************  ��ѯѧ����Ϣ  **************************";
	if (stuInfos.size() <= 0)
    {
        cout << "\n\t����ѧ����Ϣ...";
    }
    else
    {
        char sno[20]; //����û�Ҫ���ҵ���Ʒ���
        cout << "\n\n\t��������Ҫ��ѯ��ѧ��ѧ�ţ�";
		cin >> sno;
        cout << "\n\n\tѧ��" << "\t ����" << "\t   �༶" << "\t        �Ա�" << "\t����" << "\t  �绰" << endl;

        int count = 0; // ��¼����������ѧ������
        int length = strlen(sno); // \0
        int temp = 0, j=0;
        char arr[20];

        for(int i=0,len=stuInfos.size(); i<len; i++)  // ѭ������ѧ����Ϣ
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
            if (j >= length)  // ˵����������
            {
                count++;
                stuInfos[i].show();
            }
        }

        if (count>0)
        {
            cout << "\n\n\t************************ ���� " << count << " �������������� ************************" << endl;
        }
        else
        {
            cout << "\n\tû����Ҫ���ҵ�ѧ����Ϣ...";
        }

    }
    cout << "\n\n\t<�밴�س�����>" << endl;
    getch();
}

void Controller::updateStuInfo()
{
    system("cls");

	showCopy();
	cout << "\n\n\t**************************  �޸�ѧ����Ϣ  **************************";
	if (stuInfos.empty())
    {
        cout << "\n\t����ѧ����Ϣ...";
    }
    else
    {
        char sno[20];  // ѧ��
        cout << "\n\n\t��������Ҫ�޸ĵ�ѧ��ѧ�ţ�";
		cin >> sno;
		//StuInfo stu;

		int i, len = stuInfos.size();

		for(i=0; i<len; i++)
		{
            if (strcmp(sno,stuInfos[i].getSno()) == 0)
            {
                cout << "\n\t��Ҫ�����ѧ����Ϣ���£�";
                cout << "\n\n\tѧ��" << "\t ����" << "\t   �༶" << "\t        �Ա�" << "\t����" << "\t  �绰" << endl;
                stuInfos[i].show();
                break;
            }
		}

		if ( i >= len )
		{
            cout << "\n\t�Բ���û����Ҫɾ����ѧ����Ϣ...";
		}
		else
		{
		    char sname[20]; // ����
            char cname[20]; // �༶
            char sex[4]; // �Ա�
            int age; // ����
            char tel[15]; // �绰����

            cout << "\n\t������ѧ��������";
            cin >> sname;

            cout << "\n\t���������ڰ༶��";
            cin >> cname;

            cout << "\n\t������ѧ���Ա�";
            cin >> sex;

            cout << "\n\t������ѧ�����䣺";
            cin >> age;

            cout << "\n\t��������ϵ��ʽ��";
            cin >> tel;

		    int result=MessageBox(NULL,"��ȷ��Ҫ�޸Ĵ�ѧ����Ϣ��?","ȷ����ʾ",MB_YESNO|MB_ICONWARNING);
            if(result==6) // ˵��ȷ��
            {
                stuInfos[i].setSname(sname);
                stuInfos[i].setCname(cname);
                stuInfos[i].setSex(sex);
                stuInfos[i].setAge(age);
                stuInfos[i].setTel(tel);

                //stuInfos[i].set = stu;


                // ��д�����ļ�
                if(rewrite())
                {
                   cout << "\n\n\tѧ����Ϣ�޸ĳɹ�..." << endl;
                }
                else
                {
                    cout << "\n\n\tѧ����Ϣ�޸�ʧ��..." << endl;
                }
            }
		}
    }

    cout << "\n\n\t<�밴�س�����>" << endl;
    getch();
}

void Controller::deleteStuInfo()
{
    system("cls");

	showCopy();
	cout << "\n\n\t**************************  ɾ��ѧ����Ϣ  **************************";

    if (stuInfos.empty())
    {
        cout << "\n\t����ѧ����Ϣ...";
    }
    else
    {
        char sno[20]; //����û�Ҫ���ҵ���Ʒ���
        cout << "\n\n\t��������Ҫɾ����ѧ��ѧ�ţ�";
		cin >> sno;

		int i, len = stuInfos.size();

		for(i=0; i<len; i++)
		{
            if (strcmp(sno,stuInfos[i].getSno()) == 0)
            {
                cout << "\n\n\tѧ��" << "\t ����" << "\t   �༶" << "\t        �Ա�" << "\t����" << "\t  �绰" << endl;
                stuInfos[i].show();
                break;
            }
		}

		if (i>=len)
		{
            cout << "\n\t�Բ���û����Ҫɾ����ѧ����Ϣ...";
		}
		else
		{
            int result=MessageBox(NULL,"��ȷ��Ҫɾ����ѧ����Ϣ��?","ȷ����ʾ",MB_YESNO|MB_ICONWARNING);
            if(result==6) // ˵��ȷ��
            {
                stuInfos.erase(stuInfos.begin()+i);
                // ��д�����ļ�
                if(rewrite())
                {
                   cout << "\n\n\tѧ����Ϣɾ���ɹ�..." << endl;
                }
                else
                {
                    cout << "\n\n\tѧ����Ϣɾ��ʧ��..." << endl;
                }
            }
        }
    }
    cout << "\n\n\t<�밴�س�����>" << endl;
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
		cout << "\n\n\t�Բ���������Ȩ�ޣ�ϵͳ���Զ��˳�....\n\t";
        exit(0);
	}
    return 0;
}
