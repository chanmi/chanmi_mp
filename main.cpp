#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>//curses.h =>linux용
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
//이 함수들은 필요에 따라 사용할 수도 있고, 사용하지 않을 수도 있음
void GotoXY(int x, int y){//화면 커서를 안 보이게 함
 COORD Pos={x-1,y-1};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void SetCursorInvisible(void){//화면 커서를 안 보이게 함
 CONSOLE_CURSOR_INFO ci={10, FALSE};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
int GetKey(void){		//방향키 입력을 받아들임
 int ch=getch();		//일반적으로는 getch에 의해 문자가 입력되지만
 if(ch==0||ch==224)		//방향키의 경우 0 또는 224가 먼저 입력된 후 해당 방향키 값이 입력됨(2자입력)
  ch=256+getch();		//원래 일반키와의 입력과의 혼동을 피하기 위해 256을 더해줌
						//예)'H'와 UP키의 값이 72로 동일함
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
 SetCursorInvisible();	//커서가 보이지 않음
 system("mode CON COLS=100 LINES=50");
 char* map="########################################";
 cout<<map;
 char* block="□";
 GotoXY(1,3);
 cout<<block;

 while((ch=GetKey())!=KEY_ESC)
 {
  switch(ch){
  case KEY_UP://위로이동
   GotoXY(20,3);
   cout<<" ";//이건 왜하는거지@!?
   GotoXY(20,3);
   cout<<"UP☆";
   break;
  case KEY_DOWN://아래로 이동
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"DOWN";
   break;
  case KEY_LEFT://왼쪽으로 이동
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"LEFT";
   break;  
  
  case KEY_RIGHT://오른쪽으로 이동
   GotoXY(20,3);
   cout<<" ";
   GotoXY(20,3);
   cout<<"RIGHT";
   break;
  }
 }
 ClearScreen;
 cout<<"프로그램 종료!"<<endl;
 return 0;
}