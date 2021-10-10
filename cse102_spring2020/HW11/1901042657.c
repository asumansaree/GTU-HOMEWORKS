#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 200

struct Movie_Budget
{
    int budget, year;
    char name[N];
    struct Movie_Budget *next;
};

struct Movie_Name
{
    char name[N];
    char genre[N];
    double score;
    struct Movie_Name *next;
};

struct record_genre     /* To keep the genres and their occurences I create an extra struct */
{
    int each_genre;
    char genre_type[N];
    struct record_genre *next;
};

int num_of_char_in_a_line(int *in_f, int *name_letters, int *unk_stat);
void newNodeBudget(struct Movie_Budget **head1, int budget, int year, char *name);
void newNodeName(struct Movie_Name **head2, char *name, char *genre, double score);
void newNodeGenre(struct record_genre **head3, char *genre);
void fill_name(char *str, struct Movie_Budget **headB, struct Movie_Name **headN, int unk_stat, struct record_genre **head3);

int menu(struct Movie_Budget *head1 ,struct Movie_Name *head2, struct record_genre *head3);
void one(struct Movie_Budget *head1 ,struct Movie_Name *head2);
void two(struct record_genre *head3);
void three(struct Movie_Budget *head1);
void four(struct Movie_Name *head2);
void five(struct Movie_Budget *head1 ,struct Movie_Name *head2);
void six(struct Movie_Name *head2);
void seven(struct record_genre *head3);

void sort_for_one(struct Movie_Budget *head1, struct Movie_Name *head2, int which);

FILE *fptr;
char filename[N];
int total_row=1;

int main()
{
    int count_row=1, len, in_file=29, name_let, cho;    /* in_file is a variable that keeps the cursor' location in the file. (I didn't include titles to that)*/
    char *line; /* Line will be dynamically allocated for each row. */
    printf("Type the filename to open in read mode\n");
    scanf("%s", filename); 
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file %s \n", filename);     
        exit(1);
    } 
    struct Movie_Budget *head1 = NULL;  /* LinkedLists are created in the main. So that they can be seen by other functions, too.*/
    struct Movie_Name *head2 = NULL;
    struct record_genre *head3 = NULL;
    do
    {
        int unknown_stat=0;     /* If the budget data is unknown, unknown_stat will be -1 */
        fseek(fptr, in_file, SEEK_SET); /* I'm setting the cursor in the file at the beginning of the line each time. */
        len = num_of_char_in_a_line(&in_file,&name_let,&unknown_stat);  /* Find lenght of the current row for line allocation */
        if(in_file != -1)   /* -1 means file is over */
        {
            line = (char *)malloc(len*sizeof(char));
            fseek(fptr, in_file, SEEK_SET);
            fgets(line, len, fptr);
            in_file += len; /* Cursor will be updated each time */
            fill_name(line, &head1, &head2, unknown_stat, &head3);  /* Movie records will be made in this function */
            free(line);
        }
    }while(in_file != -1);

    struct Movie_Budget *count = head1;
    while(count->next != NULL)
    {
        total_row++;    /* Counting of the total row number */
        count = count->next;
    }
    
    do
    {
        cho = menu(head1, head2, head3);    /* Until user enters exit, menu function will be called. */
    }while(cho == 0);
    fclose(fptr);
    free(head1);
    free(head2);
    free(head3);
}

int num_of_char_in_a_line(int *in_f, int *name_letters, int *unk_stat)  
{
    fseek(fptr, *(in_f), SEEK_SET);
    char c;
    int count_char=0,comma=0;
    do 
    {
        c = fgetc(fptr);
        if(feof(fptr)) 
        {
            (*in_f) = -1;   /* File is over */
            break ;
        }
        else
        {
            if(comma == 0 && c == 'u')  /* To make sortings easier, unknown values are recorded as -1 (in last hw instructor said this) */
                (*unk_stat) = -1;
            if(comma == 2 && c != ',')  /* lenght of the "name" variable in each line is counted to allocate string dynamically. */
                (*name_letters)++;
            else if(c == ',')
                comma++;    
            count_char++;
        }
    }while(c != '\n');
    return count_char;  /* Current line's char elements number is returning. */
}

void newNodeBudget(struct Movie_Budget **head1, int budget, int year, char *name)   /* Adding new node to first linked list */
{
    struct Movie_Budget *newNode = malloc(sizeof(struct Movie_Budget));
    newNode->budget = budget;   /* Taking data for node that will be added now */
    newNode->year = year;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    if(*head1 == NULL)  /* If it is first entry, directly record it */
         *head1 = newNode;
    else
    {
        struct Movie_Budget *lastNode = *head1;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;
        lastNode->next = newNode;
    }
}

void newNodeName(struct Movie_Name **head2, char *name, char *genre, double score)   /* Adding new node to second linked list */
{
    struct Movie_Name *newNode = malloc(sizeof(struct Movie_Name));
    strcpy(newNode->name, name);    /* Taking data for node that will be added now */
    strcpy(newNode->genre, genre);
    newNode->score = score;
    newNode->next = NULL;
    if(*head2 == NULL)  /* If it is first entry, directly record it */
         *head2 = newNode;
    else
    {
        struct Movie_Name *lastNode = *head2;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;
        lastNode->next = newNode;
    }
}

void newNodeGenre(struct record_genre **head3, char *genre)     /* Each new genre are added to struct record_genre here. 
                                                                   Update of already existing data is not here, it's in below. */
{  
    struct record_genre *newNode = malloc(sizeof(struct record_genre));
    strcpy(newNode->genre_type, genre);
    newNode->each_genre = 1;
    newNode->next = NULL;
    if(*head3 == NULL)
        *head3 = newNode;
    else
    {
        struct record_genre *lastNode = *head3;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;
        lastNode->next = newNode;
    }
}

void fill_name(char *str, struct Movie_Budget **headB, struct Movie_Name **headN, int unk_stat, struct record_genre **head3)
{
    int is_name_recorded=0, is_genre_recorded=0,update_this, i=1, j=1;
    double scr;
    char str_cpy1[N], str_cpy2[N], str_cpy3[N], str_cpy4[N], str_cpy5[N];  /* These will be used as buffer */
    strcpy(str_cpy1, str);
    strcpy(str_cpy2, str);
    strcpy(str_cpy3, str);
    strcpy(str_cpy4, str);
    strcpy(str_cpy5, str);
    /**************************NAME**************************/
    char *token1;
    token1 = strtok(str_cpy1, ",");
    int count_name=1, len_token;
    char temp_str1[N];
    while(count_name != 3) /* I thought count_name, count_score etc variables as blocks and I gave number to them as 1 2 3 4 5 */
    {
       token1 = strtok(NULL, ",");
       len_token = strlen(token1);
       count_name++;
       if(count_name == 3)  /* When block 3 which is name block is reached, we should store that data */
       {
            strncpy(temp_str1, token1, len_token);
            temp_str1[len_token] = '\0';
       }
    }
    /**************************BUDGET**************************/
    int temp2;
    if(unk_stat == 0)   /* Budget data exists */
    {
        char *token2 = strtok(str_cpy2, ",");
        temp2 = atoi(token2);
    }
    else                /* Budget data is unknown and I assign -1 to it. Hence, ordering unknowns will be got easier. */
        temp2 = -1;
    /**************************YEAR**************************/
    char *token3 = strtok(str_cpy3, ",");
    int count_year=1;
    int temp3;
    while (token3 != NULL) 
    {
        token3 = strtok(NULL, ",");
        count_year++;
        if(count_year == 5)
            temp3 = atoi(token3);
    }
    /**************************GENRE**************************/
    char *token2 = strtok(str_cpy4, ",");
    int count_genre=1;
    char temp_str2[N];
    while(count_genre != 2) 
    {
       token2 = strtok(NULL, ",");
       len_token = strlen(token2);
       count_genre++;
       if(count_genre == 2)
       {
            strncpy(temp_str2, token2, len_token);
            temp_str2[len_token] = '\0';
       }
    }
    /**************************SCORE**************************/
    char *token4 = strtok(str_cpy5, ",");
    int count_score=1;
    while (token4 != NULL) 
    {
        token4 = strtok(NULL, ",");
        count_score++;
        if(count_score == 4)
            scr = atof(token4);
    }
    /* Control part for whether entries are recorded before or not */

    struct Movie_Budget *buffer = *headB;
    while(buffer != NULL)
    {
        if(strcmp(buffer->name, temp_str1) == 0)
        {
            is_name_recorded=1;
            update_this = i;
        }
        buffer = buffer->next;
        i++;
    }
    if(is_name_recorded == 0)       /* If the name records first time, take it's data */
    {
        newNodeBudget(headB, temp2, temp3, temp_str1);
        newNodeName(headN, temp_str1, temp_str2, scr);
    }
    else        /* If the name records before, update existing data */
    {
        /* First we have to reach the node that will be updated */
        struct Movie_Budget *buffer2 = *headB;
        for(i=1; i<update_this; i++)
            buffer2 = buffer2->next;
        /* Now our cursor is at desired node */
        buffer2->budget = temp2;
        buffer2->year = temp3;
        strcpy(buffer2->name, temp_str1);

        struct Movie_Name *buffer3 = *headN;
        for(i=1; i<update_this; i++)
            buffer3 = buffer3->next;
        buffer3->score = scr;
        strcpy(buffer3->genre, temp_str2);
    }

    /* We will make same thing that was done on name to genre struct */
    struct record_genre *buff = *head3;
    while(buff != NULL)
    {
        if(strcmp(buff->genre_type, temp_str2) == 0)
        {
            is_genre_recorded=1;
            update_this = j;
        }
        buff = buff->next;
        j++;
    }
    if(is_genre_recorded == 0)      /* If the genre records first time, take it's data */
        newNodeGenre(head3, temp_str2);
    else 
    {
        struct record_genre *buff2 = *head3;
        for(i=1; i<update_this; i++)
            buff2 = buff2->next;
        /* Now our cursor is at desired node */
        (buff2->each_genre)++;  /* Increasing the value in already existed genre */
    }
}

int menu(struct Movie_Budget *head1 ,struct Movie_Name *head2, struct record_genre *head3)
{
    int cho;
    printf("\t1. List of the Sorted Data\n""\t2. List of the Genres\n""\t3. List of the Movie Through the Years\n"
           "\t4. List of the Movie Through the Scores\n""\t5. All Informations of a Single Movie\n""\t6. Average of the IMDB Scores\n"
           "\t7. Frequence of the Genres\n""\t8. Exit\n""Please select an operation:  ");
    scanf("%d", &cho);
    switch(cho)
    {
        case 1: one(head1, head2);                  return 0;                break;
        case 2: two(head3);                         return 0;                break;
        case 3: three(head1);                       return 0;                break;
        case 4: four(head2);                        return 0;                break;
        case 5: five(head1, head2);                 return 0;                break;
        case 6: six(head2);                         return 0;                break;          
        case 7: seven(head3);                       return 0;                break;
        case 8: /*This is for exit*/                return -1;               break;
        default: printf("\nTRY AGAIN\n");           return 0;       
    }
}
/* There were no clean explaination about this part. I made it according to previous hw's pdf */
void one(struct Movie_Budget *head1 ,struct Movie_Name *head2)      
{
    /* Printfs are explaining what I've done here, comment lines are uncesesarry for function one(just for this function)
       Basic algorithm: 
       * Ask user something and chech whether it is an appropriate entry, is exist in file, is right etc.
       * Do sorting according to related part first. Then make printings etc 
    */
    int cho, cho2, min,max,i, flag=0;
    printf("\t1. Budget\n""\t2. Genre\n""\t3. Name\n"
           "\t4. Score\n""\t5. Year\n""Please select an operation:  ");
    do
    {
        scanf("%d", &cho);
        if(cho < 1 || cho > 5)
        {
            printf("INVALID ENTRY, TRY AGAIN\n");
            flag = -1;
        }
    }while(flag == -1);
    flag = 0;

    printf("1. Single Selection\n2. Multiple Selection\n""Please select an operation:  ");
    do
    {
        scanf("%d", &cho2);
        if(cho2 < 1 || cho2 > 5)
        {
            printf("INVALID ENTRY, TRY AGAIN\n");
            flag = -1;
        }
    }while(flag == -1);
    struct Movie_Budget *lastNode1 = head1;
    struct Movie_Name *lastNode2 = head2;
    switch(cho) /* At the beginning of each case, ordering according to related part will be done by sort_for_one function */
    {
        case 1: sort_for_one(head1, head2, 1);
                if(cho2 == 1)
                {
                    printf("Enter value: \n");
                    scanf("%d", &min);  /* There is no min and max in this part. I used min just to not create a new variable and waste of memory. */
                    if(min <= total_row)
                    {
                        printf("%d. Movie\n", min);
                        for(i=1; i<min; i++)
                        {
                            lastNode1 = lastNode1->next;
                            lastNode2 = lastNode2->next;
                        } 
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                    }
                    else
                        printf("THERE ARE %d FILM AT TOTAL. CHOOSE AN APPROPRIATE ONE\n", total_row);
                }
                else
                {
                    printf("Enter start value: \n");
                    scanf("%d", &min);
                    printf("Enter end value: \n");
                    scanf("%d", &max);
                    for(i=1; i<min; i++)
                    {
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    } 
                    printf("Movies between %d and %d, sorted by budget\n", min, max);
                    for(i=min; i<=max; i++)
                    {
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    }
                }
                break;
        case 2: sort_for_one(head1, head2, 2);
                if(cho2 == 1)
                {
                    printf("Enter value: \n");
                    scanf("%d", &min);  /* There is no min and max in this part. I used min just to not create a new variable and waste of memory. */
                    if(min <= total_row)
                    {
                        printf("%d. Movie\n", min);
                        for(i=1; i<min; i++)
                        {
                            lastNode1 = lastNode1->next;
                            lastNode2 = lastNode2->next;
                        } 
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                    }
                    else
                        printf("THERE ARE %d FILM AT TOTAL. CHOOSE AN APPROPRIATE ONE\n", total_row);
                }
                else
                {
                    printf("Enter start value: \n");
                    scanf("%d", &min);
                    printf("Enter end value: \n");
                    scanf("%d", &max);
                    for(i=1; i<min; i++)
                    {
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    } 
                    printf("Movies between %d and %d, sorted by genre\n", min, max);
                    for(i=min; i<=max; i++)
                    {
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    }
                }
                break;
        case 3: sort_for_one(head1, head2, 3);
                if(cho2 == 1)
                {
                    printf("Enter value: \n");
                    scanf("%d", &min);  /* There is no min and max in this part. I used min just to not create a new variable and waste of memory. */
                    if(min <= total_row)
                    {
                        printf("%d. Movie\n", min);
                        for(i=1; i<min; i++)
                        {
                            lastNode1 = lastNode1->next;
                            lastNode2 = lastNode2->next;
                        } 
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                    }
                    else
                        printf("THERE ARE %d FILM AT TOTAL. CHOOSE AN APPROPRIATE ONE\n", total_row);
                }
                else
                {
                    printf("Enter start value: \n");
                    scanf("%d", &min);
                    printf("Enter end value: \n");
                    scanf("%d", &max);
                    for(i=1; i<min; i++)
                    {
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    } 
                    printf("Movies between %d and %d, sorted by name\n", min, max);
                    for(i=min; i<=max; i++)
                    {
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    }
                }
                break;
        case 4: sort_for_one(head1, head2, 4);
                if(cho2 == 1)
                {
                    printf("Enter value: \n");
                    scanf("%d", &min);  /* There is no min and max in this part. I used min just to not create a new variable and waste of memory. */
                    if(min <= total_row)
                    {
                        printf("%d. Movie\n", min);
                        for(i=1; i<min; i++)
                        {
                            lastNode1 = lastNode1->next;
                            lastNode2 = lastNode2->next;
                        } 
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                    }
                    else
                        printf("THERE ARE %d FILM AT TOTAL. CHOOSE AN APPROPRIATE ONE\n", total_row);
                }
                else
                {
                    printf("Enter start value: \n");
                    scanf("%d", &min);
                    printf("Enter end value: \n");
                    scanf("%d", &max);
                    for(i=1; i<min; i++)
                    {
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    } 
                    printf("Movies between %d and %d, sorted by score\n", min, max);
                    for(i=min; i<=max; i++)
                    {
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    }
                }
                break;
        case 5: sort_for_one(head1, head2, 5);
                if(cho2 == 1)
                {
                    printf("Enter value: \n");
                    scanf("%d", &min);  /* There is no min and max in this part. I used min just to not create a new variable and waste of memory. */
                    if(min <= total_row)
                    {
                        printf("%d. Movie\n", min);
                        for(i=1; i<min; i++)
                        {
                            lastNode1 = lastNode1->next;
                            lastNode2 = lastNode2->next;
                        } 
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                    }
                    else
                        printf("THERE ARE %d FILM AT TOTAL. CHOOSE AN APPROPRIATE ONE\n", total_row);
                }
                else
                {
                    printf("Enter start value: \n");
                    scanf("%d", &min);
                    printf("Enter end value: \n");
                    scanf("%d", &max);
                    for(i=1; i<min; i++)
                    {
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    } 
                    printf("Movies between %d and %d, sorted by year\n", min, max);
                    for(i=min; i<=max; i++)
                    {
                        printf("\n%-10d\t", lastNode1->budget);
                        printf("%-10s\t", lastNode2->genre);
                        printf("%-40s\t", lastNode1->name);
                        printf("%lf\t", lastNode2->score);
                        printf("%d\n", lastNode1->year);
                        lastNode1 = lastNode1->next;
                        lastNode2 = lastNode2->next;
                    }
                }
                break;
    }
}

void two(struct record_genre *head3)
{
    struct record_genre *lastNode = head3;
    while(lastNode->next != NULL)
    {
        printf("%s\n", lastNode->genre_type);   /* Printing whole existing genres' names */
        lastNode = lastNode->next;
    }
    printf("%s\n", lastNode->genre_type);
}
/* 
   WARNING! There were no info about how function three and four should be order, or should it be ordered.
   So I just print the ones that are in desired interval, without ordering.
*/
void three(struct Movie_Budget *head1)
{
    int year, u_s, is_okey=0;   /* is_okey controls whether inputs are in desired range, desired value, desired interval. u_s= until_since*/
    struct Movie_Budget *lastNode1 = head1;
    printf("\nEnter a year: \n");
    scanf("%d", &year);
    printf("Until (0) or Since (1)\t%d: ", year);
    scanf("%d", &u_s);
    if(u_s == 0)
    {
        while(lastNode1 != NULL)
        {
            if(lastNode1->year < year)
            {
                printf("%s\n", lastNode1->name);
                is_okey = 1;
            }
            lastNode1 = lastNode1->next;
        }
    }
    else if(u_s == 1)
    {
        while(lastNode1 != NULL)
        {
            if(lastNode1->year >= year)
            {
                printf("%s\n", lastNode1->name);
                is_okey = 1;
            }
            lastNode1 = lastNode1->next;
        }
    }
    else
        printf("INVALID ENTRY\n");
    if(is_okey == 0)
        printf("TRY AGAIN\n");
}

void four(struct Movie_Name *head2)
{
    double score;
    int l_g, is_okey=0; /* is_okey controls whether inputs are in desired range, desired value, desired interval. l_g= less_greater */
    struct Movie_Name *lastNode2 = head2;
    printf("\nEnter a score: \n");
    scanf("%lf", &score);
    printf("Less (0) or Greater (1)\t%.1lf: ", score);
    scanf("%d", &l_g);
    if(l_g == 0)
    {
        while(lastNode2 != NULL)
        {
            if(lastNode2->score < score)
            {
                printf("%s\n", lastNode2->name);
                is_okey = 1;
            }
            lastNode2 = lastNode2->next;
        }
    }
    else if(l_g == 1)
    {
        while(lastNode2 != NULL)
        {
            if(lastNode2->score >= score)
            {
                printf("%s\n", lastNode2->name);
                is_okey = 1;
            }
            lastNode2 = lastNode2->next;
        }
    }
    else
        printf("INVALID ENTRY\n");
    if(is_okey == 0)
        printf("TRY AGAIN\n");
}

void five(struct Movie_Budget *head1 ,struct Movie_Name *head2)
{
    int len, is_name_recorded=0, update_this, i=1;
    char ch, str[N];
    struct Movie_Budget *buffer = head1;
    struct Movie_Budget *lastNode1 = head1;
    struct Movie_Name *lastNode2 = head2;
    printf("\nPlease enter the name of the movie: \n");
    scanf(" %[^\n]s", str);
    len = strlen(str);
    while(buffer != NULL)
    {
        if(strncmp(buffer->name, str, len) == 0 && len == strlen(buffer->name)) /* Both word and their lenght should be equal hello world and hello should't match */
        {
            is_name_recorded=1;
            update_this = i;
        }
        buffer = buffer->next;
        i++;
    }
    if(is_name_recorded == 0)
        printf("THERE IS NO SUCH FILM\nEntered film (%s) IS INVALID\n\n", str);
    else
    {
        for(i=1; i<update_this; i++)
        {
            lastNode1 = lastNode1->next;
            lastNode2 = lastNode2->next;
        } 
        if(lastNode1->budget == -1)
            printf("Unknown\n");
        else
            printf("\nBudget: %d\n", lastNode1->budget);
        printf("Genre: %s\n", lastNode2->genre);
        printf("Name: %s\n", lastNode1->name);
        printf("Score: %lf\n", lastNode2->score);
        printf("Year: %d\n\n", lastNode1->year);
    }
}
void six(struct Movie_Name *head2)
{
    double sum=0.0;
    struct Movie_Name *lastNode = head2;
    while(lastNode->next != NULL)
    {
        sum += lastNode->score; /* Sum all nodes' scores */
        lastNode = lastNode->next;
    }
    sum += lastNode->score;
    sum /= total_row;
    printf("Average: %lf\n", sum);
}

void seven(struct record_genre *head3)
{
    struct record_genre *lastNode = head3;
    while(lastNode->next != NULL)
    {
        printf("%-20s%d\n", lastNode->genre_type, lastNode->each_genre);
        lastNode = lastNode->next;
    }
    printf("%-20s%d\n", lastNode->genre_type, lastNode->each_genre);
}

void sort_for_one(struct Movie_Budget *head1, struct Movie_Name *head2, int which)
{
    int i, j, count=0, temp;
    double tempd;
    char tempstr[N];
    struct Movie_Budget *previous1;
    struct Movie_Budget *current1;
    struct Movie_Budget *cursor1 = head1;
    struct Movie_Name *previous2;
    struct Movie_Name *current2;
    struct Movie_Name *cursor2 = head2;
    for(i=total_row-2; i>=0; i--)
    {
        previous1 = cursor1;
        current1 = previous1->next;
        previous2 = cursor2;
        current2 = previous2->next;
        for(j=0; j<i; j++)
        {
            switch(which)   /* This switch is full of swaps... Each case have same swap operations. Instead of dividing them into functions, I used switch. */
            {               /* So that parameter sending was made just one time instead of 5 */
                case 1: if(previous1->budget > current1->budget)
                        {
                            temp = previous1->budget;
                            previous1->budget = current1->budget;
                            current1->budget = temp;

                            temp = previous1->year;
                            previous1->year = current1->year;
                            current1->year = temp;

                            tempd = previous2->score;
                            previous2->score = current2->score;
                            current2->score = tempd;

                            strcpy(tempstr, previous1->name);
                            strcpy(previous1->name, current1->name);
                            strcpy(current1->name, tempstr);

                            strcpy(tempstr, previous2->genre);
                            strcpy(previous2->genre, current2->genre);
                            strcpy(current2->genre, tempstr);
                        }
                        break;
                case 2: if(previous2->genre[0] < current2->genre[0])  /* Ordering will be from a to z */
                        {
                            temp = previous1->budget;
                            previous1->budget = current1->budget;
                            current1->budget = temp;

                            temp = previous1->year;
                            previous1->year = current1->year;
                            current1->year = temp;

                            tempd = previous2->score;
                            previous2->score = current2->score;
                            current2->score = tempd;

                            strcpy(tempstr, previous1->name);
                            strcpy(previous1->name, current1->name);
                            strcpy(current1->name, tempstr);

                            strcpy(tempstr, previous2->genre);
                            strcpy(previous2->genre, current2->genre);
                            strcpy(current2->genre, tempstr);
                        }
                        break;
                case 3: if(previous1->name[0] < current1->name[0]) /* Ordering will be from a to z */
                        {
                            temp = previous1->budget;
                            previous1->budget = current1->budget;
                            current1->budget = temp;

                            temp = previous1->year;
                            previous1->year = current1->year;
                            current1->year = temp;

                            tempd = previous2->score;
                            previous2->score = current2->score;
                            current2->score = tempd;

                            strcpy(tempstr, previous1->name);
                            strcpy(previous1->name, current1->name);
                            strcpy(current1->name, tempstr);

                            strcpy(tempstr, previous2->genre);
                            strcpy(previous2->genre, current2->genre);
                            strcpy(current2->genre, tempstr);
                        }
                        break;
                case 4: if(previous2->score > current2->score)
                        {
                            temp = previous1->budget;
                            previous1->budget = current1->budget;
                            current1->budget = temp;

                            temp = previous1->year;
                            previous1->year = current1->year;
                            current1->year = temp;

                            tempd = previous2->score;
                            previous2->score = current2->score;
                            current2->score = tempd;

                            strcpy(tempstr, previous1->name);
                            strcpy(previous1->name, current1->name);
                            strcpy(current1->name, tempstr);

                            strcpy(tempstr, previous2->genre);
                            strcpy(previous2->genre, current2->genre);
                            strcpy(current2->genre, tempstr);
                        }
                        break;
                case 5: if(previous1->year > current1->year)
                        {
                            temp = previous1->budget;
                            previous1->budget = current1->budget;
                            current1->budget = temp;

                            temp = previous1->year;
                            previous1->year = current1->year;
                            current1->year = temp;

                            tempd = previous2->score;
                            previous2->score = current2->score;
                            current2->score = tempd;

                            strcpy(tempstr, previous1->name);
                            strcpy(previous1->name, current1->name);
                            strcpy(current1->name, tempstr);

                            strcpy(tempstr, previous2->genre);
                            strcpy(previous2->genre, current2->genre);
                            strcpy(current2->genre, tempstr);
                        }
                        break;        
            }
            previous1 = current1;
            current1 = current1->next;
            previous2 = current2;
            current2 = current2->next;
        }
    }
}
