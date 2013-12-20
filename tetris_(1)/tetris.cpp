#include "Turboc.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define BX 5//board location
#define BY 3//board location
#define BW 30
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


enum { EMPTY, CHARACTER, WALL, BOSS, TRASH, MID, HP, DEFENSE, STRENGTH };
//enum { CHARACTER, MONSTER, ITEM };

char *arTile[]={"  ","☆","□","※","% ","§ ","♡","♤","♨" };

struct characterinfo{//☆
int level;
int HP;
int strength;
int defense;
int EXP;

};

struct bossinfo{//※
int HP,strength,defense;
};

struct trashinfo{//% 
int HP,strength, defense, exp;
};

struct midinfo{//§
int HP,strength, defense, exp;
};


/*
struct bossinfo{//※
int HP=100;
int strength=20;
int defense=8;
};

struct trashinfo{//% 
int HP=20;
int strength=3;
int defense=2;
int exp=5; //trash를 죽였을 때 얻을 수 있는 경험치
};

struct midinfo{//§
int HP=50;
int strength=8;
int defense=6;
int exp=8;
};*/

char *item_hp = "♡";
int hp_giving=10;

char *item_defense = "♤";
int defense_giving=1;

char *item_strength = "♨";
int strength_giving=1;

int board[BW+2][BH+2];

int nx,ny;//character position

int brick, rot;
 

void main()

{

     int nFrame, nStay;

     int x,y;

 
	 //setcursortype(NORMALCURSOR);
     setcursortype(NOCURSOR);

     randomize();

     clrscr();

     for (x=0;x<BW+2;x++) {
          for (y=0;y<BH+2;y++) {
              board[x][y] = (y==0 ||y==BH+1||x==0 ||x==1||x==BW+1) ? WALL:EMPTY;
          }
     }

     DrawScreen();

     nFrame=20;

 

     for (;1;) {

          brick= 1; //random(sizeof(Shape)/sizeof(Shape[0]));

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

 

     for (x=0;x<=BW+2;x+=2) {

          for (y=0;y<BH+2;y++) {

              gotoxy(BX+x,BY+y);

              puts(arTile[board[x][y]]);

          }

     }
	 for(y=0;y<BH+2;y++){
		gotoxy(BX+x,BY+y);
		puts(arTile[board[BW+x][y]]);
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
	 gotoxy(50,14);printf("character position: %d, %d",nx,ny);

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

                   if (board[nx-1][ny] == EMPTY) {

                        PrintBrick(FALSE);

                        nx--;

                        PrintBrick(TRUE);

                   }

                   break;

              case RIGHT:

                   if (board[nx+1][ny] == EMPTY) {

                        PrintBrick(FALSE);

                        nx++;

                        PrintBrick(TRUE);

                   }

                   break;

              case UP:

				  if (board[nx][ny-1] == EMPTY) {

                        PrintBrick(FALSE);

                        ny--;

                        PrintBrick(TRUE);

                   }

                   /* trot=(rot == 3 ? 0:rot+1);

                   if (GetAround(nx,ny,brick,trot) == EMPTY) {

                        PrintBrick(FALSE);

                        rot=trot;

                        PrintBrick(TRUE);

                   }*/

                   break;

              case DOWN:

				  if (board[nx][ny+1] == EMPTY) {

                        PrintBrick(FALSE);

                        ny++;

                        PrintBrick(TRUE);

                   }

                  /* if (MoveDown()) {

                        return TRUE;

                   }*/

                   break;

              }

          } else {

              switch (ch) {//space를 누를때!!!! item을 먹자~

              case ' ':

                   //while(MoveDown()==FALSE) {;}

                   return TRUE;

              }

          }

     }

     return FALSE;

}

 

void PrintBrick(BOOL Show)

{

     int i;

		 gotoxy(BX+nx, BY+ny);
		 puts(arTile[Show? CHARACTER:EMPTY]);
	 /*
	 for (i=0;i<4;i++) {

          gotoxy(BX+(Shape[brick][rot][i].x+nx)*2,BY+Shape[brick][rot][i].y+ny);

          puts(arTile[Show ? BRICK:EMPTY]);

     }*/

}

 

int GetAround(int x,int y,int b,int r)//얘는 딱히 필요할 것 같지 않다.

{

     int i,k=EMPTY;

 
	 //i=1;
     //for (i=0;i<4;i++) {

          k=max(k,board[x][y]);

    // }

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

          //board[nx+Shape[brick][rot][i].x][ny+Shape[brick][rot][i].y]=BRICK;

     }

 

     for (y=1;y<BH+1;y++) {

          for (x=1;x<BW+1;x++) {

//              if (board[x][y] != BRICK) break;

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