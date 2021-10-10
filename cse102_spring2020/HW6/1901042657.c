#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Rand func is succesfull even without time lib. But for each compile, it gives same random values. To get different values in each compile, remove comment lines of line 5 and line 20 */
/* #include <time.h> */
#define N 5

typedef enum {left = 1, right, up, down} direction; /* Creating an enum type for directions */
void print_array(int arr[][N], int a);
int movement(int arr[][N], direction to_where, int x, int y, int a);
bool is_done(int arr[][N], int a);

int main()
{
	int first, second, i, j, k,
        temp[N*N], array[N][N], rand_index, arr_size=N*N;
	direction towards;
	printf("******************** LET'S PLAY A GAME! ********************\n"
		   "* TO WIN THE GAME CHANGE THE PUZZLE BELOW IN THE CORRECT ORDER *\n\n\n");
    /* srand(time(NULL)); */
    for(i=0; i<N*N; i++)    /* Filling the 1D array with numbers from 0 to array size's square(0 will be our empty cell)*/
        temp[i] = i;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++,arr_size--)   /* Shuffleing the 1D array with select a random index and assigning that index's value to array */
        {
            rand_index = (rand() % arr_size);
            array[i][j] = temp[rand_index];
            /* Here, a swap operation will be done to prevent get the same random index */
            for(k=0; k<arr_size-rand_index; k++)
                temp[rand_index+k] = temp[rand_index+k+1];  /* Used values will be lost with that operation */
        }
    }
	print_array(array, N); /* Printing the created array */
	if(is_done(array, N) == true) /* If created array is already ordered, than print a message and finish the program run */
	{
		printf("\nARRAY IS ALREADY ORDERED!\n");
		return 0;
	}
	do
	{
		printf("\nChoose a cell(first cell is 0,0): \n(Enter x:-1 when you want to give up)\nx(row): ");
		scanf("%d", &first);
		if(first == -1)
		{
			printf("\n******************** YOU GAVE UP! ********************\n");
			return 0;
		}
		printf("y(column): ");
		scanf("%d", &second);
        if(array[first][second] == 0)   /* If user choose empty cell, an error message will be printed and a new coordinate couple will be asked */
        {
            printf("\nYOU CHOSE EMPTY CELL!\n""CHOOSE AN APPROPRIATE CELL\n");
            continue;
        }
		printf("To which direction do you want to go(left = 1, right=2, up=3, down=4): ");
		scanf("%u", &towards);    /* Direction will be taken in enum type */
		movement(array, towards, first, second, N);   /* This func will execute movements */
		print_array(array, N);    /* Printging updated array each time */
	}
	while(is_done(array, N) != true); /* When array is ordered, is_done func return 0, unless it is 0, program will continue to run */
}

void print_array(int arr[][N], int a)
{
	int i,j,k;
	printf("\n");
	for(i=0; i<a; i++)
	{
		for(j=0; j<(5*a)+a+1; j++)    /* Each cell is a 5x5 squre */
        	printf("*");
        printf("\n");
        for(k=0; k<a; k++)
				printf("*     ");
			printf("*\n");
			for(k=0; k<a; k++)
				printf("*     ");
			printf("*\n");
		for(j=0; j<a; j++)
		{
			if(arr[i][j] >= 10)	/* According to number of digit (1 or 2) necesarry space amount will change */
				printf("*  %d ", arr[i][j]);
			else if(arr[i][j] == 0)
				printf("*     ");
			else
				printf("*  %d  ", arr[i][j]);
		}
		printf("*\n");
		for(k=0; k<a; k++)
			printf("*     ");
		printf("*\n");
		for(k=0; k<a; k++)
			printf("*     ");
		printf("*\n");
	}
	for(j=0; j<(5*a)+a+1; j++)
        	printf("*");
    printf("\n");
}


/* 
 * Parameters:
 * Array that we'll be changed.
 * The direction of the movement: towards {left, right, up, down} enumerated type.
 * Movement start location will be determined by user in main and pass this function.
*/
int movement(int arr[][N], direction to_where, int x, int y, int a)
{
	int possibe_mov_amount, s1, s2, count=0, i;
	switch(to_where)   /* There is 4 possible direction and I use switch case for them */
	{
		case 1: 
		possibe_mov_amount=y; /* Amount of possible movements, when it is end, that means invalid movement choice */
		do
		{ 
			y--;
			possibe_mov_amount--;
			count++;
			if(arr[x][y] == 0)
			{
				s1 = x;		s2 =y; /* Saving indexes belong to empty cell */
			}

		}
		while(arr[x][y] != 0 && possibe_mov_amount > 0);
		if(possibe_mov_amount == 0 && arr[x][y] != 0)
		{
			printf("\nTHIS MOVEMENT CAN'T BE DONE!\n""CHOOSE AN APPROPRIATE CELL\n");
			return 0;
		}
		for(i=0; i<count; i++,s2++)
		{
			*(*(arr+s1)+s2) = *(*(arr+(s1))+s2+1);
		}
		*(*(arr+s1)+s2) = 0;
		break;
		case 2: 
		possibe_mov_amount=(a-1)-y;
		do
		{ 
			y++;
			possibe_mov_amount--;
			count++;
			if(arr[x][y] == 0)
			{
				s1 = x;		s2 =y;
			}
		}
		while(arr[x][y] != 0 && possibe_mov_amount > 0);
		if(possibe_mov_amount == 0 && arr[x][y] != 0)
		{
			printf("\nTHIS MOVEMENT CAN'T BE DONE!\n""CHOOSE AN APPROPRIATE CELL\n");
			return 0;
		}
		for(i=0; i<count; i++,s2--)
		{
			*(*(arr+s1)+s2) = *(*(arr+(s1))+s2-1);
		}
		*(*(arr+s1)+s2) = 0;
		break;
		case 3: 
		possibe_mov_amount=x;
		do
		{ 
			x--;
			possibe_mov_amount--;
			count++;
			if(arr[x][y] == 0)
			{
				s1 = x;		s2 =y;
			}

		}
		while(arr[x][y] != 0 && possibe_mov_amount > 0);
		if(possibe_mov_amount == 0 && arr[x][y] != 0)
		{
			printf("\nTHIS MOVEMENT CAN'T BE DONE!\n""CHOOSE AN APPROPRIATE CELL\n");
			return 0;
		}
		for(i=0; i<count; i++,s1++)
		{
			*(*(arr+s1)+s2) = *(*(arr+(s1+1))+s2);
		}
		*(*(arr+s1)+s2) = 0;
		break;
		case 4: 
		possibe_mov_amount=(a-1)-x;
		do
		{ 
			x++;
			possibe_mov_amount--;
			count++;
			if(arr[x][y] == 0)
			{
				s1 = x;		s2 =y;
			}
		}
		while(arr[x][y] != 0 && possibe_mov_amount > 0);
		if(possibe_mov_amount == 0 && arr[x][y] != 0)
		{
			printf("\nTHIS MOVEMENT CAN'T BE DONE!\n""CHOOSE AN APPROPRIATE CELL\n");
			return 0;
		}
		for(i=0; i<count; i++,s1--)
		{
			*(*(arr+s1)+s2) = *(*(arr+(s1-1))+s2);
		}
		*(*(arr+s1)+s2) = 0;
		break;
	}
	return 1;
}
bool is_done(int arr[][N], int a)
{
	int i,j,res=0;
	for(i=0; i<a; i++)
	{
		for(j=0; j<a-1; j++)
		{
			if(arr[i][j] < arr[i][j+1] && arr[i][j] !=0 && arr[i][j+1] != 0)
				res++;
		}
	}
	/* 2x2 arrays has a special case. They don't obey this formula. So I define a special case for them. */
	if(a == 2)
	{
		if(arr[0][0] == 0 && arr[0][1] == 1 && arr[1][0] == 2 && arr[1][1] == 3)
		{
			printf("\n******************** YOU WIN! ********************\n");
			return true;
		}
		else if(arr[0][0] == 1 && arr[0][1] == 0 && arr[1][0] == 2 && arr[1][1] == 3)
		{
			printf("\n******************** YOU WIN! ********************\n");
			return true;
		}
		else if(arr[0][0] == 1 && arr[0][1] == 2 && arr[1][0] == 0 && arr[1][1] == 3)
		{
			printf("\n******************** YOU WIN! ********************\n");
			return true;
		}
		else if(arr[0][0] == 1 && arr[0][1] == 2 && arr[1][0] == 3 && arr[1][1] == 0)
		{
			printf("\n******************** YOU WIN! ********************\n");
			return true;
		}
		else
			return false;
	}
	if(res == a*(a-1)-2)
	{
		printf("\n******************** YOU WIN! ********************\n");
		return true;	/* This means we've completed the game */
	}
	else
		return false;	/* This means we should continue */
}

