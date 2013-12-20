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
//int GetAround(int x,int y,int b,int r);
//BOOL MoveDown();
//void TestFull();
void printposition(bool check);

struct Point {

     int x,y;

};


enum { EMPTY, CHARACTER, WALL, BOSS, TRASH, MID, HP, DEFENSE, STRENGTH };
//enum { CHARACTER, MONSTER, ITEM };

char *arTile[]={"  ","��","��","��","% ","�� ","��","��","��" };


int character_level;
int character_fullHP;
int character_HP;
int character_strength;
int character_defense;
int character_fullEXP;
int character_EXP;
int nx,ny;//character position

struct bossinfo{//��
int HP,strength,defense;
};

struct trashinfo{//% 
int HP,strength, defense, exp;
};

struct midinfo{//��
int HP,strength, defense, exp;
};


/*
struct bossinfo{//��
int HP=100;
int strength=20;
int defense=8;
};

struct trashinfo{//% 
int HP=20;
int strength=3;
int defense=2;
int exp=5; //trash�� �׿��� �� ���� �� �ִ� ����ġ
};

struct midinfo{//��
int HP=50;
int strength=8;
int defense=6;
int exp=8;
};*/

char *item_hp = "��";
int hp_giving=10;

char *item_defense = "��";
int defense_giving=1;

char *item_strength = "��";
int strength_giving=1;

int board[BW+2][BH+2];



int brick, rot;
 

void main()

{

     //int nFrame, nStay;

     int x,y;

     setcursortype(NOCURSOR);

     randomize();

     clrscr();

     for (x=0;x<=BW+2;x++) {
          for (y=0;y<BH+2;y++) {
              board[x][y] = (y==0 ||y==BH+1||x==0 ||x==1||x==BW+1||x==BW+2) ? WALL:EMPTY;
          }
     }
	 board[4][1]=BOSS;
	 gotoxy(4,1);
	 puts(arTile[board[BX+4][BY+1]]);

			character_level=1;
			character_fullHP=100;
			character_HP=100;
			character_strength=1;
			character_defense=1;
			character_fullEXP;
			character_EXP=0;

     DrawScreen();

     //nFrame=20;

 

     //for (;1;) {

          brick= 1; //random(sizeof(Shape)/sizeof(Shape[0]));

          nx=2;

          ny=1;



          PrintBrick(TRUE);

 

          //if (GetAround(nx,ny,brick,rot) != EMPTY) break;

          //nStay=nFrame;

          for (;2;) {

            //  if (--nStay == 0) {

                   //nStay=nFrame;

                   //if (MoveDown()) break;

             // }

              if (ProcessKey()) break;

              delay(1000/20);

          }

    // }

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


 

     gotoxy(52,2);puts("Dungeon Crawl Ver 1.0");
     gotoxy(52,4);puts("�¿����Ʒ�:�̵�");
     gotoxy(52,5);puts("z:������ �Ա�");
	 gotoxy(52,6);puts("x:����");
	 
	 //character status�� �ٸ����� print�ϴ°� ��������! 
	 gotoxy(52,8);printf("<character status>");
	 gotoxy(52,9);printf("Level: %d",character_level);
	 gotoxy(52,10);printf("HP: %3d",character_HP);
	 gotoxy(52,11);printf("Strength: %2d",character_strength);
	 gotoxy(52,12);printf("Defense: %2d",character_defense);
	 //gotoxy(52,13);printf("Items: ");


	 //monster������ �� ����� �κ�
	 gotoxy(52,15);puts("Monster status");
	 gotoxy(52,16);puts("Level: ");
	 gotoxy(52,17);puts("HP:");
	 gotoxy(52,18);puts("Strength: ");
	 gotoxy(52,19);puts("Defense");
	 //gotoxy(52,20);puts("Items: ");

}

 

void DrawBoard()

{

     int x,y;

 

     for (x=1;x<BW+3;x++) {

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

                   if (board[nx-2][ny] == EMPTY) {

                        PrintBrick(FALSE);

                        nx-=2;

                        PrintBrick(TRUE);

                   }

                   break;

              case RIGHT:

                   if (board[nx+2][ny] == EMPTY) {

                        PrintBrick(FALSE);

                        nx+=2;

                        PrintBrick(TRUE);

                   }
				   else if(board[nx+2][ny]==BOSS){
						
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

              switch (ch) {//space�� ������!!!! item�� ����~

              case ' ':

                   //while(MoveDown()==FALSE) {;}

                   return TRUE;

              }

          }


     }
		 gotoxy(52,14);printf("character position: %2d, %2d", nx, ny);
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

 

int GetAround(int x,int y,int b,int r)//��� ���� �ʿ��� �� ���� �ʴ�.

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

         // TestFull();

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