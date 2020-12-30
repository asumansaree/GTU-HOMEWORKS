//Solution for problem in pdf with same name(INF211_Project_11(1)) 
//Before start,you should create a text file and write something in it.
//Don't forget to create it sampe path with where you'll compile your program.
#include <stdio.h>

void PrintFileContent( FILE *fptr);
void copy_file(FILE *fptr1, FILE *fptr2);
int findNumberofChar( FILE *fptr);

FILE *fptr1, *fptr2;
char filename1[20],filename2[20];  
//We will get 2 distinct filename from user.
//I defined them as global variable because we need filename2 in line 78
int main() {
	printf("Type the filename to open in read mode\n");
	scanf("%s", filename1); //string olduðu için & iþaretine gerek yok,bunu sildim.
	fptr1 = fopen(filename1, "r"); 
	if (fptr1 == NULL) 
	{ 
		printf("Cannot open file %s \n", filename1); 
		return 1;
	} 
	
	printf("Type the filename to open in write mode\n");
	scanf("%s", filename2);
	fptr2 = fopen(filename2, "w+"); 
	if (fptr2 == NULL) 
	{ 
		printf("Cannot open file %s \n", filename2); 
		return 1;
	} 
	
  	copy_file(fptr1, fptr2);
  	findNumberofChar(fptr2);
  	//Before reopen,first we should close files.
  	fclose(fptr1);
  	fclose(fptr2);
  	
  	fptr1 = fopen(filename1, "r"); 
  	PrintFileContent(fptr1);
  	fptr2 = fopen(filename2, "r");
  	PrintFileContent(fptr2);
  	
  	fclose(fptr1);
  	fclose(fptr2);
			
	return 0;
}

void PrintFileContent( FILE *fptr)
{
    printf("\n");
    // Read contents from file 
    char c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
    printf("\n");
}

void copy_file(FILE *fptr1, FILE *fptr2)
{
	char c = fgetc(fptr1); 
	while (c != EOF) 
	{ 
		if(c >= 'a' && c <= 'z')
			c -= 32; //You can also use toUpper function to make lowercases uppercase.
		fputc(c, fptr2); 
		c = fgetc(fptr1); 
	} 	
}

int findNumberofChar( FILE *fptr)
{
	 int a = ftell(fptr);
	 fprintf(fptr,"\n\nThe file %s has %d characters",filename2,a); 
	 return a;	 
}
