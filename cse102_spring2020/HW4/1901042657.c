#include <stdio.h>
#include <math.h>

/* Part1 Function's Decleration */
void part1();
float pretty_format(float x);
/* Part2 Function's Decleration */
void part2();
int is_armstrong(int n);
int is_palindrome(int n);
int digit_number(int n);
/* Part3 Function's Decleration */
void part3();
int is_prime(int n);


int main()
{
    part1();    
    part2();
    part3();
}

/* Before start, there are no spaces between printed terms in this part, so please while reading output */
void part1()
{
    int degree, i;  float co, temp;
    printf("\nEnter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");
    /* First term will be degree and according to this value we'll take value from user. */
    scanf("%d", &degree);
    for(i=degree; i>=0; i--)
    {
        scanf("%f", &co);
        temp = pretty_format(co);   /* Coefficienties will send that func and will be round if necesarry */
        if(i == 0)      /* For 0th degree */
        {
            if(co != 0)
            {
                if(temp != 0.0)
                    printf(" %+.1f\n",temp);    /* Shouldn't be any x value because this is constant term */
            }
        }
        else if(i == degree)    /* For first term of polynom */
        {
            if(co == 1.0)   /* If it is first term and co is positive, than we shouldn't print + sign. So this is a separate condition */
                printf("x^%d", i);
            else if(co == -1.0) 
                printf("-x^%d", i);
            else if(co == 0)
                printf("You entered degree of polynom wrong!\n");
            else
            {
                if(temp != 0.0 && i != 1)       /* If value equal to 0 after it rounds, don't print it. */
                {
                    if(temp == 1.0)
                        printf("x^%d", i);
                    else if(temp == -1.0)
                        printf("x^%d", i);
                    else
                        printf("%.1fx^%d", temp, i);
                }
                if(temp != 0.0 && i == 1)   /* If i=1, we shouldn't print ^1*/
                {
                    if(temp == 1.0)
                        printf("x");
                    else if(temp == -1.0)
                        printf("-x");
                    else
                        printf("%.1fx", temp);
                }
            }
        }
        else
        {
            if(co != 0.0 && i != 1)
            {
                if(temp != 0.0 && temp != 1.0 && temp != -1.0)
                    printf(" %+.1fx^%d",temp, i);
                if(temp != 0.0 && temp == 1.0)
                    printf(" +x^%d", i);
                if(temp != 0.0 && temp == -1.0)
                    printf(" -x^%d", i);
            }
            if(co != 0.0 && i == 1)
            {
                if(temp != 0.0  && temp != 1.0 && temp != -1.0)
                    printf(" %+.1fx",temp);
                if(temp != 0.0 && temp == 1.0)
                    printf(" +x");
                if(temp != 0.0 && temp == -1.0)
                    printf(" -x");
            }
        }
    }
}

float pretty_format(float x)
{
    int x_as_int, temp_x;   float xcpy, orgnl_x = x;
    if(x < 0)   /* This is for make things earier. If value is negative, assume that as positive and make rounds, then again make it negative. */
        x *= -1;
    temp_x = (int)(x*100);
    if(temp_x == 104 || temp_x == 103 || temp_x == 102 || temp_x == 101)   /* This values are really problematic...I do them separately. */
    {
        x = 1.0;
        if(orgnl_x < 0)
            x *= -1;
        return x;
    }
    if(x * 10 == (int)(x * 10)) /* You have a.x float number, in that case you don't need to do any rounding. Return value without not change anyting. */
    {
        if(orgnl_x < 0)
            x *= -1;
        return x;
    }
    /* We should consider three decimal after floating point. To get rid of float type, we should multiply our number with 1000 */
    xcpy = x * 1000;
    x_as_int = (int)xcpy;
    /* Part for control if float start with 0, if decimal after floating point becomes 0, than not print anything. */
    /* Here what I made is:  You have a.xyz -> axyz ->(%100) -> yz -> control is yz < 51 or not. */
    if(x_as_int % 100 < 51)
        x -= 0.01;  /* Problematic part is 0.05 part, with decreasing 0.01 we can handle that. Other parts are made automathically. */
    if(x <= 0.05)
        x = 0.0;
    if(orgnl_x < 0) /* We reversed negative numbers. Take it back after rounding. */
        x *= -1;
    return x;
}

void part2()
{
    int num, res1, res2;
    do
    {
        printf("\n\nPlease enter an integer number: ");
        scanf("%d",&num);
        if(num < 0)
            printf("You should enter a positive number!\n");
    }
    while(num < 0);
    res1 = is_armstrong(num);
    res2 = is_palindrome(num);
    /* According to return values we have conditions. */
    if(res1 == 1 && res2 != 1)
        printf("This number is only Armstrong number.\n");
    else if(res1 != 1 && res2 == 1)
        printf("This number is only Palindrome number.\n");
    else if(res1 == 1 && res2 == 1)
        printf("This number is both Palindrome and Armstrong number.\n");
    else
        printf("This number does not satisfy any special cases.\n");
    
}

int is_armstrong(int n)
{
    int sum =0, ncpy = n;
    while(ncpy > 0)
    {
        sum += (ncpy % 10)*(ncpy % 10)*(ncpy % 10); /* Taking last digit's cube every time */
        ncpy /= 10; /* Deleting last digit after it executed */
    }
    if(n == sum)
        return 1;   /* It is armstrong number */
    else
        return 0;   /* It is not armstrong number */
}

int is_palindrome(int n)
{
    int ncpy = n, digit_num, i, rem, sum=0;
    digit_num = digit_number(ncpy);
    /* According to numer is odd or even we have two condition, in both, we should check the number until it's half. In 123321, controlling last 3 is enough */
    /* What I made is that, In 123321, total digit is 6, 1 is the both 0th and 5th digit. 2 is the both 1th and 4th digit. */
    /* 0+5 =5, 1+4=5 which is digit number -1*/
    /* Make (1*10^0) + (1*10^5) or (2*10^1) + (2*10^4)*/
    if(digit_num % 2 == 1)
    {
        for(i=0; i<(digit_num-1)/2; i++)    
        {
            rem = ncpy % 10;
            sum  += rem*(pow(10,i)) + rem*(pow(10,digit_num-1-i));   /* Sum of the powers should be digit_num-1 */
            ncpy /= 10;
        }
        rem = ncpy % 10;
        sum  += rem*(pow(10,(digit_num-1)/2));
    }
    else
    {
        for(i=0; i<digit_num/2; i++)
        {
            rem = ncpy % 10;
            sum  += rem*(pow(10,i)) + rem*(pow(10,digit_num-1-i));   /* Sum of the powers should be digit_num-1 */
            ncpy /= 10;
        }
    }
    if(sum == n)
        return 1;   /* It is palindrome number */
    else
        return 0;   /* It is not palindrome number */
}

int digit_number(int n)     /* Func that finds how many digit that number has */
{
    int count = 0;
    while(n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

void part3()
{
    int lower, upper, i, result, sum = 0;
    do
    {
        printf("\nPlease enter first integer number: ");
        scanf("%d",&lower);
        printf("Please enter second integer number: ");
        scanf("%d",&upper);
        if(lower < 0 || upper < 0)
            printf("You should enter both number positive! \n");
    }
    while(lower < 0 || upper < 0);
    if(lower > upper)   /* If user enters bigger one first, than reverse their assignment order. */
    {
        int temp = lower;
        lower = upper;
        upper = temp;
    }
    for(i=lower+1; i<upper; i++)
    {
        if(is_prime(i) == 0)    /* Func that makes summmation of prime numbers in given range */
            sum += i;
    }
    printf("Sum of prime numbers between %d and %d: %d\n", lower, upper, sum);
}

int is_prime(int n)
{
    int i, result;
    for(i=2; i<n; i++)
    {
        if(n % i == 0)
        {
            result = 0;     /* Even one zero remainder means this number not prime*/
            break;
        }
        else 
            result = 1; 
    }
    if(result == 0)
        return 1;   /* this is not a prime number */
    else 
        return 0;   /* this is a prime number */
}