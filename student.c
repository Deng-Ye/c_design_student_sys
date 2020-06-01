/*
file:student.c
By:1940706248_������
��Ƶ��ʾ��ַ��https://www.bilibili.com/video/BV1MV411d713/
2020/4/24
�����ļ���ο�:./db.sql
*/
#include<stdio.h>
#include "sqlserver.h"
#include<string.h>
#include<stdlib.h>
#include<windows.h>
struct student
{
	int id;
	int uid;
	char name[20];
	int chinese;
	int math;
	int english;
};
int main(void)//�������
{
	//����������
	struct student getStudentInfo(char* p, int num, int total);
	void student_input();
	void student_search();
	void student_update();
	void student_delete();
	void quit();
	void color(short x);
	int confirmWindow();
	void student_printAll();
	//���ݿ�����
	int res;
	res = sql_connect("sql_db", "sa", "123456");
	sql_query("USE student", 0,NULL);

	//���棺
	while (1)
	{
		int sel;
		system("cls");
		printf("*****ѧ���ɼ�����ϵͳ*****\n\n");
		printf("��ѡ�����¹�����:\n");
		printf("1.ѧ���ɼ���Ϣ����\n");
		printf("2.ѧ���ɼ���Ϣ��ѯ\n");
		printf("3.ѧ���ɼ���Ϣ����\n");
		printf("4.ѧ���ɼ���Ϣɾ��\n");
		printf("0.�˳�\n");
		printf("**************************\n");
		printf("��ѡ��0~4��");
		scanf_s("%d", &sel);
		switch (sel)
		{
		case 1:student_input(); break;
		case 2:student_search(); break;
		case 3:student_update(); break;
		case 4:student_delete(); break;
		case 0:quit(); break;
		default:
			system("cls");
			printf("��Ч����,2s�󷵻����˵�");
			Sleep(2000);
			break;
		}
	}
	
	
	

	
	
	

}
struct student getStudentInfo(char* p, int num,int total)
{
	struct student stu;
	stu.id = 0;
	if (num == NULL) num = 1;
	if(total >= num)
	{
	

		
		char temp[20];
		strncpy_s(&temp, 20, 120 * (num - 1)+p, 20);
		stu.id = atoi(temp);
		if (stu.id < 0)
		{	//����Ƿ�Ϊ��
			return stu;
		}
		strncpy_s(&temp, 20, 120*(num-1)+p+20, 20);
		stu.uid = atoi(temp);
		strncpy_s(&temp, 20, 120*(num - 1)+p + 40, 20);
		strncpy_s(stu.name, 20,temp,20);
		strncpy_s(&temp,20, 120*(num-1)+p + 60, 20);
		stu.chinese = atoi(temp);
		strncpy_s(&temp, 20, 120*(num-1)+p + 80, 20);
		stu.math = atoi(temp);
		strncpy_s(&temp, 20, 120*(num-1)+p + 100, 20);
		stu.english = atoi(temp);
		return stu;
	}
	return ;

}
void student_input()
{
	struct student stu;
	system("cls");
	printf("��������ͬѧ��ѧ��:");
	scanf_s("%d", &stu.uid);
	printf("��������ͬѧ������:");
	scanf_s("%s", stu.name,20);
	printf("��������ͬѧ�����ĳɼ�");
	scanf_s("%d", &stu.chinese);
	printf("��������ͬѧ����ѧ�ɼ�:");
	scanf_s("%d", &stu.math);
	printf("��������ͬѧ��Ӣ��ɼ�:");
	scanf_s("%d", &stu.english);

	if (stu.uid == 0 || stu.name == "")
	{
		
		printf("!ѧ�Ż�����������Ϊ��!\n");
	}

	//����ʹ���ַ������ӷ���������ȫ!!!
	char sql_[256] = "INSERT INTO stu_info (uid,name,chinese,math,english) VALUES ('";//�ǵ�������
	char temp[20];
	_itoa_s(stu.uid, &temp,20, 10);
	strcat_s(sql_,sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), "','");
	strcat_s(sql_, sizeof(sql_), stu.name);
	strcat_s(sql_, sizeof(sql_), "',");
	_itoa_s(stu.chinese, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ",");
	_itoa_s(stu.math, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ",");
	_itoa_s(stu.english, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ")");
	printf(sql_);

	color(4);
	printf("\n���ѧ��\n");
	color(7);
	printf("ѧ�ţ�%d,������%s,���ĳɼ���%d,��ѧ�ɼ�%d,Ӣ��ɼ�:%d\n", stu.uid, stu.name, stu.chinese, stu.math, stu.english);
	if (confirmWindow("�Ƿ�ȷ����Ӹ�ѧ��") != 0)
	{
		color(2);
		sql_query(sql_, 0,NULL);
		printf("��ӳɹ���3����Զ��������˵���\n");
		Sleep(3000);
		
	}
	else
	{
		color(4);
		printf("���ʧ��,3����Զ��������˵���\n");
		Sleep(3000);
	}







	
}
void student_search()
{
	//�����˵�
	int in;
	char msg[20];
	while(1)
	{
		system("cls");
		printf("*******�ɼ���ѯ*******\n");
		printf("1.��ѧ�Ų�ѯ\n");
		printf("2.��������ѯ\n");
		printf("3.��ʾ����ѧ��\n");
		printf("4.�������˵�\n");
		scanf_s("%d", &in);
		if (in == 3)
		{
			student_printAll();
			int flag[3];
			printf("��������������˵�!");
			getchar();
			getchar();

		}
		else if (in == 4)
		{
			break;
		}
		else
		{


			printf("��������Ҫ���ҵ�%s\n", in == 1 ? "ѧ��" : "����");
			scanf_s("%s", msg, 20);
			//SELECT* FROM stu_info WHERE uid = '19470606248'
			char sql_[256];
			if (in == 1)
			{
				strcpy_s(sql_, 256, "SELECT * FROM stu_info WHERE uid='");//�ַ���ƴ��
			}
			else if (in == 2)
			{
				strcpy_s(sql_, 256, "SELECT * FROM stu_info WHERE name='");//�ַ���ƴ��

			}


			strcat_s(sql_, sizeof(sql_), msg);
			strcat_s(sql_, sizeof(sql_), "'");
			//printf("%s", sql_);
			SQLCHAR* sum = sql_query(sql_, 1, NULL);
			struct student stu = getStudentInfo(sum, 1, 1);
			color(4);
			printf("��ѯ���:\n\n");
			color(7);
			if (stu.id > 0)
			{
				printf("ѧ��:%d,������%s,���ĳɼ�:%d,��ѧ�ɼ���%d,Ӣ��ɼ�:%d\n\n", stu.uid, stu.name, stu.chinese, stu.math, stu.english);

			}
			else
			{
				printf("��ѯʧ�ܣ��Ҳ�����ѧ��?\n\n");
			}
			if (confirmWindow("�Ƿ������ѯ") != 0)
			{
				//������ѯ
				student_search();
			}
			else
			{
				Sleep(2000);
				free(sum);
			}
		}
	}
	





	}
void student_update()
{
	student_printAll();
	printf("\n��������Ҫ�޸ĵķ�ʽ(1.����� 2.��ѧ�� 3.������)\n");
	int mode = 0;
	char str[10];
	char flag[10];
	//"UPDATE stu_info SET english = 100 WHERE name = '������'";
	char sql_[256] = "UPDATE stu_info SET ";
	char input[20],uid[20],name[20],math[20],chinese[20],english[20];
	int temp = 0;
	scanf_s("%d", &mode);
	
	switch (mode)
	{
	case 1:strcpy_s(str, 5, "���"); strcpy_s(flag, 10, "id"); break;
	case 2:strcpy_s(str, 5, "ѧ��"); strcpy_s(flag, 10, "uid"); break;
	case 3:strcpy_s(str, 5, "����"); strcpy_s(flag, 10, "name"); break;
	case 0:return;


		
	default:

		break;
	}
	color(10);
	printf("\n��������Ҫ�޸���Ϣ��ͬѧ��%s:", str);
	color(7);
	scanf_s("%s", &input, 20);
	color(10);
	printf("\n�������޸ĺ��ѧ��?����Ҫ�޸�(n):");
	color(7);
	scanf_s("%s", &uid, 20);
	color(10);
	printf("\n�������޸ĺ������?����Ҫ�޸�(n):");
	color(7);
	scanf_s("%s", &name, 20);
	color(10);
	printf("\n�������޸ĺ�����ĳɼ�?����Ҫ�޸�(n):");
	color(7);
	scanf_s("%s", &chinese, 20);
	color(10);
	printf("\n�������޸ĺ����ѧ�ɼ�?����Ҫ�޸�(n):");
	color(7);
	scanf_s("%s", &math, 20);
	color(10);
	printf("\n�������޸ĺ��Ӣ��ɼ�?����Ҫ�޸�(n):");
	color(7);
	scanf_s("%s", &english, 20);
	if (strcmp(uid, "n") != 0)
	{
		strcat_s(sql_, 256, " uid= '");
		strcat_s(sql_, 256, uid);
		strcat_s(sql_, 256, "'");
		temp = 1;
	}

	if (strcmp(name, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");

		}
		strcat_s(sql_, 256, " name ='");
		strcat_s(sql_, 256, name);
		strcat_s(sql_, 256, " '");
		temp = 1;
	}

	if (strcmp(chinese, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " chinese = ");
		strcat_s(sql_, 256, chinese);
		temp = 1;
	}

	if (strcmp(math, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " math = ");
		strcat_s(sql_, 256, math);
		temp = 1;
	}

	if (strcmp(english, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " english = ");
		strcat_s(sql_, 256, english);
	}
	
	strcat_s(sql_, 256, " WHERE ");
	strcat_s(sql_, 256, flag);
	strcat_s(sql_, 256, " = ");
	if (mode == 3 || mode == 2)
	{
		strcat_s(sql_, 256, "'");
		strcat_s(sql_, 256, input);
		strcat_s(sql_, 256, "'");

	}
	else
	{
		strcat_s(sql_, 256, input);

	}
	sql_query(sql_, 0, NULL);
	//printf("%s", sql_);
	printf("ִ���޸ĳɹ���3s�󷵻����˵�!\n");
	Sleep(3000);




}
void student_delete()
{
	student_printAll();
	printf("\n��������Ҫɾ���ķ�ʽ(1.����� 2.��ѧ�� 3.������)\n");
	int mode = 0;
	char str[10];
	char flag[10], input[20];
	//DELETE FROM stu_info WHERE name = '������';
	char sql_[256] = "DELETE FROM stu_info WHERE ";
	scanf_s("%d", &mode);

	switch (mode)
	{
	case 1:strcpy_s(str, 5, "���"); strcpy_s(flag, 10, "id"); break;
	case 2:strcpy_s(str, 5, "ѧ��"); strcpy_s(flag, 10, "uid"); break;
	case 3:strcpy_s(str, 5, "����"); strcpy_s(flag, 10, "name"); break;
	case 0:return;



	default:

		break;
	}
	color(10);
	printf("\n��������Ҫɾ����Ϣ��ͬѧ��%s:", str);
	color(7);
	scanf_s("%s", &input, 20);


	strcat_s(sql_, 256, flag);
	strcat_s(sql_, 256, " = ");

	if (mode == 3)
	{
		strcat_s(sql_, 256, "'");
		strcat_s(sql_, 256, input);
		strcat_s(sql_, 256, "'");

	}
	else
	{
		strcat_s(sql_, 256, input);

	}
	sql_query(sql_, 0, NULL);

	printf("ִ��ɾ���ɹ���3s�󷵻����˵�!\n");
	Sleep(3000);



}
void quit()
{
	sql_disconnect();
	exit(0);
}
void student_printAll()
{
	char sql_[256];

	strcpy_s(sql_, 256, "SELECT * FROM stu_info");//�ַ���ƴ��

	struct student stu;


	system("cls");
	int j = 0;
	SQLCHAR* sum = sql_query(sql_, 1,&j);
	for (int i = 0; i < j; i++)
	{
		stu = getStudentInfo(sum, i+1, j);
		if (stu.id > 0 && i == 0)//��һ��ѭ����ӡ����
		{
			printf("�����������Щ��������������������Щ������������Щ����������������������Щ����������������������Щ�����������������������\n");
			printf("����ũ� ѧ��     �� ���� �����ĳɼ�   ����ѧ�ɼ�   ��   Ӣ��ɼ���\n");
			printf("�����������੤�������������������੤�����������੤���������������������੤���������������������੤����������������������\n");
		}
		printf("��%4d��%-10d��%6s��%11d��%11d��%11d��\n", stu.id, stu.uid, stu.name, stu.chinese, stu.math, stu.english);

	}
	printf("�����������ة��������������������ة������������ة����������������������ة����������������������ة�����������������������\n");



	


}
//helper
void color(short x) //�Զ��庯���ݲ����ı���ɫ   
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //ֻ��һ���������ı�������ɫ   
	else//Ĭ�ϵ���ɫ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	/*
	����0=��ɫ                8=��ɫ���� 
  ��1=��ɫ                9=����ɫ        ʮ������        ����                         
����2=��ɫ                10=����ɫ       0xa        ���� 
����3=����ɫ              11=��ǳ��ɫ     0xb�� 
����4=��ɫ                12=����ɫ       0xc���� 
����5=��ɫ                13=����ɫ       0xd        ���� 
����6=��ɫ                14=����ɫ       0xe        ���� 
����7=��ɫ                15=����ɫ       0xf  
  */
}
int confirmWindow(char *msg)
{
	char isconfirm;
	color(5);
	printf("\n%s(y/n)",msg);
	getchar();//ȥ�����з�
	scanf_s("%c", &isconfirm,1);
	if (isconfirm == 'y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
