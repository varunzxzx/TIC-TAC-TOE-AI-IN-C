#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define PUTVALUE        if(put_value(x,y,0))\
			{\
			gotoxy(x,y);\
			printf("%c",mark);\
			gotoxy(x,y);\
			}\
			else\
			continue;
#define ASK             gotoxy(1,15);\
			printf("Press Y to play more, N to exit");\
			another=get_key();\
			if(another=='y'||another=='Y')\
				main();\
			else\
			exit(0);
void draw_box();
void start_game();
int check_boundary(int,int,int);
int put_value(int,int,int);
int win_check(int);
int get_key();
void PC_turn(int *,int *);
int check_user_game();
int block[9],reset;char mark;
void main()
{
	int n;
	reset=1;
	clrscr();
	gotoxy(10,10);
	printf("1-> To play with X");
	gotoxy(10,11);
	printf("2-> To play with O ");
	gotoxy(10,12);
	printf("Choose an option: ");
	fflush(stdin);
	n=get_key();
	switch(n)
	{
		case 49: mark='X';
		break;
		case 50: mark='O';
		break;
		default: exit(0);
	}
	draw_box();
	start_game();
}
void draw_box()
{
	int x=20;
	clrscr();
	/*------- Horizontal lines ----------*/
	for(x=20;x<33;x++)
	{
		gotoxy(x,5);
		printf("-");
	}
	for(x=20;x<33;x++)
	{
		gotoxy(x,7);
		printf("-");
	}
	for(x=20;x<33;x++)
	{
		gotoxy(x,9);
		printf("-");
	}
	for(x=20;x<33;x++)
	{
		gotoxy(x,11);
		printf("-");
	}
	/*----------Vertical Lines---------------*/
	for(x=6;x<=10;x+=2)
	{
		gotoxy(20,x);
		printf("|");
	}
	for(x=6;x<=10;x+=2)
	{
		gotoxy(24,x);
		printf("|");
	}
	for(x=6;x<=10;x+=2)
	{
		gotoxy(28,x);
		printf("|");
	}
	for(x=6;x<=10;x+=2)
	{
		gotoxy(32,x);
		printf("|");
	}
	gotoxy(40,6);
	printf("1. Use Arrow Keys to move cursor");
	gotoxy(40,7);
	printf("2. Press SPACEBAR to mark %c",mark);
	gotoxy(40,8);
	printf("3. Press ESC to exit");
}
void start_game()
{
	int ch,x=22,y=6;char another;
	gotoxy(x,y);
	while(1)
	{
		ch=get_key();
		a:
		switch(ch)
		{
			case 72:	if(check_boundary(x,y,72)==0)
					break;
					gotoxy(x,y-=2);
					if((ch=get_key())==32)
					{
						PUTVALUE;
					}
					else goto a;
			break;
			case 77:	if(check_boundary(x,y,77)==0)
					break;
					gotoxy(x+=4,y);
					if((ch=get_key())==32)
					{
						PUTVALUE;
					}
					else goto a;
			break;
			case 80:	if(check_boundary(x,y,80)==0)
					break;
					gotoxy(x,y+=2);
					if((ch=get_key())==32)
					{
						PUTVALUE;
					}
					else goto a;
			break;
			case 75:	if(check_boundary(x,y,75)==0)
					break;
					gotoxy(x-=4,y);
					if((ch=get_key())==32)
					{
						PUTVALUE;
					}
					else goto a;
			break;
			case 32:	PUTVALUE;
			break;
			case 27:	exit(0);
			break;
			default:       	continue;
		}
		if(wincheck(3)==1)
		{
			gotoxy(1,6);
			printf("You Won!!!");
			ASK;
		}
		if(ch==32)
			PC_turn(&x,&y);
	}
}
void PC_turn(int *x,int *y)
{
	char PC_mark,another;int i;
	static struct cood
	{
		int x;
		int y;

	}tmp_block[9]={{22,6},{26,6},{30,6},{22,8},{26,8},{30,8},{22,10},{26,10},{30,10}};
	if(mark=='X')
		PC_mark='O';
	else
		PC_mark='X';
	delay(100);
	if((i=PC_strategy())!=9)
	{
		if(put_value(tmp_block[i].x,tmp_block[i].y,1))
		{
			gotoxy(tmp_block[i].x,tmp_block[i].y);
			printf("%c",PC_mark);
			gotoxy(tmp_block[i].x,tmp_block[i].y);
			*x=tmp_block[i].x;
			*y=tmp_block[i].y;
		}
		else
			goto b;
	}
	else
	{
		b:
		gotoxy(1,6);
		printf("\nGame Draw");
		ASK;
	}
	if(wincheck(12)==1)
	{
		gotoxy(1,6);
		printf("PC Won!!!");
		ASK;
	}
}
int PC_strategy()
{
	int i;
	if((i=check_user_game(1))!=9)
		return i;
	else if((i=check_user_game(0))!=9)
		return i;
	if(block[4]==1)
	{
		if(block[4]==0)
			return 4;
		if(block[0]==0)
			return 0;
		if(block[2]==0)
			return 2;
		if(block[6]==0)
			return 6;
		if(block[8]==0)
			return 8;
	}
	if(block[1]==1||block[3]==1||block[5]==1||block[7]==1)
	{
		/*if(block[4]==0)
			return 4;
		if(block[0]==0)
			return 0;
		if(block[2]==0)
			return 2;
		if(block[6]==0)
			return 6;
		if(block[8]==0)
			return 8;*/
		if(block[4]==0)
			return 4;
		if(block[5]==0)
			return 5;
		if(block[1]==0)
			return 1;
		if(block[3]==0)
			return 3;
		if(block[7]==0)
			return 7;
	}
	if((block[0]==1&&block[8]==1)||(block[2]==1&&block[6]==1))
	{
		if(block[5]==0)
			return 5;
		if(block[1]==0)
			return 1;
		if(block[3]==0)
			return 3;
		if(block[7]==0)
			return 7;
	}
	if((block[0]==1||block[2]==1||block[6]==1||block[8]==1)&&(block[1]==1||block[3]==1||block[5]==1||block[7]==1))
	{
		if(block[7]==0)
			return 7;
		if(block[5]==0)
			return 5;
		if(block[1]==0)
			return 1;
		if(block[3]==0)
			return 3;
	}
	if(block[4]==0)
		return 4;
	if(block[3]==0)
		return 3;
	if(block[1]==0)
		return 1;
	if(block[5]==0)
		return 5;
	if(block[7]==0)
		return 7;
	if(block[2]==0)
		return 2;
	if(block[0]==0)
		return 0;
	if(block[6]==0)
		return 6;
	else
		return 8;
}
int check_user_game(int who)
{
	int i;
	if(who==0)
		i=1;
	else
		i=4;
	if(block[0]==i||block[1]==i||block[2]==i)
	{
		if(block[0]==i&&block[1]==i)
			if(block[2]==0)
				return 2;
		if(block[1]==i&&block[2]==i)
			if(block[0]==0)
				return 0;
		if(block[0]==i&&block[2]==i)
			if(block[1]==0)
				return 1;
	}
	if(block[3]==i||block[4]==i||block[5]==i)
	{
		if(block[3]==i&&block[4]==i)
			if(block[5]==0)
				return 5;
		if(block[4]==i&&block[5]==i)
			if(block[3]==0)
				return 3;
		if(block[3]==i&&block[5]==i)
			if(block[4]==0)
				return 4;
	}
	if(block[6]==i||block[7]==i||block[8]==i)
	{
		if(block[6]==i&&block[7]==i)
			if(block[8]==0)
				return 8;
		if(block[7]==i&&block[8]==i)
			if(block[6]==0)
				return 6;
		if(block[6]==i&&block[8]==i)
			if(block[7]==0)
				return 7;
	}
	if(block[0]==i||block[3]==i||block[6]==i)
	{
		if(block[0]==i&&block[3]==i)
			if(block[6]==0)
				return 6;
		if(block[3]==i&&block[6]==i)
			if(block[0]==0)
				return 0;
		if(block[0]==i&&block[6]==i)
			if(block[3]==0)
				return 3;
	}
	if(block[1]==i||block[4]==i||block[7]==i)
	{
		if(block[1]==i&&block[4]==i)
			if(block[7]==0)
				return 7;
		if(block[4]==i&&block[7]==i)
			if(block[1]==0)
				return 1;
		if(block[1]==i&&block[7]==i)
			if(block[4]==0)
				return 4;
	}
	if(block[2]==i||block[5]==i||block[8]==i)
	{
		if(block[2]==i&&block[5]==i)
			if(block[8]==0)
				return 8;
		if(block[5]==i&&block[8]==i)
			if(block[2]==0)
				return 2;
		if(block[2]==i&&block[8]==i)
			if(block[5]==0)
				return 5;
	}
	if(block[0]==i||block[4]==i||block[8]==i)
	{
		if(block[0]==i&&block[4]==i)
			if(block[8]==0)
				return 8;
		if(block[4]==i&&block[8]==i)
			if(block[0]==0)
				return 0;
		if(block[0]==i&&block[8]==i)
			if(block[4]==0)
				return 4;
	}
	if(block[2]==i||block[4]==i||block[6]==i)
	{
		if(block[2]==i&&block[4]==i)
			if(block[6]==0)
				return 6;
		if(block[4]==i&&block[6]==i)
			if(block[2]==0)
				return 2;
		if(block[2]==i&&block[6]==i)
			if(block[4]==0)
				return 4;
	}
	return 9;
}
int put_value(int x,int y,int who)
{
	int i,j,n=0;
	static int flag[9]={0};
	if(reset==1)
	{
		for(i=0;i<9;i++)
		{
			flag[i]=0;
			block[i]=0;
		}
		reset=0;
	}
	if(who==0)
	{
		i=3;
		j=1;
	}
	else
	{
		i=12;
		j=4;
	}
	if(x==22&&y==6)
		{
			if(flag[0]==0)
				{block[0]=j;flag[0]=1;n=1;}
		}
	else if(x==26&&y==6)
		{
			if(flag[1]==0)
				{block[1]=j;flag[1]=1;n=1;}
		}
	else if(x==30&&y==6)
		{
			if(flag[2]==0)
				{block[2]=j;flag[2]=1;n=1;}
		}
	else if(x==22&&y==8)
		{
			if(flag[3]==0)
				{block[3]=j;flag[3]=1;n=1;}
		}
	else if(x==26&&y==8)
		{
			if(flag[4]==0)
				{block[4]=j;flag[4]=1;n=1;}
		}
	else if(x==30&&y==8)
		{
			if(flag[5]==0)
				{block[5]=j;flag[5]=1;n=1;}
		}
	else if(x==22&&y==10)
		{
			if(flag[6]==0)
				{block[6]=j;flag[6]=1;n=1;}
		}
	else if(x==26&&y==10)
		{
			if(flag[7]==0)
				{block[7]=j;flag[7]=1;n=1;}
		}
	else
		{
			if(flag[8]==0)
				{block[8]=j;flag[8]=1;n=1;}
		}
	if(n==1)
		return 1;
	else
		return 0;
}
int wincheck(int i)
{
	if(block[0]+block[1]+block[2]==i)
		return 1;
	else if(block[3]+block[4]+block[5]==i)
		return 1;
	else if(block[6]+block[7]+block[8]==i)
		return 1;
	else if(block[0]+block[3]+block[6]==i)
		return 1;
	else if(block[1]+block[4]+block[7]==i)
		return 1;
	else if(block[2]+block[5]+block[8]==i)
		return 1;
	else if(block[0]+block[4]+block[8]==i)
		return 1;
	else if(block[2]+block[4]+block[6]==i)
		return 1;
	else
		return 0;
}
int check_boundary(int x,int y,int ch)
{
	if(x==22&&y==6)
	{
		if(ch==77||ch==80)
			return 1;
		else
			return 0;
	}
	else if(x==26&&y==6)
	{
		if(ch==75||ch==80||ch==77)
			return 1;
		else
			return 0;
	}
	else if(x==30&&y==6)
	{
		if(ch==75||ch==80)
			return 1;
		else
			return 0;
	}
	else if(x==22&&y==8)
	{
		if(ch==72||ch==77||ch==80)
			return 1;
		else
			return 0;
	}
	else if(x==26&&y==8)
	{
		return 1;
	}
	else if(x==30&&y==8)
	{
		if(ch==72||ch==75||ch==80)
			return 1;
		else
			return 0;
	}
	else if(x==22&&y==10)
	{
		if(ch==72||ch==77)
			return 1;
		else
			return 0;
	}
	else if(x==26&&y==10)
	{
		if(ch==75||ch==72||ch==77)
			return 1;
		else
			return 0;
	}
	else
	{
		if(ch==72||ch==75)
			return 1;
		else
			return 0;
	}
}
int get_key()
{
	int ch;
	ch=getch();
	if(ch==NULL)
	{
		ch=getch();
		return ch;
	}
	return ch;
}