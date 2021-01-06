//This solution is belong to pdf file with same name of this c file.
//All the steps I wrote is based on instructions in that pdf file.
#include <stdio.h>
#include <math.h>
//Declaration of required functions for part1.Detailed descriptions about functions are below.
int draw_triangle(int side1,int side2, int side3);
void type_triangle(int side1,int side2, int side3);
int perimeter_triangle(int side1,int side2, int side3);
double area_triangle(int side1,int side2, int side3,int perimeter);
//Declaration of required functions for part2.Detailed descriptions about functions are below.
int number_length(int number);
int find_digit(int number, int index);

int main()
{
    int num1,num2,num3,x,y,cur,to;
    float amount;
    char cur1,cur2;
    printf("The lenght of first side:\n");
    scanf("%d",&num1);
    printf("The lenght of second side:\n");
    scanf("%d",&num2);
    printf("The lenght of first side:\n");
    scanf("%d",&num3);
    int m = draw_triangle(num1,num2,num3);
    if(m==0)
        printf("\nAccording to the triangle inequality theorem, this triangle cannot be drawn.\n");
    else
    {
        printf("\nAccording to the triangle inequality theorem, this triangle can be drawn.\n\n");
        type_triangle(num1,num2,num3);
        int p = perimeter_triangle(num1,num2,num3);
        printf("The perimeter of the triangle:%d\n",p);
        printf("The area of the triangle:%f\n",area_triangle(num1,num2,num3,p));
    }
    printf("\nEnter a number (maxiumum 6 digits)\n");
    scanf("%d",&x);
    printf("Your number has %d digits\n\n",number_length(x));
    printf("When your number is written 100 times next to each other, which digit of this number would you like to see? :\n");
    scanf("%d",&y);
    printf("%d.th digit of the big number sequence: %d\n\n",y,find_digit(x,y));
    printf("***** Welcome to ABC Exchange Office *****\n\nEnter your amount:\n");
    scanf("%f",&amount);
    printf("\nPlease select your currency\n1. Turkish Lira\n2. Euro\n3. Dollar\n");
    scanf("%d",&cur);
    switch(cur)
    {
        case 1: 
            printf("You have %f Turkish Liras\nChoose which currency you want to convert\n",amount);
            cur1 = 'T';
            break;
        case 2:
            printf("You have %f Euros\nChoose which currency you want to convert\n",amount);
            cur1 = 'E';
            break;
        case 3:
            printf("You have %f Dollars\nChoose which currency you want to convert\n",amount);
            cur1 = 'D';
            break;
        default:
            printf("Your selection is invalid!");
    }
    scanf("%d",&to);
    switch(to)
    {
        //1 Euro = 6.69 Turkish Lira
        //1 Dollar = 6.14 Turkish Lira
        case 1: 
            if(cur1 == 'E') 
                printf("You have %f Turkish Liras\n",(6.69*amount));
            else if(cur1 == 'D')
                printf("You have %f Turkish Liras\n",(6.14*amount));
            else
                printf("You have %f Turkish Liras\n",amount);
            break;
        case 2:
            if(cur1 == 'T') 
                printf("You have %f Euros\n",(amount/6.69));
            else if(cur1 == 'D')
                printf("You have %f Euros\n",(amount*(6.69/6.14)));
            else
                printf("You have %f Euros\n",amount);
            break;
        case 3:
            if(cur1 == 'E') 
                printf("\nYou have %f Dollars\n",(amount*(6.14/6.69)));
            else if(cur1 == 'T')
                printf("\nYou have %f Dollars\n",(amount/6.14));
            else
                printf("\nYou have %f Dollars\n",amount);
            break;
        default:
            printf("Your selection is invalid!");
    }

}

int draw_triangle(int side1,int side2, int side3)
{
    if((side1+side2 > side3) && (side1+side3 > side2) && (side3+side2 > side1)) //Condition for draw triangle
        return 1;
    else 
        return 0;
}
void type_triangle(int side1,int side2, int side3) //Function for determine type of the triangle
{
    if((side1 == side2 && side1 != side3) || (side1 == side3 && side1 != side2))
        printf("It is a Isosceles Triangle\n");
    else if(side1 == side2 && side1 == side3)
        printf("It is a Equilateral Triangle\n");
    else
        printf("It is a Scalene Triangle\n");
}
int perimeter_triangle(int side1,int side2, int side3) //It just returns sum of edges
{
    return side1+side2+side3;
}
double area_triangle(int side1,int side2, int side3,int perimeter) //Calculating area of a triangle using Heron's formula
{
    perimeter /= 2;
    double area = sqrt(perimeter*(perimeter-side1)*(perimeter-side2)*(perimeter-side3));
    return area;
}
int number_length(int number)
{
    int len = log10(number); //Log10 function in math.h library helps us calculate number of digits.But it returns (normal lenght-1) so I add 1 to retrun value.
    return len+1;
}
int find_digit(int number, int index)
{
    int len,power;
    len = number_length(number);
    if(index <= len) //Here I controlled whether index value entered by user is smaller than or equal to lenght or not.
    /*
    For example,if user enters 123456 as numbers and 4 for index,we couldn't do same thing with numbers bigger than 6
    Let me show you the reason
    123456 --> has 6 digits
    User wants 4th digit
    If we follow same path we will get 4%6 --> 4,power will be 4
    Than the process is:
    number = number / 10^4 --> number = 12 and it returns 12%10 which is 2 but we were expecting 4
    Instead if we say "power should be len - index if index is smaller than len" what we get is
    power = 6 - 4 --> power = 2
    number = number / 10^2 --> number = 1234 and it returns 1234%10 which is 4
    */
        power = len - index;
    else
        power = index % len;
    if(power == 0)
        return number %= 10;
    else
        number /= pow(10,power);
    /*
    The reason why we're dividing "number" to appropriate power of 10 is delete unnecesarry digits and reach the wanted digit as last digit.
    Than we can easily find what is that digit by looking it's remainder from mode 10
    */
    return number%10;
}
