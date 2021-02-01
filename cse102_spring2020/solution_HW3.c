#include <stdio.h>
#include <math.h>

//Part1's functions
int sum (int n, int flag);
int mult (int n, int flag);
//Part2's function
int isprime (int a);
int andop(int a, int b);

int main()
{
    int num,s_or_m,e_or_o;
    //Part1
    printf("Enter an integer: ");
    scanf("%d",&num);
    printf("Please enter '0' for sum, '1' for multiplication\n");
    scanf("%d",&s_or_m);    //Shortening for sum or multiplication
    printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
    scanf("%d",&e_or_o);    //Shortening for even or odd
    switch(s_or_m)
    {
        case 0:
            if(e_or_o != 0 && e_or_o != 1)
            {
                printf("Invalid value for odd/even selection.\n");
                break;
            }
            printf("%d\n",sum(num,e_or_o));
            break;
        case 1:
            if(e_or_o != 0 && e_or_o != 1)
            {
                printf("Invalid value for odd/even selection.\n");
                break;
            }
            printf("%d\n",mult(num,e_or_o));
            break;
        default:
            printf("Unsported operation.\n");
    }
    //Part2
    printf("\nPlease enter an integer: ");
    scanf("%d",&num);
    for(int i=2; i<num; i++)
    {
        int res = isprime(i);
        if(res == 0)
            printf("%d is a prime number\n",i);
        else
            printf("%d is not a prime number, it is dividible by %d\n",i,res);
    }
    //Part3
    int num1,num2,len1=0 ,len2=0 ,num1cpy, num2cpy,count1=0,count2=0,temp;
    do
    {
        printf("\nFirst integer: ");
        scanf("%d",&num1);
        printf("Second integer: ");
        scanf("%d",&num2);
        num1cpy = num1;
        num2cpy = num2;
        while(num1cpy > 0)
        {
            temp = num1cpy % 10;
            num1cpy /= 10;
            if(temp == 1 || temp == 0)
                len1++; //Aim of this part is counting the only digits 1 or 0
            count1++;   //And this is for checking whether all digits are 1 or 0(wity comparing the len1,of course)
        }
        while(num2cpy > 0)
        {
            temp = num2cpy % 10;
            num2cpy /= 10;
            if(temp == 1 || temp == 0)
                len2++;
            count2++;
        }
        if(count1 != len1 || count2 != len2)
            printf("Integers should be binary, please enter 2 new integers.\n");
        if(count1 != count2)
            printf("Integers should have the same lenght, please enter 2 new integers.\n");
    }
    while(len1 != len2);
    printf("%d AND %d = %d\n",num1,num2,andop(num1,num2));
}

int sum(int n, int flag)
{
    if(flag == 0)   //This means we will work on even numbers
    {
        int sum =0,count =0;
        for(int i=2; i<=n; i+=2)
        {
            sum += i;
            count++;
        }
        for(int i=2; i<=n; i+=2)
        {
            if(count == 1)
                printf("%d = ",i);  //Function should return an integer so that I didn't put sum here
            else
                printf("%d + ",i);
            count--;
        }
        return sum;
    }
    else    //This means we will work on odd numbers
    {
        int sum =0,count =0;
        for(int i=1; i<n; i+=2)
        {
            sum += i;
            count++;
        }
        for(int i=1; i<n; i+=2)
        {
            if(count == 1)
                printf("%d = ",i);
            else
                printf("%d + ",i);
            count--;
        }
        return sum;
    }
}

int mult(int n, int flag)
{
    if(flag == 0)   //This means we will work on even numbers
    {
        int mul =1,count =0;
        for(int i=2; i<=n; i+=2)
        {
            mul *= i;
            count++;
        }
        for(int i=2; i<=n; i+=2)
        {
            if(count == 1)
                printf("%d = ",i);  //Function should return an integer so that I didn't put mul here
            else
                printf("%d * ",i);
            count--;
        }
        return mul;
    }
    else    //This means we will work on odd numbers
    {
        int mul =1,count =0;
        for(int i=1; i<n; i+=2)
        {
            mul *= i;
            count++;
        }
        for(int i=1; i<n; i+=2)
        {
            if(count == 1)
                printf("%d = ",i);
            else
                printf("%d * ",i);
            count--;
        }
        return mul;
    }
}

int isprime(int a)
{
    int acpy = a;
    int s_root = sqrt(acpy);
    for(int i=2; i<=s_root; i++)
    {
        if((a % i) == 0)
            return i;
    }
    return 0;
}

int andop(int a, int b)
{
    int sum=0,temp1,temp2,count=0;
    while(a>0)  //Until one of the numbers reach 0,we will continue
    {
        temp1 = a % 10;
        temp2 = b % 10;
        if(temp1 == 1 && temp1 == temp2)
            sum += pow(10,count);   //Here our aim is create a new integer,because we should return int and also we couldn't use arrays
        /*
        For example,when you observe 1001011 you will see it's components are 1000000+1000+10+1
        That means summation of powers of 10 while that digit is 1 gives us a new number with AND operator of two integers 
        */
        a /= 10;
        b /= 10;
        count++;
    }
    return sum;
} 


