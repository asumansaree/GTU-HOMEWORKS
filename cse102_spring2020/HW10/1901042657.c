/* I got a segmentation fault that I didn't detect. 
   Although taking data is successful and my functions works fine in limited size of arrays, big files leads problems. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	double budget;
	int genre;	
	char name[50];
	double score;
	int year;
}Movie;

Movie *Movies;
FILE *fptr;
int num_of_genres=0;
char filename[20];

int num_of_char_in_a_line(int *in_f, int *name_letters); 
void fill_name(char *str, int which_row);
void fill_budget(char *str, int which_row);
void fill_score(char *str, int which_row);
void fill_year(char *str, int which_row);
void fill_genre(char *str, int which_row, char **genres_buffer, char **genres_available);
void one();
//void three(int row_num);
int menu(int row_num);

int main() 
{
	int count_row=1, count_row2=1, len, in_file=0, first_row_len, name_let;
	char *line;
 	printf("Type the filename to open in read mode\n");
	scanf("%s", filename); 
	fptr = fopen(filename, "r"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file %s \n", filename); 	exit(1);
	} 
	/*
	 There should be "exactly" the same number of elements in dynamically allocated struct array "as the number of lines in the file".
	 So first I found how many row file has and then allocate memory in that amount in struct array which is Movies here.
	*/
	do
	{
		len = num_of_char_in_a_line(&in_file,&name_let);
		if(in_file == 0)	/* Titles will not be counted as a part of the associated row because they are not data. */
			first_row_len = len;	/* After I found total row number, I'll start to read data from first_row_len */
		fseek(fptr, (in_file), SEEK_SET);
	  	in_file += len;
	  	count_row++;
	}while(in_file != -1);	/* in_file func will return -1 when it reachs eof */

	Movies = (Movie *)malloc((count_row)*sizeof(Movie));	/* Now, we now how many row are there in our file. Set the file cursor at the beginning with fseek. */
	char **genres_buffer = malloc(count_row * 200);  
	char **genres_available = malloc(count_row * 200); 
	in_file=first_row_len;
	do
	{
		len = num_of_char_in_a_line(&in_file,&name_let);
		/*name_let --->  Program starts to count when it understand it is name part and it stores lenght of the name in name_let variable to allocate memory. */
		/* Actually, allocating name array in struct array in the below way should work but it didn't. I wish I can see what is the problem... */
		//(Movies[count_row2].name) = ((*Movie).name)malloc((name_let)*sizeof(char));
		line = (char *)malloc(len*sizeof(char));
		fseek(fptr, (in_file), SEEK_SET);
		fgets(line, len, fptr);

	  	if(count_row2 < count_row-2)
	  	{
	  		fill_name(line, count_row2);
	  	    fill_budget(line, count_row2);
	  	    fill_score(line, count_row2);
	  	    fill_year(line, count_row2);
	  	    //fill_genre(line, count_row2, genres_buffer, genres_available);
	  	}

	  	in_file += len;
	  	count_row2++;
	  	free(line);
	  	//free(Movies[count_row2].name);
	}while(in_file != -1);
	/* Due to beginning parts didn't work properly, I add comments to this functions */
	/*
	do
	{
		int ret = menu(count_row);
	}while(ret == 0);
	*/
	free(Movies);
	free(genres_buffer);
	free(genres_available);
}	
int num_of_char_in_a_line(int *in_f, int *name_letters)	/* From the number of chars, first I calculated mumber of lines */
{
	fseek(fptr, *(in_f), SEEK_SET);
	char c;
	int count_char=0,comma=0;
	do 
	{
	    c = fgetc(fptr);
		if(feof(fptr)) 
	    {
	    	(*in_f) = -1;
	    	break ;
	    }
	    else
	    {
	    	if(comma == 2 && c != ',')
	    		(*name_letters)++;
	    	else if(c == ',')
	    		comma++;	/* After 2 comma are read, name part will begin. We need how many char are there in name to make it dinamically allocated. */
	    	count_char++;
	    }
	    //printf("%d. harf: %c\n",count_char, c);
    }while(c != '\n');
    return count_char;
}

void fill_name(char *str, int which_row)
{
	char str_cpy[300];
	strcpy(str_cpy, str);
	//   First we should seperate this one line according to titles. 
	char *token = strtok(str_cpy, ",");
	int count_title=1, len_token;
	char temp_str[100];
    // loop through the string to extract all other tokens
    while(count_title != 3) 
    {
       token = strtok(NULL, ",");
       len_token = strlen(token);
       count_title++;
       if(count_title == 3)
       {
       		strncpy(temp_str, token, len_token);
       		temp_str[len_token] = '\0';
       }
    }
	strncpy(Movies[which_row].name, temp_str, len_token+1); 
}

void fill_budget(char *str, int which_row)
{
	char str_cpy[300];
	strcpy(str_cpy, str);
	double temp;
	char *token = strtok(str_cpy, ",");
	temp = atof(token);
	Movies[which_row].budget = temp; 
}


void fill_genre(char *str, int which_row, char **genres_buffer, char **genres_available)
{
	char str_cpy[300];
	strcpy(str_cpy, str);
	char *token = strtok(str_cpy, ",");
	int count_title=1, len_token, i;
	char temp_str[100];
    // loop through the string to extract all other tokens
    while(count_title != 2) 
    {
       token = strtok(NULL, ",");
       len_token = strlen(token);
       count_title++;
       if(count_title == 2)	/* This string is belong to genre column */
       {
       		strncpy(temp_str, token, len_token);
       		temp_str[len_token] = '\0';
       }
    }
    genres_buffer[which_row] = (char *)malloc(len_token+1);
    Movies[which_row].genre = which_row;
    strncpy(Movies[which_row].name, temp_str, len_token+1); 
    if(which_row == 0)
    	strncpy(genres_buffer[which_row], temp_str, len_token+1);
    else /* Then we should check whether it is entered before or not. */
    {
    	for(i=0; i<which_row; i++)
    	{
    		if(strcmp(temp_str, genres_buffer[i]) != 0)
    		{
    			strcpy(genres_available[num_of_genres], temp_str);
    			num_of_genres++;
    		}
    	}
    }

	
}

void fill_score(char *str, int which_row)
{
	char str_cpy[300];
	strcpy(str_cpy, str);
	char *token = strtok(str_cpy, ",");
	int count_title=1;
	double temp;
    while (token != NULL) 
    {
        token = strtok(NULL, ",");
        count_title++;
        if(count_title == 4)
        {
        	temp = atof(token);
			Movies[which_row].score = temp; 
        }
    }
}

void fill_year(char *str, int which_row)
{
	char str_cpy[300];
	strcpy(str_cpy, str);
	char *token = strtok(str_cpy, ",");
	int count_title=1;
	int temp;
    while (token != NULL) 
    {
        token = strtok(NULL, ",");
        count_title++;
        if(count_title == 5)
        {
        	temp = atoi(token);
			Movies[which_row].year = temp; 
        }
    }
}

int menu(int row_num)
{
	int cho;
	printf("\t1. List of the Sorted Data\n""\t2. List of the Genres\n""\t3. List of the Movie Through the Years\n"
		   "\t4. List of the Movie Through the Scores\n""\t5. All Informations of a Single Movie\n""\t6. Average of the IMDB Scores\n"
		   "\t7. Frequence of the Genres\n""\t8. Exit\n""Please select an operation:  ");
	scanf("%d", &cho);
	switch(cho)
	{
		case 1: one();
				return 0;
				break;
		case 2: return 0;
				break;
		case 3: //three(row_num);
				return 0;
				break;
		case 4: return 0;
				break;
		case 5: return 0;
				break;
		case 6: return 0;
				break;
		case 7: return 0;
				break;
		case 8: return -1;
				break;
		default: printf("\nTRY AGAIN\n");
				 return 0;
	}
}

/*
void one()
{
	int cho, cho2, min,max,i;
	printf("\t1. Budget\n""\t2. Genre\n""\t3. Name\n"
		   "\t4. Score\n""\t5. Year\n""Please select an operation:  ");
	scanf("%d", &cho);
	printf("1. Single Selection\n2. Multiple Selection\n""Please select an operation:  ");
	scanf("%d", &cho2);
	if(cho2 == 1)
	{
		printf("Enter value: \n");
		scanf("%d", &min);
		printf("%d. Movie\n", min);
		printf("%lf\n", Movies[i].budget);
		//printf("%s ", Movies[i].genre);
		printf("%s\n", Movies[i].name);
		printf("%lf\n", Movies[i].score);
		printf("%d\n", Movies[i].year);
	}
	else
	{
		printf("Enter start value: \n");
		scanf("%d", &min);
		printf("Enter end value: \n");
		scanf("%d", &max);
		for(i=min; i<=max; i++)
		{
			printf("%d. Movie\n", i);
			printf("%lf\n", Movies[i].budget);
			//printf("%s ", Movies[i].genre);
			printf("%s\n", Movies[i].name);
			printf("%lf\n", Movies[i].score);
			printf("%d\n", Movies[i].year);
		}
	}
}
*/

/*
void three(int row_num)
{
	int year, us, i;
	printf("Enter a year\n");
	scanf("%d", &year);
	printf("Press (0) for Until and (1) for Since\n");
	scanf("%d", &us);
	if(us == 0)
	{
		for(i=0; i<row_num; i++)
		{
			if(Movies[i].year <= year)
				printf("%s\n", Movies[i].name);
		}
	}
	else
	{
		for(i=0; i<row_num; i++)
		{
			if(Movies[i].year >= year)
				printf("%s\n", Movies[i].name);
		}
	}
}
*/