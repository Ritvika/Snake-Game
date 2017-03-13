#include<iostream>
#include<conio.h>
/* For slowing the movement of the snake by milliseconds*/
#include<thread>
#include<chrono>
/*------------------------------------------------------*/
using namespace std;
bool gameOver;
const int length = 20;
const int breadth = 20;
int axis1, axis2, point_axis1, point_axis2, points;
enum direction { stop = 0, left, right, up, down };
direction dir;
int tail1[100], tail2[100], tail;

//Setting up the intial dimensions and total points.
void SetUp()
{
	gameOver = false;
	dir = stop;
	axis1 = length / 2;
	axis2 = breadth / 2;

	//Create point P at a random location inside the box.
	point_axis1 = rand() % length;
	point_axis2 = rand() % breadth;

	//Initial total points for a player will be 0.
	points = 0;
}

//Drawing the box and snake on every move.
void Draw()
{
	system("cls");

	//Drawing boundary.
	for (int i = 0; i < length + 2; i++)
		cout << "o";
	cout << endl;

	//Draw Snake and side boundaries. 
	for (int i = 0; i < breadth; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (j == 0)
				cout << "o";
			if (i == axis2 && j == axis1)  //Snake header.
				cout << "H";
			else if (i == point_axis2 && j == point_axis1)  //Points on board.
				cout << "P";
			else
			{
				bool print = false;                  //Grow tail when Head intersects with a point.
				for (int k = 0; k < tail; k++)
				{					
					if (tail1[k] == j && tail2[k] == i)
					{
					cout << "@";
					print = true;
					}					
				}
				if (!print)
					cout << " ";
			}
			if (j == length - 1)
				cout << "o";			
		}
		cout << endl;
	}

	//Drawing boundary.
	for (int i = 0; i < breadth+2; i++)
		cout << "o";
	cout << endl;

	//Display total points.
	cout << "Total Points: " << points;
}

//Add directions.
void Input()
{
	if (_kbhit())
	{
		switch (_getch())                  
		{
		case 'a':                             //a for Left direction.
			dir = direction::left;
			break;
		case 'w':                             //w for Up direction.
			dir = direction::up;
			break;
		case 'd':                             //d for Right direction.
			dir = direction::right;
			break;
		case 's':                             //s for Down direction.
			dir = direction::down;
			break;
		case 'x':                             //x for Game Over.
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prev1 = tail1[0];
	int prev2 = tail2[0];
	int temp_prev1, temp_prev2;
	tail1[0] = axis1;
	tail2[0] = axis2;	

	//To add tail the previous position.
	for (int i = 1; i < tail; i++)
	{
		temp_prev1 = tail1[i];
		temp_prev2 = tail2[i];
		tail1[i] = prev1;
		tail2[i] = prev2;
		prev1 = temp_prev1;
		prev2 = temp_prev2;
	}
	switch (dir)
	{
	case direction::left:
		axis1--;
		break;
	case direction::up:
		axis2--;
		break;
	case direction::right:
		axis1++;
		break;
	case direction::down:
		axis2++;
		break;
	default:		
		break;
	}

	/*If touching any wall means Game Over*/
	//if (axis1 < 0 || axis2 < 0 || axis1 > length || axis2 > breadth)
		//gameOver = true;

	//If touching any wall should allow the snake to enter the box from the opposite side.
	if (axis1 >= length)
		axis1 = 0;
	else if (axis1 < 0)
		axis1 = length - 1;
	if (axis2 >= breadth)
		axis2 = 0;
	else if (axis2 < 0)
		axis2 = breadth - 1;

	//When snake head touches the tail then, Game Over.
	for (int i = 0; i < tail; i++)
		if (tail1[i] == axis1 && tail2[i] == axis2)
			gameOver = true;

	//When snake head touches point P, add 10 points to the total.
	if (axis1 == point_axis1 && axis2 == point_axis2)
	{
		points = points + 10;
		point_axis1 = rand() % length;
		point_axis2 = rand() % breadth;
		tail++;
	}
}
int main()
{
	SetUp();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		this_thread::sleep_for(chrono::milliseconds(200)); //Slow down movement of the snake.
	}
	return 0;
}
