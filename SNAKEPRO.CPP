
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<dos.h>
#include<graphics.h>

#define ESC 27
#define UP 72
#define LEFT 75
#define DOWN 80
#define RIGHT 77
#define SAVE 90
#define LOAD 76

void start(void);
void snake(char **,char **);
void randomize(char *,char *,char *,char *,char *,int,char);
char getkey(char,char);
void savegame(char *,char *,int,char);
int loadgame(char *,char *,char *);
void win_message(void);
void end();
int p;

main()
{
char *x,*y,pos_x,pos_y,num,out=0,old_ch=0,ch=0,new_ch,new_x,new_y,old_num=0;
int i,length=6,a=DETECT,b;
initgraph(&a,&b,"c:/turboc3/BGI");

cleardevice();
setbkcolor(2);
setcolor(5);
settextstyle(3,0,1);
outtextxy(100,40,"WELCOME TO THE WORLD OF SNAKES");
outtextxy(120,80,"PLAY YOUR BEST LEAVE ON THE REST");
outtextxy(140,120,"UES ARROW KEYS FOR PLAYING AND Esc TO EXIT");
outtextxy(160,140,"PRESS Z TO SAVE THE GAME");
outtextxy(180,160,"PRESS L TO LOAD THE GAME");
settextstyle(5,0,2);
outtextxy(40,260,"PRESS 1 TO START EASY MODE");
outtextxy(40,300,"PRESS 2 TO START MEDIUM MODE");
outtextxy(40,280,"PRESS 3 TO START HARD MODE");
p=getch();
sleep(5);
cleardevice();
start();
snake(&x,&y);
randomize(&pos_x,&pos_y,&num,x,y,length,ch);


while(!out){
if((new_ch=getkey(old_ch,ch))==ESC)
{out=2;
end();}
if(out)
{break;end();}
if(new_ch==SAVE)
savegame(x,y,length,old_ch);
else if(new_ch==LOAD){
length=loadgame(x,y,&ch);
randomize(&pos_x,&pos_y,&num,x,y,length,ch);
}
else
ch=new_ch;
new_x=x[0];
new_y=y[0];
if(ch==UP)
new_y=y[0]-1;
else if(ch==LEFT)
new_x=x[0]-1;
else if(ch==DOWN)
new_y=y[0]+1;
else if(ch==RIGHT)
new_x=x[0]+1;
old_ch=ch;
if((new_x<2)|(new_y<2)|(new_x>79)|(new_y>22))
out=1;
for(i=1;i<length-!old_num;i++)
if((new_x==x[i])&(new_y==y[i])){
out=1;
break;
end();
}
if((pos_x==new_x)&(pos_y==new_y)){
old_num+=num;
randomize(&pos_x,&pos_y,&num,x,y,length,ch);
}
if(!old_num){
gotoxy(x[length-1],y[length-1]);
putchar(' ');
}
else{
length++;
if(length==1638){
win_message();
return 0;
}
gotoxy(67,25);
printf("Score = %5d",length-6+5);
old_num--;
x[i+1]=x[i];
y[i+1]=y[i];
}
for(i=length-1;i>0;i--){
x[i]=x[i-1];
y[i]=y[i-1];
if(i==1){
gotoxy(x[i],y[i]);
putchar('*');
}
}
x[0]=new_x;
y[0]=new_y;
gotoxy(x[0],y[0]);
printf("*\b");
if(out)
break;
delay(10);
}
if(out==1){
gotoxy(1,24);
clrscr();
end();
gotoxy(x[0],y[0]);
}
return 0;
}




void start()
{
char i;


clrscr();
putchar('!');
for(i=0;i<78;i++)
putchar('-');
putchar('!');
gotoxy(1,23);
putchar('!');
for(i=0;i<78;i++)
putchar('-');
putchar('!');
window(1,2,1,23);
for(i=0;i<21;i++)
cprintf("!");
window(80,2,80,23);
for(i=0;i<21;i++)
cprintf("!");
window(1,1,80,25);
gotoxy(38,12);
printf("******");
gotoxy(43,12);
while(!kbhit());
gotoxy(30,24);
delline();delline();
cprintf("\n( EAT THE NUMBER !! ) Score = 0");
gotoxy(43,12);
}


void snake(char **px,char **py)
{
char i;


*px=(char *)malloc(2000*sizeof(char));
*py=(char *)malloc(2000*sizeof(char));
for(i=0;i<6;i++){
(*px)[i]=43-i;
(*py)[i]=12;
}
}


void randomize(char *px,char *py,char *pn,char *x,char *y,int length,char ch)
{
int allowed=0,i;


while(!allowed){
allowed=1;
srand((unsigned)time(0));
*px=rand()%78+2;
srand((unsigned)time(0));
*py=rand()%21+2;
if(ch==UP){
if((*px==x[0])&(*py==y[0]-1))
allowed=0;
}
else if(ch==DOWN){
if((*px==x[0])&(*py==y[0]+1))
allowed=0;
}
else if(ch==LEFT){
if((*px==x[0]-1)&(*py==y[0]))
allowed=0;
}
else if((ch==RIGHT)&(*px==x[0]+1)&(*py==y[0]))
allowed=0;
for(i=0;(i<length)&&allowed;i++)
if((*px==x[i])&(*py==y[i]))
allowed=0;
}
srand((unsigned)time(0));
*pn=rand()%9+1;
gotoxy(*px,*py);
putchar(*pn+48);
gotoxy(x[0],y[0]);
}


char getkey(char old_ch,char ch)
{
char i;


if(kbhit())
for(i=0;i<5;i++){
while((ch=getch())==0);
if(ch==27){
return ch;
}
if((ch!=LOAD)&(ch!=SAVE)&(ch!=UP)&(ch!=DOWN)&
(ch!=LEFT)&(ch!=RIGHT))
continue;
if((ch!=old_ch)|(!kbhit()))
break;
}
else
for(i=0;(i<12)&(!kbhit());i++)
delay(100);
return ch;
}


void savegame(char *px,char *py,int length,char ch)
{
FILE *fp;
int i;


rename("snake.sav","snake.bak");
fp=fopen("snake.sav","wb");
fprintf(fp,"%d %c",length,ch);
for(i=0;i<length;i++)
fprintf(fp,"%c%c",px[i],py[i]);
fclose(fp);
}


int loadgame(char *px,char *py,char *pch)
{
FILE *fp;
int length,i;


fp=fopen("snake.sav","rb");
if(!fp){
clrscr();
puts("ERROR: no saved game found in current directory!!!\n\n\t\t"
"Exiting...\n");
sleep(3);
exit(1);
}
window(2,2,79,22);
clrscr();
fscanf(fp,"%d %c",&length,pch);
for(i=0;i<length;i++){
fscanf(fp,"%c%c",&px[i],&py[i]);
gotoxy(px[i]-1,py[i]-1);
putchar('*');
}
window(1,1,80,25);
gotoxy(30,24);
delline();delline();
cprintf("\n( EAT THE NUMBER !! ) Score = %5d",(length-6)+5);
gotoxy(px[0],py[0]);
printf("*\b");
fclose(fp);
return length;
}


void win_message()
{
window(1,1,80,25);
gotoxy(1,24);
delline();delline();
textcolor(14);
clrscr();
cprintf("CONGRATULATION!! YOU HAVE COMPLETED THE GAME!!\r\n"
"(Press any key to terminate...)");
sleep(15);
clrscr();
textcolor(7);
}

void end()
{
 clrscr();
 cleardevice();
 setbkcolor(CGA_GREEN);
 setcolor(CGA_RED);
 settextstyle(3,0,2);
 outtextxy(200,200,"GAME OVER");
 outtextxy(100,250,"YOU HIT WITH BOUNDRY OR YOUR SELF");
 outtextxy(150,300,"I HOPE YOU ENJOYED THE GAME");
 settextstyle(6,0,1);
 outtextxy(50,400,"ASHUTOSH COE16b007");
 outtextxy(50,420,"VIBHOR COE16b032");
 outtextxy(50,440,"ANIK COE16b001");
 getch();
 sleep(5);
 exit(0);
}