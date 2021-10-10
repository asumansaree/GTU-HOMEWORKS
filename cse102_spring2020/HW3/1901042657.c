#include <stdio.h>

void calculate_fibonacci_sequence();
void decide_perfect_harmonic_number();
void difference_max_min();
void bmi_calculation();

int main()
{
    calculate_fibonacci_sequence();
    decide_perfect_harmonic_number();
    difference_max_min();
    bmi_calculation();
}

/* The Fibonacci Sequence is the series of numbers that next number is found by adding up the two numbers before it. */
void calculate_fibonacci_sequence()
{
    char c;
    long int term, i, first, second, sum, true_input=1;    /* Here first and second represents the 1th and 2nd terms of sequence which are both 1*/
    do
    {
        first=1; second=1;
        printf("Please enter term(s) number: ");
        do
        {
            true_input = scanf("%ld", &term);
            c = getchar();
            if(c == '*')
                true_input = 1;
            if(term <= 0 && true_input > 0)
                printf("Please enter “positive” term(s) number: ");
            if(true_input != 1)
                printf("Please enter “numeric” term(s) number: ");
        } while(term <= 0 || true_input != 1);
        if(c != '*')
        {
            printf("\nFibonacci Sequence:\n");
            for(i=0; i<term; i++)
            {
                printf("%ld\n",first);
                sum = first + second;
                first = second;
                second = sum;       
            }
        }
    } while(c != '*');
}

void decide_perfect_harmonic_number()
{
    int n, i, sum_perfect;
    double sum_harmonic, count, result;
    char c;
    do
    {
    	   sum_harmonic = 0.0;
    	   count = 0.0;	/* Each time that function run again we should reset these values */
    	   sum_perfect=0;
           do
	    {
		printf("\n\n\nPlease enter input number: ");
		scanf("%d",&n);
		c = getchar();
	    } while(n < 0);
	    if(c != '*')
	    {
	                            /*********** Part for determine whether entered number is a perfect number or not ***********/
	    /* A perfect number is a number that it's natural number divisors's sum(except itself) is equal to number itself. Ex: 28's divisors 1 + 2 + 4 + 7 + 14 = 28 */
	    printf("\nNatural Number Divisors: ");   
	    for(i=1; i<=n; i++) /* 0 isn't a divisor for any number so we're strating from 1 */
	    {
		if(n % i == 0)
		{
		    if(i == 1)      /* To provide required output with commas as 1, 2, 3 I add that if else */
		        printf("%d", i);
		    else
		        printf(", %d", i);
		    if(i != n)      /* According to perfect number definiton, number itself shouldn't add even it is a divisor, too. */
		        sum_perfect += i;
		    /*********** Part for determine whether entered number is a harmonic divisor number or not ***********/
		    count++;    /* For harmonic divisor number's dividend (amount of natural number divisors) */
		    sum_harmonic += 1.00/(double)i;
		}         
	    }
	    printf("\n\nIs Perfect Number? : ");
	    if(sum_perfect == n)
		printf("Yes\n");
	    else 
		printf("No\n");
	    printf("\nIs Harmonic Divisor Number? : ");
	    result = count/sum_harmonic;
	    if(result == (int)result)
		printf("Yes\n");
	    else 
		printf("No\n");
	    }
    }   while(c != '*');                
}

void difference_max_min()
{
    int i;
    double a1, a2, a3, a4, a5, min, max;
    printf("\n\n\nPlease enter 5 numbers: ");
    scanf("%lf %lf %lf %lf %lf", &a1, &a2, &a3, &a4, &a5);
    min = a1;
        if(a2 < min)
            min = a2;
        if(a3 < min)
            min = a3;
        if(a4 < min)
            min = a4;
        if(a5 < min)
            min = a5;
    max = a1;
        if(a2 > max)
            max = a2;
        if(a3 > max)
            max = a3;
        if(a4 > max)
            max = a4;
        if(a5 > max)
            max = a5;
    
    if((int)min == min)
        min = (int)min;
    if((int)max == max)
        max = (int)max;

    printf("Maximum number is: %g\n", max);
    printf("Minimum number is: %g\n", min);
    printf("Difference between maximum and minimum is: %g\n", max-min);
}

void bmi_calculation()
{
    float w, h, bmi;
    printf("\n\n\nPlease enter weight(kg): ");
    scanf("%f",&w);
    printf("Please enter height(m): ");
    scanf("%f",&h);
    bmi = w / (h*h);
    if(bmi < 16)
        printf("Your category: Severely Underweight\n");
    else if(bmi >= 16.0 && bmi < 18.5)
        printf("Your category: Underweight\n");
    else if(bmi >= 18.5 && bmi < 24.9)
        printf("Your category: Normal\n");
    else if(bmi >= 25.0 && bmi < 29.9)
        printf("Your category: Owerweight\n");
    else if(bmi >= 30.0)
        printf("Your category: Obese\n");
    else
        printf("Undefined\n");
}