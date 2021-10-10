/* Sir, my code is a bit compliacated. Even I tried to explain, if there is missunderstandable parts please ask :) Çizerek anlatmam gerekebilir. */
/*
 * Genel algoritma:
 * Select add or process
 * If add is selected:
        * Control whether entered label is full for (row)
        * If it isn't full, place it to (row), otherwise place it to (row+1) which is next row in main 2D array
        * Store indexes of customers(struct) after dot.   1.15 means 15th customer in struct array and it has label 1
 * When process are selected, use 0th and then make left swap
*/
#include <stdio.h>
#include <string.h>
#define N 20
#define maxx 50
/* Enum that holds the customer labels are created */
enum Type_Of_Customer {employee, retired, student, unemployed, other} type_of_customer;
/* Struct that holds the customers' infos are created */
typedef struct Customer_Construct
{
    char name[N];
    int age;
    enum Type_Of_Customer cus_type;
}customer_construct;

int order(double arr[N], int until, int ix, int cur_tot);
int is_ordered(double arr[N], int m);
void add_customer(customer_construct array[maxx], int *aocp, double arr[N][N]);
void find_max();
int find_min();
void process(customer_construct array[maxx], int *aocp, double arr[N][N]);
/* Not to have too many function parameter, I declared arrays globally */
int f[5][N] = {0},      /* 2D f array will store how many label are there in that row(0.rowda 5 tane 0 var, 3 tane 1 var. 1.rowda 2 tane sıfır var şeklinde) */
    n=0,                /* n is maximum array number. Mesela ana arrayimizde 1 1 1 3 3 1 1 1 3 1 olsun, 2D arrayde max 3.row görülür. n=3 olur. */
    indexx[N] = {0},    /* index will hold how many element are there in a row, for 1 1 1 2 1 holds 4 for indexx[0] and 1 for indexx[1], yeni datanın nereye ekleneceğini gösterir. */
    row_for[N],         /* her label için ayrı bir row count'ı. */
    process_arr[maxx]; //n is num of rows 

int main()
{
    int add_or_process, aoc=0, i, j;
    double seq[N][N]={0.0};
    customer_construct customer[100];
    printf("***********Banking System***********\n\nPress 3 to exit.\n""\nCurrent Sequence: ");
    do
    {
        printf("\n1-Add customer\n2-Process customer\n");
        scanf("%d", &add_or_process);
        if(add_or_process == 1)
            add_customer(customer, &aoc, seq);
        else
        {
            if(aoc == 0)
                printf("All customers are proceed!!!\n");
            else
            {
                process(customer, &aoc, seq);
                aoc--;
            }
        }
        printf("\nCurrent Sequence: ");
        /* Outer loop is loops "how many row exist" times, inner loop prints the elements first in row0 tham row1 and so on. */
        for(i=0; i<=n; i++)
        {
            for(j=0; j<indexx[i]; j++)  /* Loops "how many element exist in the current row" times. */
                printf("%.0f ", seq[i][j]);
        }
    }while(add_or_process != 3);
}

void add_customer(customer_construct array[maxx], int *aocp, double arr[N][N])
{
    int row=0, index, i, j, k, ind, flag=0, all_total=-1, current_total=0, lcpy;
    double cpy=*aocp, last_term;
    cpy /= 100.0;
    process_arr[*aocp] = *aocp;
    printf("\nPlease enter the name of the customer: ");
    scanf("%s", array[*aocp].name);
    printf("Please enter the age of the customer: ");
    scanf("%d", &array[*aocp].age);
    printf("Please enter the label of the customer: ");
    scanf("%u", &array[*aocp].cus_type);
    lcpy = (array[*aocp].cus_type);
    last_term = (array[*aocp].cus_type);
    last_term += cpy; /* Float bir değişken oluşturarak hem labelı hem indexi tutmayı amaçladım. */

    switch(lcpy)    /* To control whether taken label is full or not in the current row. */
    {
        case 0: if(f[row_for[0]][0] == 5)   /* This means taken label is full, go to next row. */
                {
                    ind = indexx[row_for[0]+1];
                    arr[row_for[0]+1][ind] = last_term;
                    f[row_for[0]+1][0]++;
                    row_for[0]++;
                }
                else
                {
                    ind = indexx[row_for[0]];
                    arr[row_for[0]][ind] = last_term;
                    f[row_for[0]][0]++;
                }
                break;
        case 1: if(f[row_for[1]][1] == 3)   /* This means taken label is full, go to next row. */
                {
                    ind = indexx[row_for[1]+1];
                    arr[row_for[1]+1][ind] = last_term;
                    f[row_for[1]+1][1]++;
                    row_for[1]++;   
                }
                else
                {
                    ind = indexx[row_for[1]];
                    arr[row_for[1]][ind] = last_term;
                    f[row_for[1]][1]++;                   
                }
                break;
        case 2: if(f[row_for[2]][2] == 3)   /* This means taken label is full, go to next row. */
                {
                    ind = indexx[row_for[2]+1];
                    arr[row_for[2]+1][ind] = last_term;
                    f[row_for[2]+1][2]++;
                    row_for[2]++;                    
                }
                else
                {
                    ind = indexx[row_for[2]];
                    arr[row_for[2]][ind] = last_term;
                    f[row_for[2]][2]++;                  
                }
                break;
        case 3: if(f[row_for[3]][3] == 2)   /* This means taken label is full, go to next row. */
                {
                    ind = indexx[row_for[3]+1];
                    arr[row_for[3]+1][ind] = last_term;
                    f[row_for[3]+1][3]++;
                    row_for[3]++;
                }
                else
                {
                    ind = indexx[row_for[3]];
                    arr[row_for[3]][ind] = last_term;
                    f[row_for[3]][3]++;
                }
                break;
        case 4: if(f[row_for[4]][4] == 2)   /* This means taken label is full, go to next row. */
                {
                    ind = indexx[row_for[4]+1];
                    arr[row_for[4]+1][ind] = last_term;
                    f[row_for[4]+1][4]++;
                    row_for[4]++;   
                }
                else
                {
                    ind = indexx[row_for[4]];
                    arr[row_for[4]][ind] = last_term;
                    f[row_for[4]][4]++;
                }
                break;
    }
    find_max(); /* Buraya göre değişen n değeri loop'un sınırlayıcısı olacak. Max kaç row varsa o kadar dönecek. */
    for(i=0; i<=n; i++)
        indexx[i] = f[row+i][0] + f[row+i][1] + f[row+i][2] + f[row+i][3] + f[row+i][4];    /* O rowdaki tüm elementlerin toplamı indexx[i]ye depolanacak. */
    if(row == 0)
        current_total = ind;
    else
    {
        for(k=1; k<=row_for[(int)last_term]; k++)
            current_total += indexx[k];
    } 
    for(i=0; i<=n; i++)
        order(arr[i], indexx[i]-1, i, current_total);
    (*aocp)++; 
}

int is_ordered(double arr[N], int m)
{
    int i, count=0, temp, return_value=0;
    for(i=0; i<m; i++)
    {
        if(arr[i] < arr[i+1])
            count++;
    }
    if(count != m)
        return_value = -1;
    return return_value;
}

int order(double arr[N], int until, int ix, int cur_tot)
{
    int j;
    double temp;
    for(j=0; j<until; j++)
    {
        if((int)arr[j] > (int)arr[j+1])
        {
            temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
        }
    }
    if(is_ordered(arr, until) == 0) /* Array is ordered. */
        return 0;
    else
        order(arr, until-1, ix, cur_tot);   /* Run until array becomes ordered */
}

void find_max()
{
    int i, max=row_for[0];
    for(i=1; i<5; i++)
    {
        if(row_for[i] > max)
            max = row_for[i];
    }
    n = max;
    printf("max n: %d\n", n);
}

int find_min()  /* Process en minimum row'a göre yapılacak, genelde 0 */
{
    int i, min=row_for[0];
    for(i=1; i<5; i++)
    {
        if(row_for[i] < min)
            min = row_for[i];
    }
    return min;
}

void process(customer_construct array[maxx], int *aocp, double arr[N][N])
{
    int i, j, musteri, min, label_of_first;
    min = find_min();
    musteri = (int)(100.0*(arr[0][0]))%100; /* Double'ın tam ve float kısmını ayırarak ayrı ayrı işlemde kullanıyorum. */
    label_of_first = (int)(arr[0][0]);
    for(j=min; j<indexx[min]; j++)
        arr[min][j] = arr[min][j+1];
    for(i=musteri; i<(*aocp)-1; i++)    /* Struct array swapı ayrılan müşterinin yerini doldurmak için left swap yapıyor. */
    {
        array[i].age = array[i+1].age;
        array[i].cus_type = array[i+1].age;
        strcpy(array[i].name, array[i+1].name);
    }   
    for(i=0; i<=n; i++) /* -0.01 yaparak müşteri indexini azaltıyoruz */
    {
        for(j=0; j<indexx[i]; j++)  
        {
            if((int)(100.0*(arr[i][j]))%100 > musteri)
                arr[i][j] -= 0.01 ;
        }
    }
    f[label_of_first][min]--;
    indexx[min]--;
}
