// BGIFirstTest.c : Example graphic application

#include <graphics.h>
#include <stdio.h>
#include <conio.h>  
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LABEL 10

void Snake(int Size, int bodyX[], int bodyY[], int head, int body);
void Points(int foodPosX, int foodPosY);
int Random(int placement);
int Game(int head, int body);

void Snake(int Size, int bodyX[], int bodyY[], int head, int body) {
	setfillstyle(0, BLACK);				
	for (int i = 0; i < Size; i++) {														//For loop goes through the length  to get the 
		bar(bodyX[i], bodyY[i], (bodyX[i] + 24), (bodyY[i] + 24));							//show snake body
		setfillstyle(0, GREEN);
	}
}

void Points(int foodPosX, int foodPosY) {
	setfillstyle(0, RED);
	setcolor(RED);
	fillellipse(foodPosX, foodPosY, 10, 10);

}

int Random(int placement) {
	int x = ((((rand() % placement) + 1) * 25) + 12);									//Algoriothm to randomly respawn food on the screen after previous food was eaten 
	return x;																			 
}
void main(void)
{
	int gd = DETECT, gm = 0, head = 0, body = 15;			//Begins window graphic window 
	char Player[256];

	initgraph(&gd, &gm, "");
	printf("Welcome to the wonderful world of snake\n");	 //Title
	printf("What is the snake's name?\n");					//Asks for name from player
	gets(Player);											//Recieves name of player				
		
	srand(time(NULL));
	int end = Game(head, body);
	if (end == 1) {											//1 should be returned when you win printing the win message
		printf("\nVictory for %s\n", Player);
	}
	else {
		printf("\n%s died :'(\n\n", Player);				//else you win the printing message
	}
	getchar();
}

int Game(int head, int body) {

	int input = 100;  
	int x = 25;
	int y = 100;
	int foodPosX = 312;
	int foodPosY = 212;
	int k = 0;
	int direction = -1;
	int i = 0;
	int size = 20;
	int view = 0;
	float delayNum;
	int bodyX[100] = { x,(x - 25), (x - 50), (x - 75), (x - 100), (x - 125), (x - 150), (x - 175), (x - 200), (x - 225), (x - 250), (x - 275), (x - 300), (x - 325), (x - 350), (x - 375), (x - 400), (x - 425), (x - 450), (x - 475) };
	int bodyY[100] = { y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y };

	while (1) {										//While the game is running
		view = (view + 1) % 2;			
		setactivepage(view);						//Smooth animation
		clearviewport();
		setbkcolor(LIGHTRED);						//Layor above background is light red 
		setfillstyle(0, LIGHTBLUE);					//Background is light blue
		bar(25, 25, 600, 450);						//Attributes for the border

		Snake(size, bodyX, bodyY, head, body);	//This presents the snake with all the cordinates

		Points(foodPosX, foodPosY);				//This presents the food with all the cordinates

		if (((bodyX[0] + 12) == foodPosX) && ((bodyY[0] + 12) == foodPosY)) {	//Collision for snake as it eats the food 
			bodyX[size] = bodyX[size - 1];										//Snake will be enlarged by another bar being added to its body  	
			bodyY[size] = bodyY[size - 1];										//add an extra segment to the snake
			size++;																//length++ adds to the length
			printf("\rScore: %d", (size - 20));									//print score number
			foodPosX = Random(22);
			foodPosY = Random(17);												//Randomises the coordinates of food 
		}
		setvisualpage(view);

		delayNum = log2((double)size / 10.0);
		delay(230.0 / delayNum);						//give user time to input control

		k = _kbhit();
		if (k == 1) {									//input check
			input = _getch();
			k = 0;
		
		}
		switch (input) {								//This case statement checks if input is valid. If valid change direction of the snake.
		case(119): if (direction != 1) {				//W makes the snake move up
			direction = 0;
		}
				   break;
		case(115): if (direction != 0) {				//S makes the snake the down
			direction = 1;
		}
				   break;
		case(100): if (direction != 3) {				//D makes the snake the right
			direction = 2;
		}
				   break;
		case(97): if (direction != 2) {					//A makes the snake the left
			direction = 3;
		}
				  break;
		}

		for (i = (size - 1); i > 0; i--) {			//move body of snake through x and y axis
			bodyX[i] = bodyX[i - 1];				
			bodyY[i] = bodyY[i - 1];
		}

		switch (direction) {					//Through the previous case statement, this allows the head to move such as...
		case(0): bodyY[0] -= 25;				//The heads postion to move upwards
			break;
		case(1): bodyY[0] += 25;				//The heads postion to move downards
			break;
		case(2): bodyX[0] += 25;				//The heads postion to move right
			break;
		case(3): bodyX[0] -= 25;				//The heads postion to move left
			break;
		}
		for (i = 1; i < (size); i++) {	//check body collisions
			if ((bodyX[0] == bodyX[i]) && (bodyY[0] == bodyY[i])) {				//if head collides with body return 0 (lose)
				return 0;
			}
			if (((foodPosX - 12) == bodyX[i]) && ((foodPosY - 12) == bodyY[i])) {		//As the snake growns another bar in its body...
				foodPosX = Random(22);													//The eaten food will respawn in another randomised area 
				foodPosY = Random(17);
			}
		}
		if ((bodyX[0] < 25) || (bodyX[0] > 590) || (bodyY[0] < 25) || (bodyY[0] > 440)) {	//The game terminates as the head of the snake hits its own body body
			return 0;
		}
	}
}


