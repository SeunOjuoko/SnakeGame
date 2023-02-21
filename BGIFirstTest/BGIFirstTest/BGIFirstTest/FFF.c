// BGIFirstTest.c : Example graphic application

#include <graphics.h>
#include <stdio.h>
#include <conio.h>  
#include <stdlib.h>
#include <time.h>
#include <math.h>

int SnakeAnimation(int headColour, int body1Colour, int body2Colour);
int FoodRandom1(int numSquares);
int FoodRandom2(int numSquares);
void PrintSnake(int length, int bodyX[], int bodyY[], int headColour, int body1Colour, int body2Colour);
void ShowFood1(int foodX, int foodY);
void ShowFood2(int foodV, int foodW);
int SelectColour();

//TODO implement highscore saving to a file

void main(void)
{
	// Initialise graphic window
	int gd = DETECT, gm = 0, head = 0, body1 = 15, body2 = 1;
	char name[256];

	initgraph(&gd, &gm, "");
	printf("Welcome to SNAKE\n"
		"The controls are W, A, S and D for\n"
		"UP, LEFT, DOWN and RIGHT respectively\n");

	printf("What is your snake's name?\n");
	gets(name);
	printf("\r                                                  \n");


	srand(time(NULL));
	int end = SnakeAnimation(head, body1, body2);

	if (end == 1) {
		printf("\nVictory for %s\n", name);
	}
	else {
		printf("\n%s died RIP\n\n", name);
	}
	getchar();
}

int SelectColour() {
	int i, x = 250, y = 50, cursorY = 50, view = 0;
	int colours[14] = { 0,1,3,5,6,7,8,9,10,11,12,13,14,15 };
	while (1) {
		view++;
		//setactivepage(view % 2);
		//clearviewport();
		setfillstyle(0, BLACK);
		setcolor(WHITE);
		for (i = 0; i < 14; i++) {
			setfillstyle(0, colours[i]);
			bar(x, (y + (25 * i)), (x + 25), (y + (25 * (i + 1))));
			rectangle(x, (y + (25 * i)), (x + 25), (y + (25 * (i + 1))));
		}
		setfillstyle(0, LIGHTRED);
		bar((x + 40), cursorY, (x + 90), cursorY + 25);
		setvisualpage(view % 2);
		switch (getch()) {
		case(119):
			if (cursorY > 50) {
				cursorY -= 25;
			}
			break;
		case(115):
			if (cursorY < 375) {
				cursorY += 25;
			}
			break;
		case(13):
			return colours[((cursorY - 50) / 25)];
		}
	}
}

int SnakeAnimation(int headColour, int body1Colour, int body2Colour) {

	int input = 100, x = 25, y = 100, foodX = 312, foodY = 212, foodV = 312, foodW = 300, k = 0, direction = -1, i = 0, length = 20, view = 0;
	float delayNum;
	int bodyX[100] = { x,(x - 25), (x - 50), (x - 75), (x - 100), (x - 125), (x - 150), (x - 175), (x - 200), (x - 225), (x - 250), (x - 275), (x - 300), (x - 325), (x - 350), (x - 375), (x - 400), (x - 425), (x - 450), (x - 475)
};
	int bodyY[100] = { y, y, y, y };

	while (1) {
		view = (view + 1) % 2;
		setactivepage(view);
		clearviewport();
		setbkcolor(BROWN);
		setfillstyle(0, GREEN);
		bar(25, 25, 600, 450);		//border

		PrintSnake(length, bodyX, bodyY, headColour, body1Colour, body2Colour);	//Print the snake

		ShowFood1(foodX, foodY);				//Print the food


		ShowFood2(foodV, foodW);

		if (((bodyX[0] + 12) == foodX) && ((bodyY[0] + 12) == foodY)) {		//if the head and food collide
			bodyX[length] = bodyX[length - 5];
			bodyY[length] = bodyY[length - 5];	//add an extra segment to the snake
			length++;							//increment length
			printf("\rscore: %d", (length - 20));		//print score number
			foodX = FoodRandom1(22);
			foodY = FoodRandom1(17);				//Randomise food coordinates
			
		}

		if (((bodyX[0] + 12) == foodV) && ((bodyY[0] + 12) == foodW)) {		//if the head and food collide
			bodyX[length] = bodyX[length - 5];
			bodyY[length] = bodyY[length - 5];	//add an extra segment to the snake
			length--;							//increment length
			printf("\rScore: %d", (length - 20));		//print score number
			foodW = FoodRandom2(22);
			foodV = FoodRandom2(17);				//Randomise food coordinates

		}

		setvisualpage(view);

		delayNum = log2((double)length / 10.0);
		delay(230.0 / delayNum);			//give user time to input control

		k = _kbhit();
		if (k == 1) {		//input check
			input = _getch();
			k = 0;
		}
		switch (input) {		//Checks if input is valid. If valid change direction of the snake.
		case(119): if (direction != 1) {		//up(w)
			direction = 0;
		}
				   break;
		case(115): if (direction != 0) {		//down(s)
			direction = 1;
		}
				   break;
		case(100): if (direction != 3) {		//right(d)
			direction = 2;
		}
				   break;
		case(97): if (direction != 2) {			//left(a)
			direction = 3;
		}
				  break;
		}

		for (i = (length - 1); i > 0; i--) {		//move body of snake
			bodyX[i] = bodyX[i - 2];
			bodyY[i] = bodyY[i - 2];
		}

		switch (direction) {	//moves snake's head to new position
		case(0): bodyY[0] -= 25;
			break;
		case(1): bodyY[0] += 25;
			break;
		case(2): bodyX[0] += 25;
			break;
		case(3): bodyX[0] -= 25;
			break;
		}
		for (i = 1; i < (length); i++) {	//check body collisions
			if ((bodyX[0] == bodyX[i]) && (bodyY[0] == bodyY[i])) {				//if head collides with body return 0 (lose)
				return 0;
			}
			if (((foodX - 12) == bodyX[i]) && ((foodY - 12) == bodyY[i])) {		//if spawns inside body, randomise position of food
				foodX = FoodRandom1(22);
				foodY = FoodRandom1(17);
			}
			if (((foodV - 12) == bodyX[i]) && ((foodW - 12) == bodyY[i])) {		//if spawns inside body, randomise position of food
				return 0;
			}
		}
		if ((bodyX[0] < 25) || (bodyX[0] > 590) || (bodyY[0] < 25) || (bodyY[0] > 440)) {	//if snake's head leaves boundary area, return 0 (lose)
			return 0;
		}
	}
}

void PrintSnake(int length, int bodyX[], int bodyY[], int headColour, int body1Colour, int body2Colour) {
	setfillstyle(0, headColour);				//head colour
	for (int i = 0; i < length; i++) {
		bar(bodyX[i], bodyY[i], (bodyX[i] + 24), (bodyY[i] + 24));		//show snake body

		if ((i % 4) == 0) {					//alternate colours of snake body (1 white, 3 blue reccurring)
			setfillstyle(0, body1Colour);
		}
		else {
			setfillstyle(0, body2Colour);
		}
	}
}

void ShowFood1(int foodX, int foodY) {
	setfillstyle(0, RED);
	setcolor(RED);
	fillellipse(foodX, foodY, 10, 10);

}

void ShowFood2(int foodV, int foodW) {
	setfillstyle(0, BLUE);
	setcolor(BLUE);
	fillellipse(foodV, foodW, 10, 10);

}

int FoodRandom1(int numSquares) {
	int a = ((((rand() % numSquares) + 1) * 25) + 12);
	return a;
}

int FoodRandom2(int numSquares) {
	int a = ((((rand() % numSquares) + 1) * 25) + 12);
	return a;
}


