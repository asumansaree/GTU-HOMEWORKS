//This solution is belong to pdf file with same name of this c file.
//All the steps I wrote is based on instructions in that pdf file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define filename "games.txt" 

struct games //Our struct consist of these 3 elements 
{
	char name[20];
	char platforms[20][20];
	int platformCounter;
};

void write(struct games array[], char platform[])  //We're sending a struct array and alsa name of the platform to be search 
{
	FILE *fptr;
	fptr = fopen(filename,"w");  //A file-named games-created and we'll fill that file with below in for loop
	if(fptr == NULL)
	{
		printf("Couldn't create text file.\n");
		exit(1);  //To check whether file created succesfully or not
	}
	fprintf(fptr,"%s games:\n\n",platform);
	int i,j;
	for(i=0; i<N; i++)
	{
		for(j=0; j<array[i].platformCounter; j++)
		{
			//To see what's going on,you can delete 2 comment lines below and print inside this for loop  
			//printf("array[%d].platforms[%d]:%s\n",i,j,array[i].platforms[j]);
			//printf("Return value:%d\n\n",strcmp(platform,array[i].platforms[j]));
			if(strcmp(platform,array[i].platforms[j]) == 0) //strcmp provide us control whether given strings are equal or not
				fprintf(fptr,"%s\n",array[i].name);
		}
	}
}


int main()
{
	struct games info[N];
	int i,count;
	char which[20];
	for(i=0; i<N; i++)  //N declared in the global scope as 4.With this,we can easily change N's value from anywhere.
	{
		count=0;
		printf("%d. Game\n",i+1);
		printf("Name: ");
		scanf(" %[^\n]",info[i].name); //When we didn't put a space before %,it accepts "enter" as string and immediatly prints 53th line.
		printf("Platforms (enter '0' to stop):\n");
		scanf("%s",info[i].platforms[count]);
		while(strcmp(info[i].platforms[count],"0") != 0) //read until see the 0,that means if user didn't press 0,program will continue to receive data.
		{
			count++;
			scanf("%s",info[i].platforms[count]);
		}
		info[i].platformCounter = count;        
	}
	printf("Which platform's games do you want to write? ");
	scanf("%s",which);
	write(info,which); //"write" is a function we created.
	printf("\nTxt file has been written\n");
}

