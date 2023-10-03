/*Valentine Gundorov*/
/*Reversi Game*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define COLS 20

void printBoard(int num, char mat[][COLS]);  
char fillboard(char mat[][COLS], int choise);
int actual_Move(char mat[][COLS], char ch, int row, int col, int size);     //this function checking leagle move and if step is legal it changes the gameboard
void score(char mat[][COLS], char name1, char name2, int count);      // this function gives a final result for winner
int countValibleMoves(char mat[][COLS], int size, char ch);   //this function count for X or 0 have for valible moves
int legalStep(char mat[][COLS], char ch, int row, int col, int size); //this function chech if X or 0 have valible move

char mat[COLS][COLS];

void main()
{
	int exit = 1,choise, count = 0, row, col;
	char name1[20],name2[20];
	char ch;
	int countNumber = 0;
	while (1)
	{
		printf("Select board size :\n"
			"0. Exit\n"
			"1. 5x5\n"
			"2. 15x15\n"
			"3. 20x20\n");
		scanf("%d", &choise);
		if (choise >= 0 && choise <= 3)  
			break;
		else   
			printf("Invalid option.\n");
	}
	if (choise == 0)
		return;
	printf("Enter first player name :");
	scanf("%s", name1);
	printf("Enter second player name :");
	scanf("%s", name2);
	printf("\n");
	switch (choise)
	{
		case 1:
			choise = 5;
			fillboard(mat, choise);
			printBoard(choise, mat);
			break;
		case 2:
			choise = 15;
			fillboard(mat, choise);
			printBoard(choise, mat);
			break;
		case 3:
			choise = 20;
			fillboard(mat, choise);
			printBoard(choise, mat);
			break;
	}

	while (count < (choise * choise) - 4 || (countValibleMoves(mat, choise, 'X')!= 0 && countValibleMoves(mat, choise, '0') != 0))
	{
		if (countValibleMoves(mat, choise, '0') == 0 && countValibleMoves(mat, choise, 'X') == 0)
		{
			score(mat, name1, name2, count);
			break;
		}

		if (count % 2 != 0)
		{
			ch = '0';
			if (countValibleMoves(mat, choise, '0') == 0)
			{
				printf("Player %s has no move\n", name2);
				count++;
				countNumber = 1;
			}
			else
			{
				if (countNumber == 2)
				{
					countNumber = 0;
					count--;
				}
				printf("Player %s (0) turn\n", name2);
				printf("Enter your move (row + column):");
				scanf("%d %d", &row, &col);

				if (actual_Move(mat, ch, row - 1, col - 1, choise) != 0)
				{
					count++;
					printBoard(choise, mat);
				}
				else
					printf("Invalid move.\n");
			}
		}
		if (count % 2 == 0)
		{
			ch = 'X';
			if (countValibleMoves(mat, choise, 'X') == 0)
			{
				printf("Player %s has no move\n", name1);
				count++;
				countNumber = 2;
			}
			else
			{
				if (countNumber == 1)
				{
					countNumber = 0;
					count--;
				}
				printf("Player %s (X) turn\n", name1);
				printf("Enter your move (row + column):");
				scanf("%d %d", &row, &col);

				if (actual_Move(mat, ch, row - 1, col - 1, choise) != 0)
				{
					count++;
					printBoard(choise, mat);
				}
				else
					printf("Invalid move.\n");
			}
		}
	}
	score(mat, name1, name2,count);
}

int countValibleMoves(char mat[][COLS], int size, char ch)
{
	int i, j;
	int count = 0;
	for ( i = 1; i <= size; i++)
	{
		for ( j = 1; j <= size; j++)
		{
			if (legalStep(mat, ch, i - 1, j - 1, size) != 0)
			{
				count++;
			}
		}
	}
	return count;
}

void score(char mat[][COLS], char name1 , char name2, int count)
{
	int countX = 0;
	int count0 = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (mat[i][j] == 'X')
			{
				countX++;
			}
			if (mat[i][j] == '0')
			{
				count0++;
			}
		}
	}
	if (count0 > countX)
	{
		printf("player %s Won!\n", name2);
	}
	if (count0 < countX)
	{
		printf("player %s Won!\n", name1);
	}

}

int actual_Move(char mat[][COLS], char ch, int row, int col, int size)
{
/*
	6	3	7
	 \  |  /
	  \ | /
	1-------2
	  / | \
	 /  |  \
	8   4   5
				*/
	char letter1 = 'X';
	char letter2 = '0';
	if (ch == '0')
	{
		letter1 = '0';
		letter2 = 'X';
	}
	int count = 1;
	int stepcounter = 0;

	if (mat[row][col] == '.')
	{
		if (mat[row][col - 1] == letter2)
		{
			for (int i = 0; col-count >= 0 ; i++)
			{
				if (mat[row][col-count]==letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row][col - i] = letter1;
					}
					stepcounter++;   //1
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row][col+1] == letter2)
		{
			for (int i = 0; col+count <= size; i++)
			{
				if (mat[row][col+count] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row][col + i] = letter1;
					}
					stepcounter++;   //2
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col] == letter2)
		{
			for (int i = 0; row - count>=0; i++)
			{
				if (mat[row - count][col] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row-i][col] = letter1;
					}
					stepcounter++;   //3
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col] == letter2)
		{
			for (int i = 0; row + count<= size; i++)
			{
				if (mat[row + count][col] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row+i][col] = letter1;
					}
					stepcounter++;   //4
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col - 1] == letter2)
		{
			for (int i = 0; row - count >= 0 || col-count >=0 ; i++)
			{
				if (mat[row - count][col-count] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row-i][col - i] = letter1;
					}
					stepcounter++;   //6
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col-1] == letter2)
		{
			for (int i = 0; row + count <= size || col-count>=0; i++)
			{
				if (mat[row + count][col-count] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row + i][col - i] = letter1;
					}
					stepcounter++;   //8
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col + 1] == letter2)
		{
			for (int i = 0; row + count<= size || col +count <= size; i++)
			{
				if (mat[row + count][col + count] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row + i][col + i] = letter1;
					}
					stepcounter++;   //5
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col + 1] == letter2)
		{
			for (int i = 0; row - count >= 0 || col+count <= size; i++)
			{
				if (mat[row - count][col + count] == letter1)
				{
					for (int i = 0; i <= count; i++)
					{
						mat[row - i][col + i] = letter1;
					}
					stepcounter++;   //7
					break;
				}
				count++;
			}
		}
	}

	return stepcounter;
}

void printBoard(int num, char mat[][COLS]) 
{
	int number = 0;
	printf("  ");
	for (int i = 1; i <= num; i++)
	{
		printf(" %2d", i);
	}
	printf("\n");
	for (int i = 0 ; i < num ; i++)
	{
		printf("%2d ", ++number);
		
		for (int j = 0; j < num; j++)
		{
			printf(" %c ", mat[i][j]);
		}
		printf("\n");
	}

}

char fillboard(char mat[][COLS] , int choise)
{
	int i, j;
	for ( i = 0; i < choise; i++)
	{
		for ( j = 0; j < choise; j++)
		{
			mat[i][j] = '.';
		}
	}
	mat[choise / 2-1][choise / 2-1] = 'X';
	mat[choise/2-1][choise /2] = '0';
	mat[choise /2][choise /2] = 'X';
	mat[choise /2][choise /2-1] = '0';
	
	return mat;
}

int legalStep(char mat[][COLS], char ch, int row, int col, int size)
{
	char letter1 = 'X';
	char letter2 = '0';
	if (ch == '0')
	{
		letter1 = '0';
		letter2 = 'X';
	}
	int count = 1;
	int stepcounter = 0;

	if (mat[row][col] == '.')
	{
		if (mat[row][col - 1] == letter2)
		{

			for (int i = 0; col - count >= 0; i++)
			{
				if (mat[row][col - count] == letter1)
				{
					stepcounter++;   //1
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row][col + 1] == letter2)
		{
			for (int i = 0; col + count <= size; i++)
			{
				if (mat[row][col + count] == letter1)
				{
					stepcounter++;   //2
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col] == letter2)
		{
			for (int i = 0; row - count >= 0; i++)
			{
				if (mat[row - count][col] == letter1)
				{
					stepcounter++;   //3
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col] == letter2)
		{
			for (int i = 0; row + count <= size; i++)
			{
				if (mat[row + count][col] == letter1)
				{
					stepcounter++;   //4
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col - 1] == letter2)
		{
			for (int i = 0; row - count >= 0 || col - count >= 0; i++)
			{
				if (mat[row - count][col - count] == letter1)
				{
					stepcounter++;   //6
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col - 1] == letter2)
		{
			for (int i = 0; row + count <= size || col - count >= 0; i++)
			{
				if (mat[row + count][col - count] == letter1)
				{
					stepcounter++;   //8
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row + 1][col + 1] == letter2)
		{
			for (int i = 0; row + count <= size || col + count <= size; i++)
			{
				if (mat[row + count][col + count] == letter1)
				{
					stepcounter++;   //5
					break;
				}
				count++;
			}
		}
		count = 1;
		if (mat[row - 1][col + 1] == letter2)
		{
			for (int i = 0; row - count >= 0 || col + count <= size; i++)
			{
				if (mat[row - count][col + count] == letter1)
				{
					stepcounter++;   //7
					break;
				}
				count++;
			}
		}
	}
	return stepcounter;
}