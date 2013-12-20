#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>//curses.h =>linux��
#include <ctime>

using namespace std;
void GotoXY(int x, int y);
void SetCursorInvisible(void);
int GetKey(void);
void SetConsoleWindow(int cols, int lines);
void ClearScreen(void);
#define KEY_ESC 27
#define KEY_UP (256+72)
#define KEY_DOWN (256+80)
#define KEY_LEFT (256+75)
#define KEY_RIGHT (256+77)
//�� �Լ����� �ʿ信 ���� ����� ���� �ְ�, ������� ���� ���� ����
void GotoXY(int x, int y){//ȭ�� Ŀ���� �� ���̰� ��
 COORD Pos={x-1,y-1};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void SetCursorInvisible(void){//ȭ�� Ŀ���� �� ���̰� ��
 CONSOLE_CURSOR_INFO ci={10, FALSE};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
int GetKey(void){		//����Ű �Է��� �޾Ƶ���
 int ch=getch();		//�Ϲ������δ� getch�� ���� ���ڰ� �Էµ�����
 if(ch==0||ch==224)		//����Ű�� ��� 0 �Ǵ� 224�� ���� �Էµ� �� �ش� ����Ű ���� �Էµ�(2���Է�)
  ch=256+getch();		//���� �Ϲ�Ű���� �Է°��� ȥ���� ���ϱ� ���� 256�� ������
						//��)'H'�� UPŰ�� ���� 72�� ������
 return ch;
}
void SetConsoleWindow(int cols, int lines)
{
 char Buff[256];
 sprintf(Buff, "mode CON COLS=%d LINES=%d", cols, lines);
 system(Buff);
}
void ClearScreen(void){
 system("cls");
}
int main(void){
 int ch;
 SetCursorInvisible();	//Ŀ���� ������ ����
 system("mode CON COLS=100 LINES=50");
 char* map="########################################";
 cout<<map;
 char* block="��";
 GotoXY(1,3);
 cout<<block;

 while((ch=GetKey())!=KEY_ESC)
 {
  switch(ch){
  case KEY_UP://�����̵�
   GotoXY(20,3);
   cout<<" ";//�̰� ���ϴ°���@!?
   GotoXY(20,3);
   cout<<"UP��";
   break;
  case KEY_DOWN://�Ʒ��� �̵�
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"DOWN";
   break;
  case KEY_LEFT://�������� �̵�
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"LEFT";
   break;  
  
  case KEY_RIGHT://���������� �̵�
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"RIGHT";
   break;
  }
 }
 ClearScreen;
 cout<<"���α׷� ����!"<<endl;
 return 0;
}