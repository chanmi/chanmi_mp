#include "Turboc.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define BX 5
#define BY 1
#define BW 15
#define BH 15

void DrawScreen();
void DrawBoard();
BOOL ProcessKey();
void PrintBrick(BOOL Show);
int GetAround(int x,int y,int b,int r);
BOOL MoveDown();
void TestFull();

struct Point {

     int x,y;

};

Point Shape[][4][4]={

     { {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2}, {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2} },

     { {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} },

     { {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1}, {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1} },

     { {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1}, {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1} },

     { {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1}, {0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} },

     { {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1}, {0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} },

     { {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0}, {0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} },

};


enum { EMPTY, BRICK, WALL };

char *arTile[]={". ","☆","□"};

//char character="☆";

int board[BW+2][BH+2];

int nx,ny;

int brick,rot;

 

void main()

{

     int nFrame, nStay;

     int x,y;

 

     setcursortype(NOCURSOR);

     randomize();

     clrscr();

     for (x=0;x<BW+2;x++) {
          for (y=0;y<BH+2;y++) {
              board[x][y] = (y==0 || y==BH+1 || x==0 || x==BW+1) ? WALL:EMPTY;
          }
     }

     DrawScreen();

     nFrame=20;

 

     for (;1;) {

          brick= random(sizeof(Shape)/sizeof(Shape[0]));

          nx=BW/2;

          ny=3;

          rot=0;

          PrintBrick(TRUE);

 

          if (GetAround(nx,ny,brick,rot) != EMPTY) break;

          nStay=nFrame;

          for (;2;) {

              if (--nStay == 0) {

                   nStay=nFrame;

                   //if (MoveDown()) break;

              }

              if (ProcessKey()) break;

              delay(1000/20);

          }

     }

     clrscr();

     gotoxy(30,12);puts("G A M E  O V E R");

     setcursortype(NORMALCURSOR);

}

 

void DrawScreen()

{

     int x,y;

 

     for (x=0;x<BW+2;x++) {

          for (y=0;y<BH+2;y++) {

              gotoxy(BX+x*2,BY+y);

              puts(arTile[board[x][y]]);

          }

     }

 

     gotoxy(50,2);puts("Dungeon Crawl Ver 1.0");
     gotoxy(50,4);puts("좌우위아래:이동");
     gotoxy(50,5);puts("z:아이템 먹기");
	 gotoxy(50,6);puts("x:공격");
	 
	 //character status는 다른데서 print하는게 좋을랑가! 
	 gotoxy(50,8);puts("character status");
	 gotoxy(50,9);puts("Level: ");
	 gotoxy(50,10);puts("HP:");
	 gotoxy(50,11);puts("Strength: ");
	 gotoxy(50,12);puts("Defense");
	 gotoxy(50,13);puts("Items: ");

	 //monster만났을 때 생기는 부분
	 gotoxy(50,15);puts("Monster status");
	 gotoxy(50,16);puts("Level: ");
	 gotoxy(50,17);puts("HP:");
	 gotoxy(50,18);puts("Strength: ");
	 gotoxy(50,19);puts("Defense");
	 gotoxy(50,20);puts("Items: ");

}

 

void DrawBoard()

{

     int x,y;

 

     for (x=1;x<BW+1;x++) {

          for (y=1;y<BH+1;y++) {

              gotoxy(BX+x*2,BY+y);

              puts(arTile[board[x][y]]);

          }

     }

}

 

BOOL ProcessKey()

{

     int ch,trot;

 

     if (kbhit()) {

          ch=getch();

          if (ch == 0xE0 || ch == 0) {

              ch=getch();

              switch (ch) {

              case LEFT:

                   if (GetAround(nx-1,ny,brick,rot) == EMPTY) {

                        PrintBrick(FALSE);

                        nx--;

                        PrintBrick(TRUE);

                   }

                   break;

              case RIGHT:

                   if (GetAround(nx+1,ny,brick,rot) == EMPTY) {

                        PrintBrick(FALSE);

                        nx++;

                        PrintBrick(TRUE);

                   }

                   break;

              case UP:

                   trot=(rot == 3 ? 0:rot+1);

                   if (GetAround(nx,ny,brick,trot) == EMPTY) {

                        PrintBrick(FALSE);

                        rot=trot;

                        PrintBrick(TRUE);

                   }

                   break;

              case DOWN:

                   if (MoveDown()) {

                        return TRUE;

                   }

                   break;

              }

          } else {

              switch (ch) {

              case ' ':

                   while(MoveDown()==FALSE) {;}

                   return TRUE;

              }

          }

     }

     return FALSE;

}

 

void PrintBrick(BOOL Show)

{

     int i;

     for (i=0;i<4;i++) {

          gotoxy(BX+(Shape[brick][rot][i].x+nx)*2,BY+Shape[brick][rot][i].y+ny);

          puts(arTile[Show ? BRICK:EMPTY]);

     }

}

 

int GetAround(int x,int y,int b,int r)

{

     int i,k=EMPTY;

 

     for (i=0;i<4;i++) {

          k=max(k,board[x+Shape[b][r][i].x][y+Shape[b][r][i].y]);

     }

     return k;

}

 

BOOL MoveDown()

{

     if (GetAround(nx,ny+1,brick,rot) != EMPTY) {

          TestFull();

          return TRUE;

     }

     PrintBrick(FALSE);

     ny++;

     PrintBrick(TRUE);

     return FALSE;

}

 

void TestFull()

{

     int i,x,y,ty;

 

     for (i=0;i<4;i++) {

          board[nx+Shape[brick][rot][i].x][ny+Shape[brick][rot][i].y]=BRICK;

     }

 

     for (y=1;y<BH+1;y++) {

          for (x=1;x<BW+1;x++) {

              if (board[x][y] != BRICK) break;

          }

          if (x == BW+1) {

              for (ty=y;ty>1;ty--) {

                   for (x=1;x<BW+1;x++) {

                        board[x][ty]=board[x][ty-1];

                   }

              }

              DrawBoard();

              delay(200);

          }

     }

}