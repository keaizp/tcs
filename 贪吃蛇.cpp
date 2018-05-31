#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

int score=0,speed=300;

void set_cursor_position(int x,int y);
void create_snake();
void create_food();
void eat_food();
int bite_self();
int strike_map();
void print_snake(); 
void move_snake();
void print_map();
void pause();
void update();
void start_Game();
void init_Game();
void run_Game();
void end_Game();

enum direction  //�ߵķ���
{
U,D,L,R
}dir;


struct SNAKE  //�ߵĽṹ��
{
int x;
int y;
struct SNAKE *next;
};
SNAKE *snake,*temp,*head,*food;



void set_cursor_position(int x,int y)  //�ƶ����
{
COORD coord={x,y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}




void create_snake()  //���߽��г�ʼ��
{
head=(SNAKE*)malloc(sizeof(SNAKE));
snake=head;
snake->x=8;
snake->y=8;
snake->next=NULL;
for(int i=6;i>=4;i-=2)
{
temp=(SNAKE*)malloc(sizeof(SNAKE));
temp->x=i;
temp->y=8;
temp->next=NULL;
snake->next=temp;
snake=temp;
}
}


void create_food()    //��ӡʳ��
{
srand((unsigned)time(NULL));
food=(SNAKE *)malloc(sizeof(SNAKE));
food->x=(rand()%27+1)*2;
food->y=rand()%27+1;
snake=head;
while(snake!=NULL)
{
if(food->x==snake->x&&food->y==snake->y)
{create_food();return;}
else snake=snake->next;
}
set_cursor_position(food->x,food->y);
printf("ʳ");
}

void eat_food()   //�ж��Ƿ�Ե�ʳ��
{
snake=head;
if(snake->x==food->x&&snake->y==food->y)
{
food->next=snake;
head=food;
create_food();
score=score+100;
if(score%500==0)speed=speed+50;
set_cursor_position(head->x,head->y);
printf("��");
}
}


int bite_self()  //�ж��Ƿ�ҧ���Լ�
{
snake=head->next->next;
while(snake!=NULL)
{
if(snake->x==head->x&&snake->y==head->y)return 1;
snake=snake->next;
}
return 0;
}

int strike_map()  //�ж��Ƿ�ײǽ
{
snake=head;
if(snake->x==0||snake->y==0||snake->x==58||snake->y==28)
return 1;
else return 0;
}

void print_snake()    //��ӡ��
{
snake=head;
while(snake!=NULL)
{
set_cursor_position(snake->x,snake->y);
printf("��");
snake=snake->next;
}
}


void move_snake()
{
temp=(SNAKE*)malloc(sizeof(SNAKE));
if(dir==R)     {temp->x=head->x+2;temp->y=head->y;}
else if(dir==L){temp->x=head->x-2;temp->y=head->y;}
else if(dir==U){temp->x=head->x;temp->y=head->y-1;}
else           {temp->x=head->x;temp->y=head->y+1;}
temp->next=head;
head=temp;
snake=head;
set_cursor_position(head->x,snake->y);
printf("��");
while(snake->next->next!=NULL)
{
snake=snake->next;
}
set_cursor_position(snake->next->x,snake->next->y);
printf("  ");
free(snake->next);
snake->next=NULL;
}


void print_map()    //��ӡ��ͼ
{
for(int i=0;i<=58;i+=2)
{
set_cursor_position(i,0);
printf("��");
set_cursor_position(i,28);
printf("��");
}
for(i=1;i<28;i++)
{
set_cursor_position(0,i);
printf("��");
set_cursor_position(58,i);
printf("��");
}
}

void update()
{
set_cursor_position(70,10);
printf("score=%d",score);
set_cursor_position(70,12);
printf("speed=%d",speed);
}

void pause()
{
while(1)
{
Sleep(300);
if(GetAsyncKeyState(VK_SPACE))
break;
}
}

void init_Game()     //��ʼ����Ϸ
{
create_snake();
print_map();
print_snake();
create_food();
}




void run_Game()      //������Ϸ
{
dir=R;
while(1)
{
update();
Sleep(600-speed);
if(GetAsyncKeyState(VK_UP)&&dir!=D){dir=U;}
else if(GetAsyncKeyState(VK_DOWN)&&dir!=U){dir=D;}
else if(GetAsyncKeyState(VK_RIGHT)&&dir!=L){dir=R;}
else if(GetAsyncKeyState(VK_LEFT)&&dir!=R){dir=L;}
else if(GetAsyncKeyState(VK_SPACE))pause();
else;
move_snake();
eat_food();
if(bite_self()==1||strike_map()==1)break;
}
}


void end_Game()
{
set_cursor_position(72,15);
printf("Game Over");
pause();

}

void start_Game()
{
set_cursor_position(40,8);
printf("��������̰�������磡");
set_cursor_position(40,10);
printf("1�����л���Ӣ�����뷨");
set_cursor_position(40,12);
printf("2���ϡ��¡����ҡ����Ʒ���");
set_cursor_position(40,14);
printf("3���ո����ͣ");
set_cursor_position(40,16);
printf("����̰���ߣ��ҵ������������棬�ҷֲ����Լ���ͷ��β�ͣ���ϲ���ԡ�ʳ�����Ҳ���");
set_cursor_position(40,17);
printf("���Լ�(�Լ�̫�ѳ�)����ײǽ�ͻ��������ܸ����ϲ���Ҿ͸�1594008518������ɣ�");
set_cursor_position(40,19);
system("pause");
system("cls");
}


void main()
{
start_Game();
init_Game();
run_Game();
end_Game();
}