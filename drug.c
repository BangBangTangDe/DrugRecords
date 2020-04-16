#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define TOTALDRUGS 10000 //10000种药品
#define MAXSIZE 10 // 10种包装

int nrofDrug = 0; //药品数量
// 包装尺寸的结构体
struct Data {
	int size;
	int stock;
};
// 药品
//  fscanf(fp,"%s,%s",a,b);
struct Drugs {
	char name[20];
	struct Data inventory[MAXSIZE];
	int kind;
};
typedef struct Drugs Drugs;
Drugs mydrug[TOTALDRUGS];//全局变量
//函数定义
void menu();
void readfp();
void searchdrug();
void showdrugs();
int getkind(char s[], int *a);
int readFile(char filename[], Drugs *drug);
void writeToFile(char filename, struct Drugs *drug, int i);
int Sub_Exist(char a[], char b[]);
int main() {
	int ch;

	while (1)
	{
		menu();
		scanf("%d",&ch);
		if (ch == 1)readfp();
		else if (ch == 2) showdrugs();
		else if (ch == 3)searchdrug();
		else if (ch == 0)break;
		else if (ch == 4)system("cls");
		else {
			printf("输入错误！\n");
		}
	}



	return 0;
}

//菜单
void menu()
{
	printf("****************药品库存管理******************\n");
	printf("1.读入文件\n");
	printf("2.打印所有药品在屏幕上\n");
	printf("3.搜索药品\n");
	printf("4.清屏\n");
	printf("0.退出程序\n");
}
void readfp()
{
	char fname[30];
	char s[5] = ".txt";
	printf("输入读取的文件名称:");
	scanf("%s", fname);
	strcat(fname, s);

	if (readFile(fname, mydrug) == -1)
	{
		system("cls");
		printf("提示：读取出错!\n");
	}
	else
	{
		system("cls");
		printf("提示：读取文件成功！\n");

	}

}
void searchdrug()
{
	char ch;
	char drugname[20];
	int k = 0;
	int cnt1 = 0;
	int flag = 0;//标志
	printf("**************药物搜索************\n");
	printf("\t\t1.精确查找\n");
	printf("\t\t2.模糊查找\n");
	printf("\t\t3.其他退出\n");
	printf("请输入：\n");
	rewind(stdin);
	scanf("%c", &ch);
	if (ch == '1')
	{
		printf("输入药品名称:");
		scanf("%s", drugname);
		for (int i = 0; i < nrofDrug; i++)
		{
			if (strcmp(drugname, mydrug[i].name) == 0)
			{
				if (!flag)
				{
					printf("drugname\t\tsize\t\tstock\n");
					flag = 1;
				}
				cnt1++;
				printf("%s\t\t\t", mydrug[i].name);
				k = mydrug[i].kind;
				for (int i = 0; i < k; i++)
				{
					printf("%d ", mydrug[i].inventory[i].size);
				}
				printf("\t\t");
				for (int i = 0; i < k; i++)
				{
					printf("%d ", mydrug[i].inventory[i].stock);
				}
				printf("\n");
			}
		}
		if (!cnt1)
		{
			printf("\n\t\t搜索记录为空!!!\n");

		}
	}
	else if (ch == '2')
	{
		printf("输入药品名称:");
		scanf("%s", drugname);
		for (int i = 0; i < nrofDrug; i++)
		{
			if (Sub_Exist(mydrug[i].name, drugname) != -1)
			{
				if (!flag)
				{
					printf("drugname\t\tsize\t\tstock\n");
					flag = 1;
				}
				cnt1++;
				printf("%s\t\t\t", mydrug[i].name);
				k = mydrug[i].kind;
				for (int i = 0; i < k; i++)
				{
					printf("%d ", mydrug[i].inventory[i].size);
				}
				printf("\t\t");
				for (int i = 0; i < k; i++)
				{
					printf("%d ", mydrug[i].inventory[i].stock);
				}
				printf("\n");
			}
		}
		if (!cnt1)
		{
			printf("\n\t\t搜索记录为空!!!\n");

		}
	}
	else
	{
		system("cls");
	}



}
void showdrugs()
{
	int cnt = 0;
	int k = 0;
	printf("drugname\t\tsize\t\tstock\n");
	while (mydrug[cnt].name[0] != NULL)
	{
		printf("%s\t\t\t", mydrug[cnt].name);
		k = mydrug[cnt].kind;
		for (int i = 0; i < k; i++)
		{
			printf("%d ", mydrug[cnt].inventory[i].size);
		}
		printf("\t\t");
		for (int i = 0; i < k; i++)
		{
			printf("%d ", mydrug[cnt].inventory[i].stock);
		}
		printf("\n");
		cnt++;
	}
}
int getkind(char s[], int *a)
{
	char *pch;
	int j = 0;
	pch = strtok(s, ",");
	while (pch != NULL)
	{
		a[j++] = atoi(pch);
		pch = strtok(NULL, ",");
	}
	return j;
}
// 读入文件
int readFile(char filename[], Drugs *drug) {
	FILE *fp;
	int ans[10];//尺寸
	int ans1[10];//库存
	int number = 0;
	int number1 = 0;
	char name1[20];
	char line1[50];
	char line2[50];
	int count = 0; //当前药品数量
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Can not open file.");
		return -1;

	}
	else {
		while (fscanf(fp, "%s%s%s", name1, line1, line2) != EOF) {
			strcpy(mydrug[count].name, name1);
			number = getkind(line1, ans);
			getkind(line2, ans1);
			mydrug[count].kind = number;
			for (int i = 0; i < number; i++)
			{
				mydrug[count].inventory[i].size = ans[i];
				mydrug[count].inventory[i].stock = ans1[i];
			}
			count++;
		}
	}
	nrofDrug = count;
	fclose(fp);
	return count;
}
// 写到文件
void writeToFile(char filename, struct Drugs *drug, int i) {
	FILE *fp;
	fp = fopen(filename, "w");

	fclose(fp);
}

int Sub_Exist(char a[], char b[])//a  wodeyaowu   b yao
{
	int alen = strlen(a);
	int blen = strlen(b);
	int i = 0, j = 0;
	while (i<alen)
	{
		while (a[i] == b[j] && i<alen)
		{
			i++; j++;
		}
		if (j == blen)
			return i - j + 1;

		i = i - j + 1;
		j = 0;

	}
	return -1;

}

