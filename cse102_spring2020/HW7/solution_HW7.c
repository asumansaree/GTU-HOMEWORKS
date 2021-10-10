/*
* GENERAL ALGORITHM
* Take a character each time from text.txt file. Until see the space character, continue reading. (So that punction marks will also get)
* When program see a space, then it will store that word in a string
* Send the word to control function for whether it exists in dictionary or not(If last element of the string is not a letter, then don't send last one)
* If it exists, do nothing in the file. If it not, find the best matching considering both upper-lower case, different elements, vowels etc.
* With the help of fseek, correct the misselled words in the text.txt file according to dictionary.txt file.
* All the punction marks, non-letter characters' both positions and values stay same.(I understand in that way and my code is according to this.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30	/* I accepted that one word will be max 30 character */

void fix_spelling_error(char *filename1, char *filename2, FILE *fptr_text);
int is_word_exist(char *str, FILE *fptr, int m);
void find_best_correction(char *str, FILE *fptr, FILE *fptr2, int m, int index, char punc);
char* is_upper(char *string, int m);
int is_all_num(char *str, int m);

/* Instead of sending lots of parameter to each function, I define them as global variables just for simplicity. */
/* One more reason is I use recursive function so that variables should stay same until the end of the program will locate at global scope. */
int stop_cond=0, n, count=-1, count_cpy=-1, count_same_char, word=0, old_c1, fseek_index, flag;
char pos[N], c1, c2;

int main()
{
	int cont_stat;
	char *filename_text, *filename_dict;
	filename_text = "text.txt";
	filename_dict = "dictionary.txt";
	FILE *fptr_text;
	/* I use recursion on fix_spelling_error func. So I couldn't make fopen part inside the function, I should have made it in main and send as parameter. */
	fptr_text = fopen(filename_text, "r+");
	if(fptr_text == NULL)
 	{
 		printf("Couldn't open text file.\n");
 		exit(1);
 	}
 	/* First ask the user whether he/she want to apply rule just for one letter mistake or two letter mistake. */
 	printf("Which one do you want to apply?\n""0 for fix_spelling_error\n""1 for fix_spelling_error2(BONUS PART)\n");
 	scanf("%d", &cont_stat);
	if(cont_stat == 0)
	{
		flag = 1;	/* These flags will help me in the fix_spelling_error function */
		fix_spelling_error(filename_text, filename_dict, fptr_text);
	}
	else
	{
		flag = 2;	/* Instead of write additional func, I changed necesarry part only */
		fix_spelling_error(filename_text, filename_dict, fptr_text);
	}
	fclose(fptr_text);
	printf("File succesfully arranged. You can control it now.\n");
	return 0;
}

void fix_spelling_error(char *filename1, char *filename2, FILE *fptr_text)
{
	int empty, i, j, what_returns;
	FILE *fptr_dict;
	/* There are two different counter. count will follow the file character by character whereas count_cpy will follow words. */
    count++;	count_cpy++;	
    if(count_cpy == 0)		/* After each time a new word begins, first element of that string will be send to fseek for using if necesarry. */
		fseek_index = count;
	if(count == 0)
	{
		c1 = fgetc(fptr_text);
    	c2 = fgetc(fptr_text);
    	pos[count_cpy] = c1;
	}
	else
	{
		old_c1 = c1;
		c1 = c2;
		if(c1 != ' ')	/* Unless the character you get be space, continue reading */
			pos[count_cpy] = c1;
		else
		{
			n= count_cpy;
			char pos_cpy[n+1];
			for(j=0; j<n; j++)		/* Copying the string without strcpy */
				pos_cpy[j] = pos[j];
			pos_cpy[n] = 0;	/* With making following 3 steps we're saying program that "I complated reading one word" */
			count_cpy = -1;
			stop_cond = 0;	
			fptr_dict = fopen(filename2, "r");
		    if(fptr_dict == NULL)
		 	{
		 		printf("Couldn't open text file.\n");
		 		exit(1);
		 	}	
		 	/* If last element of the string is not a letter, then don't send it. Just send it's n-1 terms */
		 	if((pos_cpy[n-1] < 65) || (pos_cpy[n-1] > 90 && pos_cpy[n-1] < 97) || (pos_cpy[n-1] > 122))
	 			what_returns = is_word_exist(pos_cpy, fptr_dict, n-1);
	 		else
	 			what_returns = is_word_exist(pos_cpy, fptr_dict, n);
	 		/********************************************************************************/
	 		if(is_all_num(pos_cpy,n) == 0)	/* This means this is a number, not a word. */
		 		what_returns = 0;	/* There is no need to control if pos_cpy is a number */
	 		/********************************************************************************/
		 	if(what_returns == 0)	/* We don't have to make any arrangement for this because this word is already exist in the dictionary */
		 		empty=0;	/* Just not to do anything */
		 	else
		 	{
		 		fptr_dict = fopen(filename2, "r");
			    if(fptr_dict == NULL)
			 	{
			 		printf("Couldn't open text file.\n");
			 		exit(1);
			 	}
			 	/* Correction will not be apply the non-letter elements if we send n-1 term */
			 	if((pos_cpy[n-1] < 65) || (pos_cpy[n-1] > 90 && pos_cpy[n-1] < 97) || (pos_cpy[n-1] > 122))
		 			find_best_correction(pos_cpy, fptr_dict, fptr_text, n-1, fseek_index, pos_cpy[n-1]);
		 		else
		 			find_best_correction(pos_cpy, fptr_dict, fptr_text, n, fseek_index, ' ');
		 	}
		}
		c2 = fgetc(fptr_text);

	}
    
    if(!feof(fptr_text))	/* Until the end of file, program will call itself. */
    {
    	if(c1 == '.' && c2 == ' ')
    		fix_spelling_error(filename1, filename2, fptr_text);
    	else if(c1 != ' ' && c2 == '.')	/* This is not only a word done, but also a sentence done. */
    	{
    		word++;		
    		fix_spelling_error(filename1, filename2, fptr_text);
    	}
    	else if(old_c1 != '.' && c1 == ' ' && c2 != '.')	/* This is the just word done. */
    	{
    		word++;
    		fix_spelling_error(filename1, filename2, fptr_text);
    	}
    	else
    		fix_spelling_error(filename1, filename2, fptr_text);
    }
    
}

void find_best_correction(char *str, FILE *fptr, FILE *fptr2, int m, int index, char punc)
{
	char str_dict_temp[N], orgnl_str[N], inequal_char;
	int i,j,sit=0;
	strcpy(orgnl_str, str);
	str = is_upper(str, m);	/* If there is upper characters in the string, is_upper will make them lowercase to get comparison easier. */
	while(!feof(fptr))    
    {
 		fscanf(fptr, "%s", str_dict_temp);
 		int count_same_char =0;
		for(i=0; i<m; i++)
 		{
 			if(str_dict_temp[i] == str[i])
 				count_same_char++;
 		}
 		/* If flag is 1, then just consider one letter difference. If it is 2, consider two letter dif */
 		if((count_same_char == m-1 && flag==1) || (flag==2 && (count_same_char == m-1 || count_same_char == m-2)))	
 		{		
 			if(m == strlen(str_dict_temp) && sit < 3)
 			{
 				if(sit==0)
 				{
 					for(i=0; i<m; i++)
	 				{
	 					if(orgnl_str[i] >= 65 && orgnl_str[i] <= 90)
	 						str_dict_temp[i] -= 32;	/* To get original upper-lower situation again, if there is a change, remove it. */
	 				}
	 				fseek(fptr2, index, SEEK_SET);
	 				if(punc == ' ')
	 					fprintf(fptr2, "%s ", str_dict_temp);
	 				else
	 					fprintf(fptr2, "%s%c ", str_dict_temp, punc);
 				}
 				else	/* This means we find a matched word at least once. */
 				{
 					for(i=0; i<m; i++)
			 		{
			 			if(str_dict_temp[i] != str[i])
			 				inequal_char = str_dict_temp[i];	/* To determine whether inequal character is vowel or not */
			 		}
			 		/* Here comes overwriting part if inequal char is a vowel */
			 		if(inequal_char == 'a' || inequal_char == 'e' || inequal_char == 'o' || inequal_char == 'u' || inequal_char == 'i')
			 		{
			 			for(i=0; i<m; i++)
		 				{
		 					if(orgnl_str[i] >= 65 && orgnl_str[i] <= 90)
		 						str_dict_temp[i] -= 32;
		 				}
		 				fseek(fptr2, index, SEEK_SET);
		 				if(punc == ' ')
		 					fprintf(fptr2, "%s ", str_dict_temp);
		 				else
		 					fprintf(fptr2, "%s%c ", str_dict_temp, punc);
			 		}
 				}
 				sit++;	/* According to pdf, it is required that we need take up to 3 iteration in dictionary */
 			}
 		}		 		
    }
    fclose(fptr);
}

char* is_upper(char *string, int m)
{
	int i;
	for(i=0; i<m; i++)
	{
		if(string[i] >= 65 && string[i] <= 90)	/* If there is an upper char, then make it lower char by adding 32 to it. */
			string[i] = string[i] + 32;
	}
	return string;
}

int is_word_exist(char *str, FILE *fptr, int m)
{
	char tempstr[N];
	while(!feof(fptr))    
    {
 		fscanf(fptr, "%s", tempstr);
 		if(strncmp(tempstr,str,m) == 0 )
 		{

 			if(m == strlen(tempstr))
	 		{
				fclose(fptr);
 				return 0;	/* This means we have our word in dictionary, so it is a true word */
 			}
 		}
 	}
 	fclose(fptr);
 	return 1;	/* This means we don't have our word in dictionary, so it is a misspelled word */
}

int is_all_num(char *str, int m)
{
	int i, c=0;
	for(i=0; i<m; i++)
	{
		if(str[i] >= '0' && str[i] <= '9')	/* Controling is all elements are number(so this is a number rather than a word) */
			c++;
	}
	if(c == m)
		return 0;
	else
		return 1;
}

