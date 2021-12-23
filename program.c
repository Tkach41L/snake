#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#define width 20
#define height 20

bool gameOver;
int x,y,candyX,candyY,score;
int tailX[100],tailY[100];
int nTail;
int speed=500;
char food, menu;


/*struct timespec ts = {
	    .tv_sec = 0,                    // nr of secs
	        .tv_nsec = 10 * 1000000000L  // nr of nanosecs
};

struct timespec st = {
	            .tv_sec = 0,                    // nr of secs
		                    .tv_nsec = 0.10 * 1000000000L  // nr of nanosecs
};
struct timespec ts = {
	.tv_sec = 0,   
	.tv_nsec = 0.10 * 1000000000L };
*/		
enum Direction{STOP,LEFT,RIGHT,UP,DOWN};
int dir;

void setup();
void draw();
void input();
void logic();

int main(){
	initscr();
	start_color();
		init_pair(1, COLOR_YELLOW, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
		
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	curs_set(FALSE);
	nodelay(stdscr,TRUE);
	
	
	/*mvprintw(height/2,width/2,"WANNA PLAY?");
	refresh();
	int yes = getch();
		switch(yes){
			case 'y':case'Y':
				menu='Y';
				break;
			case 'n':case'N':
				menu='N';
				break;
	}
	if(menu=='N'){
		gameOver=true;}
	else if(menu=='Y'){*/
	
	
	setup();
	while(!gameOver){
	//	dir=STOP;
		draw();
		input();
		logic();
		refresh();
		}
	attron(COLOR_PAIR(4));
	mvprintw(height/2,width/2-4,"Game Over");
	attron(COLOR_PAIR(4));
	refresh();
	getchar();
	endwin();
	return EXIT_SUCCESS;
}

void setup(){
	gameOver=false;
	dir=STOP;
	x=width/2-1;
	y=height/2-1;
	candyX=rand()%width;
	candyY=rand()%height;
	// mvprintw(candyY,candyX,"@");
	score=0;
}

void draw(){
	
	struct timespec ts = {
		        .tv_sec = 0,
			        .tv_nsec = 0.10 * 1000000000L };
if(score<350){
	ts.tv_nsec=0.30* 1000000000L;}
if(score>=350){
	ts.tv_nsec=0.20* 1000000000L;}
if(score>=900){
	ts.tv_nsec=0.15* 1000000000L;}
if(score>=2000){
	ts.tv_nsec=0.10* 1000000000L;}
if(score>=3000){
	ts.tv_nsec=0.08*1000000000L;}
		for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			mvprintw(i,0,"#");
			mvprintw(i,width,"#");
		if(i==y && j==x){
			attron(COLOR_PAIR(2));
			mvprintw(y,x,"O");
			attroff(COLOR_PAIR(2));}
		
		else if(i==candyY && j==candyX){
			
		//	candyX=rand()%width;
		//	candyY=rand()%height;
			attron(COLOR_PAIR(1));
			mvprintw(candyY,candyX,"@");
			attroff(COLOR_PAIR(1));
			
		}
		else{
			bool print=false;
			for(int k=0;k<nTail;k++){
				if(tailX[k]==j && tailY[k]==i){
					print=true;
					attron(COLOR_PAIR(2));
					mvprintw(tailY[k],tailX[k],"o");
					attroff(COLOR_PAIR(2));
			}
			}
		if(!print)
			mvprintw(i,j," ");
		}
		}
	}
	
	for(int i=0;i<width+1;i++){
		//attron(COLOR_PAIR(5));
		mvprintw(height,i,"#");
		mvprintw(0,i,"#");
		//attroff(COLOR_PAIR(5));
		}
			
		
	attron(COLOR_PAIR(1));
	mvprintw(21,0,"Score:%d",score);
	attroff(COLOR_PAIR(1));
	refresh();
	nanosleep(&ts, NULL);
}

void input(){
	int input = getch();
	switch(input){
		case 'a': case 'A':
				dir=LEFT;
				break;
		case 'd': case 'D':
				dir=RIGHT;
				break;
		case 'w': case 'W':
				dir=UP;
				break;
		case 's': case 'S':
				dir=DOWN;
				break;
		case 'x': case 'X':
				gameOver=true;
				break;
		}
}

void logic(){
	int prevX=tailX[0];
	int prevY=tailY[0];
	int prev2x,prev2y;

	tailX[0]=x;
	tailY[0]=y;

	for(int i=1;i<nTail;i++){
		prev2x=tailX[i];
		prev2y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2x;
		prevY=prev2y;
	}
	switch(dir){
		case LEFT:
		x--;
		break;
		case RIGHT:
		x++;
		break;
		case UP:
		y--;
		break;
		case DOWN:
		y++;
		break;
	}
	
	if(x>width || x<0)
		gameOver=true;
	if(y>height || y<0)
		gameOver=true;
	for(int i=0;i<nTail;i++){
		if(tailX[i]==x && tailY[i]==y){
			gameOver=true;
	}
}
	if(x==candyX && y==candyY){
		nTail++;	
		score+=100+(rand()%10);
		while(1){
		candyX=rand()%width;
		if(candyX==0 || width==candyX)
			candyX=rand()%width;
		else break;}
		while(1){
		candyY=rand()%height;
		if(candyY==0 || height==candyY)
		candyY=rand()%height;
		else break;}
	}
}
