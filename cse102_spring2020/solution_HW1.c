//This solution is belong to pdf file with same name of this c file.
//All the steps I wrote is based on instrutions in that pdf file.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void find_root();
void find_newtonian_root();
int find_multiple_closest(int a, int b);

int main()
{
    int num1,num2;
    find_root(); 
    find_newtonian_root();
    printf("\nEnter the first integer:");
    scanf("%d",&num1);
    printf("Enter the second integer:");
    scanf("%d",&num2);
    int m = find_multiple_closest(num1,num2);
    //Whether return value is equal to number1 itself or not
    //Just for shorten I used ternary operator instead of write if else
    (m == num1) ?printf("Closest number to %d that is multiple of %d is itself.\n",num1,num2)
                :printf("Closest number to %d that is multiple of %d is %d.\n",num1,num2,m);
}
/*
Your function will read three integers from the command prompt as coefficients of a
quadratic equation and calculate the roots of the equation.
*/
void find_root()
{
    int i,a,b,c,x,y,delta,root1,root2;
    printf("Please Enter the first coefficient:");
    scanf("%d",&a);
    printf("Please Enter the second coefficient:");
    scanf("%d",&b);
    printf("Please Enter the third coefficient:");
    scanf("%d",&c);
    delta = (b*b) - (4*a*c);
    //To determine signes in 44th line I made something like that
    x = b < 0 ? '-' : '+';
    y = c < 0 ? '-' : '+'; 
    if(delta < 0)
        printf("Your equation %dx^2 %c %dx %c %d does not have any real roots.",a,x,b,y,c); //I assumed signes as character
    else
    {
        root1 = ( (-1*b) + (sqrt(delta)) ) / (2*a); //Classic finding root formula in math
        root2 = ( (-1*b) - (sqrt(delta)) ) / (2*a);
        if(root1 >= root2) //We should print roots in descending order.
            printf("Your equation %dx^2 %c %dx %c %d have real roots {%d,%d}.",a,x,abs(b),y,abs(c),root1,root2);
        else
            printf("Your equation %dx^2 %c %dx %c %d have real roots {%d,%d}.",a,x,abs(b),y,abs(c),root2,root1);
    }
} 

void find_newtonian_root()
{
    int a,b,c,x,y;
    float xValues[6];
    float fxValues[5];
    float difValues[5];
    printf("\n\nPlease Enter the first coefficient:");
    scanf("%d",&a);
    printf("Please Enter the second coefficient:");
    scanf("%d",&b);
    printf("Please Enter the third coefficient:");
    scanf("%d",&c);
    printf("Please Enter the initial:");
    scanf("%f",&xValues[0]);
    //Those may seem complicated.I suggest you first search that:   https://planetcalc.com/7748/ 
    for(int i=1; i<6; i++)
        xValues[i] = xValues[i-1] - ((xValues[i-1]*xValues[i-1]*a) + (xValues[i-1]*b) + (c)) / ((2*xValues[i-1])+(b));
    for(int i=0; i<5; i++)
        fxValues[i] = ((xValues[i+1]*xValues[i+1]*a) + (xValues[i+1]*b) + (c));
    for(int i=1; i<6; i++)
        difValues[i-1] = (xValues[i] - xValues[i-1]) >= 0 ? (xValues[i] - xValues[i-1]) : -1*(xValues[i] - xValues[i-1]);
    x = b < 0 ? '-' : '+';
    y = c < 0 ? '-' : '+';
    printf("Your equation is %dx^2 %c %dx %c %d  and iterations are\n\n",a,x,b,y,c);
    printf("Step     x      f(x)      Difference\n\n");
    for(int i=0; i<5; i++)
        printf("x%d %10.4f  %-10.5f %8.4f\n",i+1,xValues[i+1],fxValues[i],difValues[i]); //These %10's purpose's to look like a table
}

int find_multiple_closest(int a, int b)
{
    int res = a/b;
    if(res*b == a)
        return a;
    else
    {
        int p1 = a - (res*b); 
        /*
        Here purpose is that:
        If we enter 76 and 15 res will be 5 and closest number to 76 will be 75
        But if we enter 76 and 13 res will be 6 and closest number to 76 will be 78
        Res may be equal to a/b or (a/b)+1
        */
        int p2 = ((res+1)*b) - a;
        return (p1 <= p2) ? (res*b) : ((res+1)*b);
    }
}
