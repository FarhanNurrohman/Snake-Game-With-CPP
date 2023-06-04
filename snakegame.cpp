#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <unistd.h>

using namespace std;

bool gameOver;
const int width = 31, height =20;
int x, y, fruitx, fruity, score, ntail;
int tailx[100], taily[100];
enum direction {
	STOP = 0, UP, DOWN, LEFT, RIGHT
};
direction dir;

void fruit(){
	fruitx = (rand() % width);
	fruity = (rand() % height);
	if(fruitx == 0){
		fruitx++;
	}
	if(fruity == 0){
		fruity++;	
	}
}

void setGame(){
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruit();
	score = 0;
	
}
void map(){
	for(int i = 0; i <= width; i++){
		cout << "#";
	}
	cout << endl;
	
	for(int i = 0; i < (height+1); i++){
		for(int k = 0; k <= (width); k++){
			if(k == 0 || k == (width)){
				cout << "#";
			}
			
			if( i == y && k == x){
				cout << "O";
			}else if(i == fruity && k == fruitx){
				cout << "@";
			}else{
				bool pr = false;
				for(int j = 0; j < ntail; j++){
					if(tailx[j] == k && taily[j] == i){
						cout << "o";
						pr = true;
					}	
				}
				if(!pr){
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	
	for(int i = 0; i <= width; i++){
		cout << "#";
	}
	cout << endl <<"skor anda :" << score << ", Xbuah : " << fruitx << ", Ybuah : " << fruity << ", jumlah ekor:" << ntail;
}

void control(){
	if(kbhit()){
		switch(getch()){
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				dir = STOP;
				break;
			default:
				break;
		}
	}
}
void logic(){
	int ptailx = tailx[0], ptaily = taily[0];
	int ptailx2, ptaily2;
	tailx[0] = x;
	taily[0] = y;
	for(int i = 1; i < ntail; i++){
		ptailx2 = tailx[i];
		ptaily2 = taily[i];
		tailx[i] = ptailx;
		taily[i] = ptaily;
		ptailx = ptailx2;
		ptaily = ptaily2;
	}
	switch(dir){
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
	}
	
	if(x > width || x < 0 || y > height || y < 0){
		gameOver = true;
	}
	for(int c = 0; c < ntail; c++){
		if(tailx[c] == x && taily[c] == y){
			gameOver = true;
		}
	}
	
	if(x == fruitx && y == fruity ){
		score += 10;
		ntail++;
		fruit();
	}
}

int main(){
	setGame();
	
	while(!gameOver){
		map();
		control();
		logic();
		system("cls");
		sleep(0.35);
	}
}
